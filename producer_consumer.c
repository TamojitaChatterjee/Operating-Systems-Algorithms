//producer-consumer using semaphores
/*
The basic logic is:
- producer adds information to the buffer
- consumer reads information from the buffer
- semaphores ensure that producer and consumer are not operating together
*/

#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

#define SIZE 5 //size of buffer

int buffer[SIZE]; //shared buffer
int in = 0; //index where producer will add
int out = 0; //index where consumer will remove

sem_t empty; //counts empty slots
sem_t full; //counts filled slots
pthread_mutex_t mutex; //to protect shared buffer

void* producer(void* arg){
    int item = 1;
    
    while(1){
        sem_wait(&empty); //wait if buffer is full
        pthread_mutex_lock(&mutex); //lock the buffer

        buffer[in] = item; //produce item
        printf("Produced: %d\n", item);
        in = (in +1) % SIZE;
        item++ ;

        pthread_mutex_unlock(&mutex); //unlock buffer
        sem_post(&full); //signal item added
        sleep(1); //stimulate delay
    }
}

void* consumer(void* arg){
    while(1){
        sem_wait(&full); //wait if buffer is empty
        pthread_mutex_lock(&mutex); //lock the buffer

        int item = buffer[out]; //consume item
        printf("Consumed: %d\n", item);
        out = (out+1) % SIZE;

        pthread_mutex_unlock(&mutex); //unlock buffer
        sem_post(empty); //signal item removed
        sleep(1); //delay
    }
}

int main(){
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE); //all slots are empty
    sem_init(&full, 0, 0); //no items to consume yet
    pthread_mutex_init(&mutex, NULL); //init mutex

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}