//dining philosopher's
/*
The basic idea behind this is:
There are n (say, 5) philosophers sitting around a table and eating
Each philosopher has one fork (or chopstick). So there are a  total of 5
A philosopher needs 2 chopsticks to start eating - one on the left, the other on the right
philopher's can either be thinking, or hungry, or eating
*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5 //number of philosophers

pthread_mutex_t forks[N]; //one mutex lock for each fork

void* philosopher(void* num){
    int id = *(int *)num;

    while(1){
        printf("Philosopher %d is thinking...\n",id);
        sleep(1); //thinking

        //pick up chopsticks
        if(id == N-1){
            //last philosopher picks up right fork first to avoid deadlock
            pthread_mutex_lock(&forks[(id+1)%N]);
            pthread_mutex_lock(&forks[id]);
        }else{
            pthread_mutex_lock(&forks[id]); //first left
            pthread_mutex_lock(&forks[(id+1)%N]); //then right
        }

        //eating
        printf("Philosopher %d is eating...\n");
        sleep(2);

        //put chopsticks down
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id+1)%N]);

        printf("Philosopher %d has finished eating. \n", id);
        sleep(1);
    }
    return NULL;
}
int main(){
    pthread_t threads[N];
    int ids[N];

    //initialize all forks
    for(int i = 0; i<N; i++){
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    //join threads -- will form an infinite loop
    for(int i=0; i<N; i++){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}