//peterson's solution
/*
the basic idea is that this is a Humble Algorithm
It focuses on bounded waiting, progress, mutual exclusion
if thread 1 and thread 2 both want to enter the critical section together
one of them will ask the other one to go first
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthreads.h>

int flag[2] = {0, 0};
int turn = 0;

void* process(void* arg){
    int i = *(int* arg);
    int j = 1-i; //if i=0, j=1; j=1, i=0

    //entry section
    flag[i] = 1; //wants to enter critical section
    turn = j; //let other go first, if needed

    //wait while the other thread wants to enter
    while(flag[j] == 1 && turn == j);

    //critical section
    printf("Thread %d is in critical section\n", i);
    sleep(1);
    printf("Thread %d is leaving the critical section\n", i);

    //exit section
    flag[i] = 0; //done with critical section

    return NULL;
}

int main(){
    pthread_t t0, t1;
    int id_0 = 0, id_1 = 1;

    pthread_create(&t0, NULL, process, &id_0);
    pthread_create(&t1, NULL, process, &id_1);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    
    return 0;
}