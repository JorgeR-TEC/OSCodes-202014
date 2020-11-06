#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int count=0;
_Atomic int pid=0;
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
}

Process *dequeue(){
	Process *toReturn=front;
	front=front->next;
	count--;
	toReturn->next=NULL;
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
        int rTime=rand()%30;
        int currentPid=pid++;
        printf("User %d: created process %d with burst %d\n",id, currentPid, rTime);
        enqueue(createProcess(currentPid, rTime));
    }
}

void *cpu(void *args){//consumer
	int id=*(int *)args;
	int quantum=4;
	while(count>0){
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
	    if(p->remainingTime==0){
	        printf("Process %d finished\n", p->id);
	    }else{ 
	        if(i<quantum){
	            printf("Process %d preempted due I/O with remaining time %d\n", p->id, p->remainingTime);
    	    }else{
    	        printf("Process %d preempted with remaining time %d\n", p->id, p->remainingTime);
    	    }
    	    enqueue(p);
	    }
	}
}




int main(){
   
	pthread_t user1, cpu1;
	int id1=1; 
	int id2=2;
	pthread_create(&user1, NULL, user, (void *)&id1);
	pthread_join(user1, NULL);
	pthread_create(&cpu1, NULL, cpu, (void *)&id1);
	pthread_join(cpu1, NULL);
	return 0;
}