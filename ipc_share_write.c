#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<stdlib.h>

int main(){
    key_t key = ftok("shmfile", 65); //generates a key

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); //create shared memory with necessary args

    if(shmid == -1){
        perror("shmget failed");
        exit(1);
    }

    char *str = (char*) shmat(shmid, NULL, 0); //attach to shared memory
    if (str == (char *)-1){
        perror("shmat failed");
        exit(1);
    }

    printf("Write to shared memory: ");
    gets(str); //gets a string input

    shmdt(str); //detach shared memory
    return 0;
}