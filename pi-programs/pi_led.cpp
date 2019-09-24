/*
Description: 
        pi_led waits for a valid input from the standard input
        
        Valid input: 4 integer values (red/green/blue/brightness) seperated by a space
        If more than 4 values are entered, program will only use first 4
        If any of the values are invalid integers, program will default to blue color
           

*/
#include <sstream>
#include <iostream> //for getLine

#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>


using namespace std;

class Color {
    public:
        int rgba[4] = {0,0,0,0};
};

class Led {
    public:

        Led() {
            wiringPiSetup();
            softPwmCreate(0, 0, 100);
            softPwmCreate(1, 0, 100);
            softPwmCreate(2, 0, 100);
        }
        
        //Format the input into color.rgba
        void formatInput(string input) {
            string temp;
            int j = 0;
            int tempRgba[4];
            //Convert string input into array of values for red/green/blue/brightness
            for(int i = 0; j < 4; ++i) {
            
                if(input[i] == ' ' || input[i] == '\0') {
                    try {
                        
                        tempRgba[j] = stoi(temp);
                    }
                    //If invalid argument, default to max brightness blue
                     catch(invalid_argument) {
                         color.rgba[0] = 0;
                         color.rgba[1] = 0;
                         color.rgba[2] = 100;
                         color.rgba[3] = 100;
                        return;
                    }
                    temp = "";
                   
                    ++j;
                    continue;
                }
                temp += input[i];  
            }

            //If input values are all > 0 && < 100, store them in color.rgba
            //Needs to be done after check, so if just 1 value is invalid, color stays the same as previously
            if(tempRgba[0] >= 0 && tempRgba[0] <= 100 
            && tempRgba[1] >= 0 && tempRgba[1] <= 100
            && tempRgba[2] >= 0 && tempRgba[2] <= 100
            && tempRgba[3] >= 0 && tempRgba[3] <= 100
            ) {
                color.rgba[0] = tempRgba[0];
                color.rgba[1] = tempRgba[1];
                color.rgba[2] = tempRgba[2];
                color.rgba[3] = tempRgba[3];
            }
            return;
        }

        void getLed() {
            cout << "Red: " << color.rgba[0] << endl;
            cout << "Green: " << color.rgba[1] << endl;
            cout << "Blue: " << color.rgba[2] << endl;
            cout << "Brightness: " << color.rgba[3] << endl;

        }

        void setLed() {
            softPwmWrite(0, color.rgba[0]);
            softPwmWrite(1, color.rgba[1]);
            softPwmWrite(2, color.rgba[2]);
        }

      

    private:
        Color color;
};


int main() {

    Led led;
    string input;

    while (true) {

        //if parent process exited, kill this child by sending -2 to the pipe
        if (getppid() == 1) {
            cout << "Parent Died" << endl;
            exit(0);
        } 

        //Get the last line from the the standard input, and store it in input.
        getline(cin, input);

        if(input == "\n" || input == "\0") {
            continue;
        }

        cout << input << endl;
        cout << "num chars: " << input.length() << endl;
        led.formatInput(input);
        led.setLed();
        led.getLed();
        sleep(2);
    }

    return 0;
}