#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct arguments{
    int i;
    int j;
} numbers;

void *function(void *arg){
    numbers *value=(numbers *)arg;
    printf("i: %d, j: %d\n",value->i, value->j);
}


int main(){
    printf("Hello from main\n");
    /*int a=3;
    int *b=(int *)malloc(sizeof(int));
    *b=2;
    pthread_t tid1, tid2;
    pthread_create(&tid2, NULL, function, (void *)b);
    pthread_create(&tid1, NULL, function, (void *)&a);*/
    pthread_t tid1;
    numbers *args=(numbers *)malloc(sizeof(numbers));
    args->i=1;
    args->j=2;
    pthread_create(&tid1, NULL, function, (void *)args);
    pthread_join(tid1, NULL);
    //pthread_join(tid2, NULL);
    /*
    pthread_create(//function to create a thread
        pthread_t *thread,//thread id
        const pthread_attr_t *attr,//attributes of the thread
        void *(*start_routine) (void *),//function
        
        void *arg);//arguments of the function
    function();
    */
    return 0;
}