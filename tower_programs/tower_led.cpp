
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
    if (strcmp(arg, "blue") == 0) {
        printf("blue called\n");
        if(write (fd, "0 0 100 100\n", 13) < 0) {
                return -1;
        }
    } else if (strcmp(arg, "red") == 0) {
        if(write (fd, "100 0 0 100\n", 13) < 0) {
                return -1;
        }
    } else if (strcmp(arg, "green") == 0) {
        if(write (fd, "0 100 0 100\n", 13) < 0) {
                return -1;
        }
    } else if (strcmp(arg, "white") == 0) {
        if(write (fd, "100 100 100 100\n", 17) < 0) {
                return -1;
        }
    }
    
    
    
        
    close(fd);

}
