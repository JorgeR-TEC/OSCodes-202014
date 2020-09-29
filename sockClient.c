#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>



int main(){
    //Create a socket, obtaining the socket file descriptor
    int sock=socket(AF_INET, SOCK_STREAM, 0);
    //Setup the address that we want to connect to
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(80);
    inet_pton(AF_INET, "216.58.193.46", &addr.sin_addr);
    //Connecting to the address
    connect(sock,(struct sockaddr*)&addr, sizeof(addr));
    //read and write from the socket
    char *buffer=(char *)malloc(1000);
    strcpy(buffer, "GET / HTTP/1.1\r\n\r\n");
    write(sock, buffer, strlen(buffer));
    //send(sock, buffer, strlen(buffer), 0);
    read(sock, buffer, 1000);
    printf("%s\n", buffer);
    //close the socket
    close(sock);
    return 0;
}