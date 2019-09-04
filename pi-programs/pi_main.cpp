/*
Description:
    pi-main reads input from the pi's gpio serial port and determines which
    program to redirect the input to.

Sample serial input:
    fan 75 - redirects to fan, where it will change fans to be at 75%
    fan -auto    - redirects to fan, where it will operate in auto mode, and use the 
                sysinfo information
 

 Implementation:

    Read first 3 chars; if fan, redirect to fan, if led, redirect to led. If something else, ignore
*/


int main() {


    return 0;
}