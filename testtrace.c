#include <stdio.h>
#include <signal.h>

void handler(int signum){
	if(signum==SIGINT){
		printf("Hey, dont try to kill me\n");
	}else if(signum==SIGTERM){
		printf("HA,i am immortal\n");
	}else if(signum==SIGKILL){
		printf("No!!!\n");
	}
	fflush(NULL);
}

int main(){
	signal(SIGINT, handler);
	signal(SIGTERM, handler);
	signal(SIGKILL, handler);
	printf("hello world\n");
	while(1){
	}
}