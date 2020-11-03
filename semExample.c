#include <stdio.h>
#include <pthread.h>

#define BUFFERSIZE 5
int buffer[BUFFERSIZE];
int count=0;
int in=0, out=0;
sem_t semaphore;

void *producer(void *arg){
    int i=0;
    while(i<100){
        while(count==BUFFERSIZE);//wait while the buffer is full
        sem_wait(&semaphore);
        buffer[in]=i;
        in=(in +1)%BUFFERSIZE;
        count++;
        i++;
        sem_post(&semaphore);
        
    }
}

void *consumer(void *arg){
    int i=0;
    while(i<100){
        while(count==0);//wait while the buffer is empty
        sem_wait(&semaphore);
        int num=buffer[out];
        out=(out+1)%BUFFERSIZE;
        count--;
        i++;
        sem_post(&semaphore);
        printf("%d\n", num);
    }
}

int main(){
    sem_init(&semaphore, 0, 1);
    pthread_t p,c;
    pthread_create(&c, NULL, consumer, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_join(c, NULL);
    pthread_join(p,NULL);
}