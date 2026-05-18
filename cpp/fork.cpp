#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
int main(){
    pid_t pid = fork();

    if(pid == 0){
        //child process
        cout << "This is child process" << endl;
        cout << "child PID: " << getpid() << endl;
    }else if(pid > 0){
        // parent process
        cout << "This is parent process" << endl;
        cout << "Parent PID: " << getpid() << endl;
        cout << "Parent's child PID: " << pid << endl;

        wait(nullptr); // parent waits for child to finish
    }else{
        //fork failed
        cout << "fork failed" << endl;
        return 1;
    }

    return 0;
}



