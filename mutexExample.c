#include <stdio.h>
#include <pthread.h>

#define BUFFERSIZE 5
int buffer[BUFFERSIZE];
int count=0;
int in=0, out=0;
pthread_mutex_t lock;

void *producer(void *arg){
    int i=0;
    while(i<100){
      
        while(count==BUFFERSIZE);//wait while the buffer is full
        pthread_mutex_lock(&lock);
        buffer[in]=i;
        in=(in +1)%BUFFERSIZE;
        count++;
        i++;
        pthread_mutex_unlock(&lock);
        
    }
}

void *consumer(void *arg){
    int i=0;
    while(i<100){
        while(count==0);//wait while the buffer is empty
        pthread_mutex_lock(&lock);
        int num=buffer[out];
        out=(out+1)%BUFFERSIZE;
        count--;
        i++;
        pthread_mutex_unlock(&lock);
        printf("%d\n", num);
        
    }
}

int main(){
    pthread_mutex_init(&lock, NULL);
    pthread_t p,c;
    pthread_create(&c, NULL, consumer, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_join(c, NULL);
    pthread_join(p,NULL);
}