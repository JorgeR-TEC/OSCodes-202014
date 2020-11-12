#include <stdio.h>
#include <pthread.h>
#define PROD 0
#define CONS 1
#define BUFFERSIZE 5
int buffer[BUFFERSIZE];
int count=0;
int in=0, out=0;
int turn=0;
int ready[2]={0,0};

void *producer(void *arg){
    int i=0;
    while(i<100){
        while(count==BUFFERSIZE);//wait while the buffer is full
        turn=CONS;//give the turn to blue
        ready[PROD]=1;//set green to ready
        while(ready[CONS]&&turn==CONS);//while blue is in the CS
        buffer[in]=i;
        count++;
        ready[PROD]=0;//green is not ready
        in=(in +1)%BUFFERSIZE;
      
        i++;
    }
}

void *consumer(void *arg){
    int i=0;
    while(i<100){
        while(count==0);//wait while the buffer is empty
        turn=PROD;//green's turn
        ready[CONS]=1;
        while(ready[PROD]&& turn==PROD);
        int num=buffer[out];
        count--;
        ready[CONS]=0;
        out=(out+1)%BUFFERSIZE;
        
        i++;
        printf("%d\n", num);
    }
}

int main(){
    pthread_t p,c;
    pthread_create(&c, NULL, consumer, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_join(c, NULL);
    pthread_join(p,NULL);
}