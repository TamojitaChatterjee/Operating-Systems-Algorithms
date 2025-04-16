//creating a zombie process
/*
The basic idea is child executes and gets over
before parent can call wait()
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    pid_t pid = fork();

    if(pid == 0){
        printf("Child exiting...\n");
        exit(0);
    }else{
        printf("Parent sleeping...Child becomes zombie\n");
        sleep(10);
        printf("Parent exiting...\n");
    }
    return 0;
}