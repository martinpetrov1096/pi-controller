
/* Usage:

fan

cmd args:

 -a : Auto (Default) - Uses fan speed from tower_sys_info to determine ap
 -m : Manual, followed by an int specifying the percentage of the fan speed you want

 
 -s : return current fan speed
*/
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>



#include <fcntl.h>  //file open types
#include <sys/ioctl.h>


using namespace std;

int main (int argc, char *argv[]) {

    int fd; //file descriptor to be used for serial port
    //Open the serial port 
    if ((fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) < 0) {
        printf("Open failed with exit code: %d\n", fd);
        return -1;
    }

    //If 1st arg is a number, write the value, else, fan will be in auto
    if (strtol(argv[1], NULL, 10) != 0) {

        if(write (fd, argv[1], strlen(argv[1])) < 0) {
                return -1;
        }

    } else {

        if(write (fd, "auto", 4) < 0) {
                return -1;
        }

    }
        
    close(fd);

}
