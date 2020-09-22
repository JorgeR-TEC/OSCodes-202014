#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1



int main(){
    int fileDescriptors[2];
    pipe(fileDescriptors);
    pid_t child=fork();
    if(child==0){
        char *dataSend="hello";
        close(fileDescriptors[READ]);
        write(fileDescriptors[WRITE], dataSend, strlen(dataSend)+1);
        close(fileDescriptors[WRITE]);
    }else{
        wait(NULL);
        char *dataRecv=(char *)malloc(sizeof(char)*100);
        close(fileDescriptors[WRITE]);
        read(fileDescriptors[READ], dataRecv, 100);
        close(fileDescriptors[READ]);
        printf("The parent received %s\n", dataRecv);
        free(dataRecv);
    }
    
    
    return 0;
}