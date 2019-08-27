#include <string>
#include <iostream>
#include <vector>

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

    //Declare all apps
    App fan;
    fan.name = "fan_client";


    

    //Calling all of the programs to run here (Fan/LED)
    //App childProc[1];
    vector<App> childProc(1);
    childProc.push_back(fan);


        
        

    for (App currProc: childProc) {
        currProc.pid = fork();
            if (currProc.pid == 0) {
                //cout << "Fork worked\n child_pid: " << currProc.pid << endl;
                write(0, "Fork Worked\n", 15);
                chdir("/home/pi/Documents/pi-controller/");
                execl(currProc.name.c_str, ("./" + currProc.name).c_str, (char*) NULL);

            }
    }




    //while(true) {
       // userInput = getUserInput();


       // wait for user input

    //}




    return 0;
}






