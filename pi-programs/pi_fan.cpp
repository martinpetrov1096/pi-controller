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
#include <iostream>


using namespace std;

class Fan {

    public:
        State *state;
        Fan() {
            state = new State();
        }
    
    private:


};

class State {
    virtual void set();
};

class Auto: public State {
    public:
        void set() override {
            cout <<"Auto State" << endl;
        }

};

class Manual: public State {
    public:
        void set () override {
            cout <<"Manual State" << endl;
        }
};

int main() {

    Fan fan;
    Auto autoState;

    fan.state = &autoState;
    fan->state.set();


    return 0;
}