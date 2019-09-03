
/* Usage:

fan

cmd args:

 -a : Auto (Default) - Uses fan speed from tower_sys_info to determine ap
 -m : Manual, followed by an int specifying the percentage of the fan speed you want
 -s : return current fan speed
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

int main (int argc, char *argv[]) {

    int fd;   
    const char temp[] = "50";
     
    if ((fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) < 0) {
        printf("Open failed with exit code: %d\n", fd);
        return -1;
    }

    if(write (fd, &temp, strlen(temp)) < 0) {
            cout << "fail" << endl;
            return -1;
    }
    
    close(fd);
    
}
