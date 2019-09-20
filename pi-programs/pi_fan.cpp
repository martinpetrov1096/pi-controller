/*
Description: 
        pi_fan creates a seperate thread that runs the fan.setState, which will initially call fan.stateAuto(). 
        It then waits for input from the standard input. 
        
        Valid input: integer with range [-1, 100]. Invalid input will be ignored
        
        if input == -1, fan.stateAuto() will be called

        if input > 0 && input <= 100, fan.stateManual() will be called

        if input == -2, thread running fan.setState() will exit
           
            stateAuto():
                -will use tower_cpu_temp info froma file created by pi_sys_reader
                -defaults to 100% if cannot read the file

            stateManual():
                - sets fan to whatever convertedInput is requested
                - if cpu temp is over 70c, defaults to auto

*/

/*
TODO:
    1. When pi_fan process dies, send kill signal to the child via the inputPipe to end the thread - done (I think)
    2. Reset tower_temp.csv every hour, and allow this program to run with empty file
    3. Fix setFan() to write to pi gpio
*/



#include <fstream>
#include <sstream>
#include <iostream> //for getLine
#include <thread>
#include <queue>

#include <unistd.h>
#include <iostream>
#include <fcntl.h>  //file open types
#include <stdio.h>


using namespace std;

/*
TempMonitor class deals with retrieving the temperature from tower_temp.csv
*/
class TempMonitor {
    public:
        //Grab the current CPU temp from the tower_temp.csv
        int getTemp() {
        
            string currInput;
            fin.open(tempFileName);
             //If the file is open, keep reading until you reach "," 
            if(fin.is_open()) {
                fin.seekg(-1,ios_base::end);                // go to one char before the EOF
                char ch;

                //Need do while loop to ignore ',' at end of file
                do {
                    fin.seekg(-2, ios_base::cur);  
                    fin.get(ch); 

                    //If have reached the beginning of file, break
                    if ((int) fin.tellg() < 1) {
                        fin.seekg(0);
                        break;
                    }
                } while (ch != ',');
                getline(fin, currInput, ',');
            }
            fin.close();

            try {
                return stoi(currInput);
            }
            catch(invalid_argument) {
                return 100;
            }
        }

    private:
        FILE *sysTempFd;
        string tempFileName = "tower_temp.csv";
        ifstream fin;

};


class Fan {
    public:
        //Grabs the current input from the pipe, stores it in currInput, and sets manual to true or false 
        void getCurrInput() {
            if (!inputPipe.empty()) {
                    currInput = inputPipe.front();
                    inputPipe.pop();
                    //If inputPipe == -1, setState manual to false
                    if (currInput == -1) {
                        manual = false;
                    } else {
                        manual = true;
                    }
            }
            return;
        }

        int getFanSpeed() {
            return 30; //TODO: remove later
            //return pwmRead(3)
        }
        //check if input is valid, and push to inputPipe if it is, else ignore
        void pushInput(string input) {
            int convertedInput;
            //see if input if a valid number
            try {
                convertedInput = stoi(input);
            }
            catch(invalid_argument) {
                return;
            }
            if (!(convertedInput > 100 || convertedInput < -1)) {
                inputPipe.push(convertedInput);
            } 
            if (convertedInput == -2) {
                exit(0);
            }
            return;
        }

        void setFanSpeed(int val) {
            //pwmWrite(3, val); //Technially max is 1024, not 1000, but close enough
            cout << "Writing to PWM: " << val * 10 << endl;
        }

        void setState() {
            while (true) {
                getCurrInput();
                if (manual) {
                    stateManual(currInput);
                } else {
                    stateAuto();
                }
                //Sleep for 2 seconds after each iteration
                sleep(2); 
            }
        }

        void stateAuto() {
            cout << "AutoState" << endl;
            int currTemp  = tempMonitor.getTemp();
            cout << "Current Temp: " << currTemp << endl;
            if (currTemp < 50) {
                setFanSpeed(0);
            } else if (currTemp < 70){
                /*
                    50c = 40%
                    60c = 70%
                    70c = 100%
                    y = 3x - 110
                */

                setFanSpeed(3 * currTemp - 110);
            } else {

                setFanSpeed(100);
            }        
        }

        void stateManual(int mSpeed) {
             cout << "Manual State" <<  endl; 
             setFanSpeed(mSpeed);
             if (tempMonitor.getTemp() > 70){
                stateAuto();
             }
        }

    private:
        bool manual;
        int currInput;
        queue <int> inputPipe;  //inputPipe is used like go channels. Stores the input 
        TempMonitor tempMonitor;
};


int main() {

    Fan fan;
    string input;

    thread setThread(&Fan::setState, &fan);

    while (true) {

        //if parent process exited, kill this child by sending -2 to the pipe
        if (getppid() == 1) {
            cout << "Parent Died" << endl;
            fan.pushInput("-2");
            setThread.join();
            exit(0);
        } 

        //Get the last line from the the standard input, and store it in input.
        getline(cin, input, '\n');
        fan.pushInput(input);
    }
    setThread.join();
    return 0;
}