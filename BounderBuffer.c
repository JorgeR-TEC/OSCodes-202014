#include <stdio.h>
#include <pthread.h>

#define BUFFERSIZE 5
int buffer[BUFFERSIZE];
int in=0, out=0;
pthread_mutex_t lock;
sem_t full, empty;

void *producer(void *arg){
    int i=0;
    while(i<100){
        sem_wait(&empty);
        pthread_mutex_lock(&lock);
        buffer[in]=i;
        in=(in +1)%BUFFERSIZE;
        i++;
        pthread_mutex_unlock(&lock);
        sem_post(&full);
    }
}

void *consumer(void *arg){
    int i=0;
    while(i<100){
        sem_wait(&full);
        pthread_mutex_lock(&lock);
        int num=buffer[out];
        out=(out+1)%BUFFERSIZE;
        count--;
        i++;
        pthread_mutex_unlock(&lock);
        sem_post(&empty);
        printf("%d\n", num);
    }
}

int main(){
    pthread_mutex_init(&lock, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFERSIZE);
    pthread_t p,c;
    pthread_create(&c, NULL, consumer, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_join(c, NULL);
    pthread_join(p,NULL);
}