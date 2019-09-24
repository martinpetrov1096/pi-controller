/*
Description:
    pi-main reads input from the pi's gpio serial port and determines which
    program to redirect the input to.

Sample serial input:
    fan 75 - redirects to fan, where it will change fans to be at 75%
    fan -1    - redirects to fan, where it will operate in auto mode, and use the 
                sysinfo information

    led red green blue brightness
    led 0 0 100 100
 

 Implementation:

   
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <fcntl.h>  //file open types
#include <wiringPi.h>
#include <wiringSerial.h>
#include <string>
#include <iostream>
#include <vector>

#include <wiringSerial.h>

using namespace std;

//Read from serial until '\n' is reached
string serialReadLine() {

    //fd is the file descriptor for serial
    int fd;
    string input;
    char currChar;

    fd = serialOpen("/dev/ttyAMA0", 115200);
    do {
        currChar = serialGetchar(fd);
        input += currChar;
    } while(currChar != '\n');
    return input;

}

/*
Args[0] is the program name
Args[1] is the rest of the string
*/
vector<string> inputToArgv(string input) {

    vector <string> args(2);

    int i = 0;
    while(input[i] != ' ') {
        args[0] += input[i];
        ++i;
    } 
    ++i; //for the ' ' (space)
    for (; i < input.length(); ++i) {
        args[1] += input[i];
    }
    return args;
}


class ChildProg{

    public:
        ChildProg(string n) {
            name = n;
        }

        void exec() {
            pipe(pipefd);
            childPid = fork();
            if (childPid == 0) {
                close(pipefd[1]);   //Close output part of pipe
                dup2(pipefd[0], STDIN_FILENO); //set pipefd[0] to cin for child
                close(pipefd[0]);
                execl(name.c_str(), ("./" + name).c_str(), (char*) 0);
            }

        }

        void update(string command) {
            write(pipefd[1], (command + '\n').c_str(), command.length() + 1);
            //close(pipefd[1]);
        }
    private:
        int childPid;
        string name;
        int pipefd[2];
};


int main() {
    //int serialFd = serialOpen();

    //Call all pi child programs
    ChildProg fan("pi_fan.out");
    ChildProg led("pi_led.out");
    ChildProg sys("pi_sys_reader.out");

    //fan.exec();
    led.exec();
    //sys.exec();

    string serialString;
    string* currProgram;
   
    vector <string> input(2);
    int fd = 0;
    char test;
    while (true) {
        
        serialString = serialReadLine();
        
        //serialString = "LED 52";    //TODO: grab input from serialReadLine()
        input = inputToArgv(serialString);
        //cout << input[0] << endl;
        //cout << input[1] << endl;

        if (input[0] == "LED") {
            cout << "calling led" << endl;
            led.update(input[1]);
        }
        if (input[0] == "FAN") {
            fan.update(input[1]);
        }

        sleep(2);
    }
    
    return 0;
}