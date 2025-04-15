//ipc using shared memory -- read and write process
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h> //shared memory
#include<sys/ipc.h> //ipc

#define SHM_SIZE 1024 //size of shared memory

int main(){

    //create a unique key for shared memory
    key_t key = ftok("shmfile", 65);
    //ftok generates a unique key based on the file named "shmfile" and the number 65
    //the key is used for accessing the shared memory segment

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); //create a shared memory segment
    //shmget creates a shared memory segment with given key, size(1024 bytes) and permissions
    //0666 gives read/write permissions, IPC_CREAT creates the segment if it doesn't exist

    if(shmid == -1){ //check if memory creation failed
        printf("shmget failed"); 
        exit(1); //exit if there was an error in shared memory
    }

    //attach shared memory segment to address space of process
    char *str = (char*) shmat(shmid, NULL, 0);
    //shmat --> attajches shared memory segment to process's address space and returns a pointer
    //str is a pointer to the shared memory

    if(str == (char*)-1){ //in case of failure
        printf("shmat failed"); //or you may use perror
        exit(1);
    }

    printf("Write to shared memory: ");
    gets(str); //get user input and store in shared memory
    //gets is used to demonstrate reading input into shared memory

    printf("Data from shared memory: %s\n",str); //print data from shared memory

    //detach shared memory segment from the process
    shmdt(str); 

    return 0;
}