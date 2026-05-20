#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main(){
    int pipefd[2];

    if(pipe(pipefd) == -1){
        cout << "piple faild" << endl;
        return 1;
    }

    pid_t pid = for();

    if(pid == 0){
        //child process receive message
        close(pipefd[1]); // close write end

        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));

        cout << "child received: " << buffer << endl;

        close(pipefd[0]);
    }else if( pid > 0 ){
        // parent process send message
        close(pipefd[0]); // close read end

        const char* message = "Hello from parent!";
        write(pipefd[1], message, strlen(message) + 1);

        close(pipefd[1]);
        wait(nullptr);
    }else{
        cout << "fork failed" << endl;
        return 1;
    }

    return 0;
}