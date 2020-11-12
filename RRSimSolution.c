#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define FULLCOUNT 5

int count=0;
_Atomic int pid=0;
pthread_mutex_t queueLock;
sem_t full, empty;
typedef struct Processes{
	int id;
	int remainingTime;
	struct Processes *next;
} Process;

Process *front;

Process *createProcess(int id, int remainingTime){
	Process *toAdd=(Process *)malloc(sizeof(Process));
	toAdd->id=id;
	toAdd->remainingTime=remainingTime;
	toAdd->next=NULL;
	return toAdd;
}
void enqueue(Process *toAdd){
	pthread_mutex_lock(&queueLock);
	if(front==NULL){
		front=toAdd;
	}else{
		Process *temp=front;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=toAdd;
	}
	count++;
	pthread_mutex_unlock(&queueLock);
}

Process *dequeue(){
	pthread_mutex_lock(&queueLock);
	Process *toReturn=front;
	front=front->next;
	count--;
	toReturn->next=NULL;
	pthread_mutex_unlock(&queueLock);
	return toReturn;
}

void printQueue(){
	Process *temp=front;
	printf("Total:%d;", count);
	while(temp!=NULL){
			printf("id:%d,rT:%d;",temp->id, temp->remainingTime);
			temp=temp->next;
	}
	printf("\n");
}

void *user(void *args){//producer
	int id=*(int *)args;
	int processesToCreate=(rand()%10)+5;
	for(int i=0; i<processesToCreate; i++){
		sem_wait(&empty);//decrease the value of empty
        int rTime=rand()%30;
        int currentPid=pid++;
        printf("User %d: created process %d with burst %d\n",id, currentPid, rTime);
        enqueue(createProcess(currentPid, rTime));
        sem_post(&full);//increase the value of full
    }
}

void *cpu(void *args){//consumer
	int id=*(int *)args;
	int quantum=4;
	int counterNoProc=0;
	while(1){
		//sem_wait(&full);
		int result=sem_trywait(&full);
		if(result==-1){
			counterNoProc++;
			if(counterNoProc==3){
				printf("Ready queue empty 3 times for CPU %d. Exiting\n", id);
				break;
			}
			printf("CPU %d did not found a process in the queue. Sleeping 5 seconds.\n",id);
			sleep(5);
			continue;
		}else{
			counterNoProc=0;
		}//semaphore cannot be decrease, there is no process in the queue.
	    Process *p=dequeue();
	    
	    printf("CPU %d is loading process %d\n",id, p->id);
	    int i;
	    for(i=0; i<quantum; i++){
	        p->remainingTime--;
	        if(p->remainingTime==0){
	            break;
	        }else if(rand()%100<10){
	            break;
	        }
	    }
	    if(p->remainingTime<=0){
	        printf("Process %d finished\n", p->id);
	        sem_post(&empty);
	    }else{ 
	        if(i<quantum){
	            printf("Process %d preempted due I/O with remaining time %d\n", p->id, p->remainingTime);
    	    }else{
    	        printf("Process %d preempted with remaining time %d\n", p->id, p->remainingTime);
    	    }
			
    	    enqueue(p);
    	    sem_post(&full);
			
	    }
	}
}




int main(){
	pthread_t user1, cpu1, user2, cpu2;
	pthread_mutex_init(&queueLock,NULL);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, FULLCOUNT);
	int id1=1; 
	int id2=2;
	pthread_create(&user1, NULL, user, (void *)&id1);
	pthread_create(&user2, NULL, user, (void *)&id2);
	pthread_create(&cpu1, NULL, cpu, (void *)&id1);
	pthread_create(&cpu2, NULL, cpu, (void *)&id2);
	pthread_join(user1, NULL);
	pthread_join(user2, NULL);
	pthread_join(cpu1, NULL);
	pthread_join(cpu2, NULL);
	return 0;
}