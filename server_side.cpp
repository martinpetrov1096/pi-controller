#include <string>
#include <iostream>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

using namespace std;

class App {
    public: 
        pid_t pid;
        string name;

    //TODO: Add pipe here
};



int main() {

    //Declare all 
    App fan;
    fan.name = "fan_client";


    

    //Calling all of the programs to run here (Fan/LED)
    App childProc[2];
    childProc[0] = fan;
        
        

    for (App currProc: childProc) {
        currProc.pid = fork();
            if (currProc.pid == 0) {
                cout << "Fork worked\n child_pid: " << currProc.pid << endl;
                execl("/home/pi/Documents/pi-controller", "./fan_clent", (char*) NULL);

                //execl("/home/vlc", "/home/vlc", (char*) NULL);
            }
    }




    while(true) {
       // userInput = getUserInput();


       // wait for user input

    }




    return 0;
}






