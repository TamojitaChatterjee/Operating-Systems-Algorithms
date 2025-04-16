//creating threads using pthread
#include<stdio.h>
#include<pthread.h>

void* myThread(void* arg){
    printf("Hello from the thread\n");
    return NULL;
}

int main(){
    pthread_t thread;

    pthread_create(&thread, NULL, myThread, NULL);
    pthread_join(thread, NULL);

    printf("Thread finished. Back to main\n");
    return 0;
}