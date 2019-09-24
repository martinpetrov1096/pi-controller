/*
Description:
    pi-main reads input from the pi's gpio serial port and determines which
    program to redirect the input to.

Sample serial input:
    fan 75 - redirects to fan, where it will change fans to be at 75%
    fan auto    - redirects to fan, where it will operate in auto mode, and use the 
                sysinfo information

    led red green blue brightness
    led 0 0 100 100
 

 Implementation:

   
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>  //file open types

#include <string>
#include <iostream>

using namespace std;

//Read from serial until '\n' is reached
string serialReadLine() {

    //fd is the file descriptor for serial
    int fd;
    string input;
    char currChar = 0;

    if ((fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) < 0) {
        printf("Open failed with exit code: %d\n", fd);
        return "-1";
    }
    
    while(currChar != '\n') {
        read(fd, &currChar, 1);
        input += currChar;

    }

    return input;
}

/*
Args[0] is the program name
Args[1] is the rest of the string
*/
string* inputToArgv(string input) {
    string* args;
    args = new string[2];

    //Getting the program name
    int i = 0;
    while(input[i] != ' ') {
        args[0] += input[i];
        ++i;
    }
    ++i; //Skip the space

    //Get the program parameters from the rest of the input
    for (;i < input.length(); ++i) {
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

    //Call all pi child programs
    ChildProg fan("pi_fan.out");
    ChildProg led("pi_led.out");
    ChildProg sys("pi_sys_reader.out");

    //fan.exec();
    led.exec();
    //sys.exec();

    string serialString;
    string* currProgram;
   
    string input;
    while (true) {
        

        input = serialReadLine();
        cout << input << endl;
        //cin >> input;
        //serialString = "LED 52";    //TODO: grab input from serialReadLine()
        
        /*if (inputToArgv(serialString)[0] == "FAN") {
            fan.update(input);
           // fan.update("76");
        }

        if (inputToArgv(serialString)[0] == "LED") {
            led.update(input);
        }*/

        sleep(2);
    }

    return 0;
}