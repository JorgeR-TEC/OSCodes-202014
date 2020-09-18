#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
	int a=5;
	char *c=(char *)malloc(20);
	c="hello";
	pid_t own=getpid();
	pid_t parent=getppid();
	printf("Before fork, My process id is %d, and my parent's id is %d\n", own, parent);
	pid_t child=fork();
	if(child==0){
		//child
		own=getpid();
		parent=getppid();
		printf("My process id is %d, and my parent's id is %d, and my child is %d\n", own, parent, child);
		char *params[2]={"ps", NULL};
		//execvp("ps", params);
		execlp("ls", "ls", "|", "grep", "cpp", NULL);
		//printf("From the child: %s\n", c);
	}else{
		//parent
		wait(NULL);
		own=getpid();
		parent=getppid();
		printf("My process id is %d, and my parent's id is %d, and my child is %d\n", own, parent, child);
		
		//printf("From the parent: %s\n",c);
	}
	return 0;
}