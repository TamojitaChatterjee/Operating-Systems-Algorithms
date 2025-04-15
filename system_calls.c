/*
Basic system calls in Linux:
- open()
- read()
- write()
- sleep()
- fork()
- getpid()
- wait()
- exec()
- lseek()
*/

//open()
#include<stdio.h>
#include<fcntl.h> //file control

int main(){
    int fd = open("file.txt", O_RDONLY); //open in read-only mode

    if(fd<0){
        printf("Failed to open file\n");
    }else{
        printf("File opened successfully\n");
    }

    return 0;
}

//read()
#include<stdio.h>
#include<unistd.h> //unix std
#include<fcntl.h>

int main(){
    int fd = open("file.txt",O_RDONLY); //open file in read-only mode
    char buffer[1000]; //stores whatever we read
    int bytes = read(fd, buffer, 99); //reads first 99 bytes
    buffer[bytes] = '\0'; //end string with null character
    printf("Data read: %s\n", buffer); //print the data that has been read
    close(fd); //close the file
    return 0;
}

//write()
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    int fd = open("file.txt", O_WRONLY | O_CREAT, 0644); //O_WRONLY --> write only ; O_CREAT --. if file doesn't exist, create it; 0644 -> permission
    char message[] = "Hello, World!";
    write(fd, message, sizeof(message));
    close(fd);
    printf("Message has been written in the file\n");
    return 0;
}

//sleep()
#include<stdio.h>
#include<unistd.h>

int main(){
    printf("Sleeping for 3 seconds...\n");
    sleep(3);
    printf("Awake now!\n");
    return 0;
}

//fork()
#include<stdio.h>
#include<unistd.h>
/*
The basic idea is to create a child process by
duplicating the contents of the parent process
*/
int main(){
    pid_t pid = fork();

    //if fork() returned 0, we are in the child process
    if (pid == 0){
        printf("This is the child process\n");
    }else{
        printf("This is the parent process");
    }
    return 0;
}

//getpid()
#include<stdio.h>
#include<unistd.h>

int main(){
    printf("The process ID is: %d\n", getpid()); //the process ID is assigned by the OS
    return 0;
}

//wait()
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h> //exclusive for Linux

int main(){
    pid_t pid = fork();

    if(pid == 0){
        printf("Child process");
    }else{
        wait(NULL); //pauses the parent process until any of it's child processes finishes execution. The NULL means that we do not care about the child's exit status
        printf("Parent waited for child to finish\n");
    }
    return 0;
}

//exec()
#include<stdio.h>
#include<unistd.h>

int main(){
    printf("Running 'ls' command using exec\n");
    exec("/bin/ls","ls","-1",NULL);
    /*
    Arguments:
        1. full path
        2. program name
        3. lost listing formula
        4. end of arguments is marked by NULL
    */

    printf("This line won't run if exec is successful");

    return 0;
}

//lseek()
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd = open("file.txt", O_RDWR);
    lseek(fd, 5, SEEK_SET); //move to 5th byte
    write(fd, "X", 1); //overwrite 1 character
    close(fd);
    printf ("seek and overwrite successful");
    return 0;
}