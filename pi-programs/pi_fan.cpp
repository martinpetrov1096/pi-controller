/*
Description: takes optional -m (manual) mode which also requires percentage of fan speed.
If no arguements are supplied, then fan goes to auto mode.


Notes:
    Going to use state design method, and have 2  states (auto/manual). 
        auto state:
            -will use tower_cpu_temp info froma file created by pi_sys_reader
            -defaults to 100% if cannot read the file

        manaul state:
            - sets fan to whatever temp is requested
            - if cpu temp is over 70c, defaults to auto
*/

#include <unistd.h>
#include <stdio.h>


using namespace std;

int main(int argc, char *argv[]) {

    int opt;   
    while((opt = getopt(argc, argv, ":m:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'm': 
                printf("Manual Mode: %c\n", opt); 
                printf("Fan Speed: %s\n", optarg);  
                //Do manual fan stuff
                break;  
            
            case ':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    }  
      
    return 0;
}