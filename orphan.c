//orphan process
/*
The basic idea is that the parent process gets terminated
before the child process
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    pid_t pid = fork();

    if(pid <0){
        perror("Fork failed");
        return 1;
    }else if(pid > 0){
        printf("Parent started...\n");
        exit(0);
    }else{
        printf("Child started...\n");
        wait(2);
        exit(0);
    }
    return 0;
}