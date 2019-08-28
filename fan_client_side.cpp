//send FAN TEMP command every 2 seconds

/* Options:

Auto: Default - FAN SYSTEM_TEMP , e.g: FAN 42
Manual: FAN PERCENTAGE, e.g: FAN 75%

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
    cout << "working here";
    int fd;   
    const char temp[] = "50";
    /*   
    if ((fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) < 0) {
        printf("Open failed with exit code: %d", fd);
        return -1;
    }
    
    while(true) {
        if (getppid() == 1) {   //if parent process exited, kill this child
            exit(0);
        } 
        cout << "working loop";
        if(write (fd, &temp, strlen(temp)) < 0) {
            cout << "fail";
            return -1;
        }
        sleep(2);
    }*/

}
