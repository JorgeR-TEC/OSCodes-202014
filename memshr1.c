#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main(){
	//char *text=(char *)malloc(sizeof(char)*20);
	char *text=(char *)mmap(NULL, sizeof(char)*20, PROT_READ | PROT_WRITE , MAP_SHARED |MAP_ANONYMOUS , -1, 0);
	strcpy(text, "hello");
	pid_t child=fork();
	if(child==0){
		strcpy(text, "goodbye");
		printf("Text from the child %s\n", text);
	}else{
		wait(NULL);
		printf("Text from the parent %s\n", text);
	}
}

