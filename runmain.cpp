//
// Created by kuukie on 2021/7/16.进程与子进程 “系统调用”
//

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int mains() {
    pid_t pid = fork();
    if(pid < 0) {
        cerr << "fork apply error\n";
        return 0;
    } else if (pid == 0) {
        cout << "Sub-process PID:" << getpid() << " PPID:" << getppid() << "\n\n";
        char* args[] = {"/home/polite/","test",(char*)0};
        char* evnp[] = {0};
        execve("/home/polite/test",args,evnp);
    } else {
        cout << "Parent process\n";
        pid_t pr = wait(NULL);
        cout << "\nParent process, I catched a child process with pid of " << pr << "\n";
    }
}
