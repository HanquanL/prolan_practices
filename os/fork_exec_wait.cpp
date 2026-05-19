#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(){
    pid_t pid = fork();

    if(pid ==0){
        cout << "child process will run ls now. " << endl;

        char *args[]{
            const_cast<char *>("ls"),
            const_cast<char *>("-l"),
            nullptr
        };

        execv("/bin/ls", args);

        //if succeeds, this line will not run
        cout << "child execv failed." << endl;

        return 1;
    }else if (pid > 1){
        cout << "parent is waiting for child" << endl;

        wait(nullptr);    //parent blocked 

        cout << "child finished" << endl;
    }else {
        cout << "fork faild" << endl;
        return 1;
    }

    return 0;
}