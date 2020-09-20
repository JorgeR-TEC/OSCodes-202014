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
	int fileDescriptor=open("/mnt/c/Users/L03040561/Desktop/example.txt",  O_RDWR);
	char *text=(char *)mmap(NULL, sizeof(char)*20, PROT_READ , MAP_SHARED , fileDescriptor, 0);
	printf("Text from other process %s\n", text);
	munmap(text, sizeof(char)*20);
	close(fileDescriptor);
}