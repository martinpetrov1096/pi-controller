/*
Description:
    pi-main reads input from the pi's gpio serial port and determines which
    program to redirect the input to.

Sample serial input:
    fan 75 - redirects to fan, where it will change fans to be at 75%
    fan auto    - redirects to fan, where it will operate in auto mode, and use the 
                sysinfo information

    led blue
    led white
 

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

int main() {

    //Call all pi child programs
    int pipeFan[2];
    pipe(pipeFan);

    int childPid = fork();
    if(childPid == 0) {
        cout << "Fan Called" << endl;
        close(pipeFan[1]);
        dup2(pipeFan[0], STDIN_FILENO);
        close(pipeFan[0]);
        execl("pi_fan.out", "./pi_fan.out", (char *) 0);
    }

    close(pipeFan[0]);
    string serialString;
    string* currProgram;
   
    string input;
    while (true) {

        serialString = "FAN 52";    //TODO: grab input from serialReadLine()
        
        if (inputToArgv(serialString)[0] == "FAN") {
            //send currProg[1] to cin of pi_fan child process
            write(pipeFan[1], inputToArgv(serialString)[1].c_str(), 20);
            close(pipeFan[1]);
        }

        sleep(2);
    }

    return 0;
}