#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	//char *text=(char *)malloc(sizeof(char)*20);
	int fileDescriptor=open("/mnt/c/Users/L03040561/Desktop/example.txt", O_CREAT | O_RDWR);
	ftruncate(fileDescriptor, sizeof(char)*20);
	char *text=(char *)mmap(NULL, sizeof(char)*20, PROT_READ | PROT_WRITE , MAP_SHARED, fileDescriptor, 0);
	strcpy(text, "hello world");
	printf("Text from one process %s\n", text);

}