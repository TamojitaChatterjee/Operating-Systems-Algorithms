#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>

int main(){

    key_t key = ftok("shmfile", 65); //same key as writer

    int shmid = shmget(key, 1024, 0666); //same as writer
    if (shmid == -1){
        perror("shmget failed");
        exit(1);
    }

    char *str = (char*) shmat(shmid, NULL, 0); //attach to shared memory
    if(str == (char*)-1){
        perror("shmat failed");
        exit(1);
    }
    
    printf("Data from shared memory: %s\n", str); //read from shared memory
    shmdt(str); //detach shared memory
    return 0;
    return 0;
}