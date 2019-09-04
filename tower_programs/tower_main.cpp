
/*
Usage:
    Can control either the fan or the led's from this program using the command line args

    tower_main -f 55 - Sets the fan's to manual at 55%
    tower_main -f auto - Sets the fans to auto, and uses the sys_info to get cpu temp

    tower_main -l blue - Sets the LED's to blue
    tower_main -l white

    tower_main -f auto -l blue - sets fan to auto and led's to blue

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

    int opt;   
    while((opt = getopt(argc, argv, "f:l:h")) != -1)  
    {  
        switch(opt)  
        {  
            case 'f': {
                printf("Calling fan with options: %s\n", optarg);  
                int childPid = fork();
                if (childPid == 0) {
                    execl("/home/pi/Documents/pi-controller/tower_programs/tower_fan", "./tower_fan", optarg, (char*) 0);
                } else {
                    wait(&childPid);
                    return 0;
                }
            }
                break;  
            case 'l':
                printf("LED Mode: %c\n", opt); 
                printf("Color: %s\n", optarg);  
                break;
            case 'h':
                printf("Fan control: -f followed by auto, or value for fan speed percentage\n");
                printf("LED control: -l followed by desired color(e.g red, green, blue, white)\n");
                break;
            case ':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                printf("-h for help\n");
                break;  
        }  
    }  
      
    return 0;
}


