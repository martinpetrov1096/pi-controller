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

    Read first 3 chars; if fan, redirect to fan, if led, redirect to led. If something else, ignore
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>  //file open types

#include <string>

int main() {

    //file descriptor to be used for serial port
    int fd; 
    char buf;

    //Open the serial port 
    if ((fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) < 0) {
        printf("Open failed with exit code: %d\n", fd);
        return -1;
    }

    //Read until space is reached, which will be the args to the program. Then read until "\n" is reached
    if (read(fd, &buf, 1) < 0) {
        printf("Error\n");
            
        return -1;
    }


    printf("%s\n", buf);
    return 0;
}