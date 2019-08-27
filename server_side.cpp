/*

int main() {

    pipe p[2];  //Pipe to send/recieve commands


    //Calling all of the programs to run here (Fan/LED)
    subProcesses children[2] = {fan, led} //struct contains program name as well as pid, and pipe

    for (currProc: subprocess) {
        currProc.pid = fork() {
            if (currProc.pid == 0)
                exec(currProc.name, p);
        }


    }

    while(true) {
        userInput = getUserInput();


        wait for user input

    }




}





*/