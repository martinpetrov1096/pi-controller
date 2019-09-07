/*
Description: pi_fan creates a seperate thread that runs the fan object's state.set().
             Fan.state changes whether the fan is in auto mode or not. 
             In the main thread, program waits for user input. If input is -1,
             fan.state goes to auto mode. If it is a positive value, fan goes to manual



Notes:
    
        auto state:
            -will use tower_cpu_temp info froma file created by pi_sys_reader
            -defaults to 100% if cannot read the file

        manaul state:
            - sets fan to whatever temp is requested
            - if cpu temp is over 70c, defaults to auto

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

class Fan {
    public:
        //pipe is used like go channels. Stores the manual speed wanted for the fan. 
        queue <int> pipe;

        Fan() {
            fin.open(fileName);
        }
        ~Fan() {
            fin.close();
        }
        void set() {

            while (true) {
                if (!pipe.empty()) {
                    currInput = pipe.front();
                    pipe.pop();
                    //If pipe == -1, set manual to false
                    if (currInput == -1) {
                        manual = false;
                    } else {
                        manual = true;
                    }
                }

                if (manual) {
                    manualState(currInput);
                } else
                {
                    autoState();
                }
                //Sleep for 2 seconds after each iteration
                sleep(2); 
            }
        }

        void autoState() {
            //If the file is open, keep reading until you reach "," 
            int currTemp  = getTemp();
            //cout << "Current Temp: " << currTemp << endl;
            if (currTemp < 50) {
                //Fan speed
            } else if (currTemp < 70) {
                //Fan Speed
            } else {
                //Fan speed = 100
            }
            
        }

        void manualState(int mSpeed) {
             //cout << "currInput: " << mSpeed << endl; 

        }

        int getTemp() {
            string currInput;
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
            return stoi(currInput);
        }
    private:
        bool manual;
        int currInput;
        FILE *sysTempFd;
        string fileName = "tower_temp.csv";
        ifstream fin;
};


int main() {

    //Need to have fan be a pointer since we are going to be deleting and newing fan->state 
    Fan *fan = new Fan;
    string fanVal;
    thread setThread(&Fan::set, fan);

    while (true) {


        //if parent process exited, kill this child
        if (getppid() == 1) {
            cout << "Parent Died" << endl;
            //setThread.join();
            exit(0);
        } 

        cin >> fanVal;
        cout << "fanVal: " << fanVal << endl;
        //fan->pipe.push(fanVal);

        if(fanVal == "30") 
            return 0;

        sleep(2);



    }
    setThread.join();
    return 0;
}