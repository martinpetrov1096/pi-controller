
/*
Usage:
    Can control either the fan or the led's from this program using the command line args

    tower_main -f 55 - Sets the fan's to manual at 55%
    tower_main -f auto - Sets the fans to auto, and uses the sys_info to get cpu temp

    tower_main -l blue - Sets the LED's to blue
    tower_main -l white

*/

#include <stdio.h>
#include <unistd.h>

#include <string>

using namespace std;

int main(int argc, char *argv[]) {

    int opt;   
    while((opt = getopt(argc, argv, "f:l:h")) != -1)  
    {  
        switch(opt)  
        {  
            case 'f': {
                printf("Fan Mode: %c\n", opt); 
                printf("Fan Speed: %s\n", optarg);  

                int childPid = fork();
                if (childPid == 0) {
                    execl("/home/pi/Documents/pi-controller/tower_programs/tower_fan", "./tower_fan", optarg, (char*) 0);
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




/*
New idea: looks exactly like the standard bash program in the book

3 children:
FAN - Send percentage of fan, exit when done
SYSINFO - Runs in the background, might not even be needed in this program, start when tower_main starts,
close when tower_main is closed. Send CPU Temp
LED - Send led command, exit when done


*/

