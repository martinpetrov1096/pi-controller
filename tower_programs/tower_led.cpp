
/* Usage:

fan

cmd args:

 -auto : Auto (Default) - Uses fan speed from tower_sys_info to determine ap
 -value(int) : Manual, followed by an int specifying the percentage of the fan speed you want (valid from 0-100)

 TODO: 
 -s : return current fan speed
*/



#include <unistd.h>
#include <fcntl.h>  //file open types
#include <sys/ioctl.h>
#include <string.h> //strlen()
#include <stdio.h>
#include <stdlib.h> //strtol()


using namespace std;

int main (int argc, char *argv[]) {

    char arg[strlen(argv[1])];
    strcpy(arg, argv[1]);
    printf("Workin2g\n");
    //file descriptor to be used for serial port
    int fd; 
    
    //Open the serial port 
    if ((fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) < 0) {
        printf("Open failed with exit code: %d\n", fd);
        return -1;
    }

    //Write "LED" to serial so pi_main knows what program to call
    if(write(fd, "LED ", 4) < 0) {
        return -1;
    }

    //If 2nd arg is a number, write the value, else, fan write -1 to let the fan know to be in auto
    //Add "\n" to be able to parse on the pi's side
    printf("%s\n", arg);
    if (arg == "blue") {
        printf("blue called\n");
        if(write (fd, "0 0 100 100\n", 12) < 0) {
                return -1;
        }
    } else if (arg == "red") {
        if(write (fd, "100 0 0 100\n", 12) < 0) {
                return -1;
        }
    } else if (arg == "green") {
        if(write (fd, "0 100 0 100\n", 12) < 0) {
                return -1;
        }
    } else if (arg == "white") {
        if(write (fd, "100 100 100 100\n", 14) < 0) {
                return -1;
        }
    }
    
    
    
    
    /*
    if (strtol(arg, NULL, 10) != 0) {

        strcat(arg, "\n");
        if(write (fd, arg, strlen(arg)) < 0) {
                return -1;
        }

    } else {

        if(write (fd, "-1\n", 2) < 0) {
                return -1;
        }

    }*/
        
    close(fd);

}
