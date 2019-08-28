/*
client for LED's


*/

#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main () {

    int serial;  
    string ledCmd; 
    

    if ((serial = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) < 0) {
        printf("Open failed with exit code: %d", serial);
        return -1;
    }
    
    while(true) {
        if (getppid() == 1) {   //if parent process exited, kill this child
            exit(0);
        } 


        
        cin >> ledCmd;

        if (write(serial, ledCmd.c_str(), ledCmd.length()) < 0)
            exit(-1);

        

      

    }

}