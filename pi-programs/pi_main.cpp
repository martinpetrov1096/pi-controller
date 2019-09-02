/*
Description:
    pi-main reads input from the pi's gpio serial port and determines which
    program to redirect the input to.

Sample serial input:
    fan -m 75 - redirects to fan, where it will change fans to be at 75%
    fan -a    - redirects to fan, where it will operate in auto mode, and use the 
                sysinfo information
    sys 


*/