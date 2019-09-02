/*
Description: 


Notes:
    Going to use state design method, and have 2  states (auto/manual)

        auto state:
            -will use tower_cpu_temp info froma file created by pi_sys_reader
            -defaults to 100% if cannot read the file

        manaul state:
            - sets fan to whatever temp is requested
            - if cpu temp is over 70c, defaults to auto
*/
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {


    string args[argc];  //used to store args in c++ string

    //copying cmd arg's to args[]
    for (int i = 0; i < argc; ++i) {
        args[i] = argv[i];
    }
    return 0;
}