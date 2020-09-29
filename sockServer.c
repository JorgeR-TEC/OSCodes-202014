#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
    //Create a socket
    int sock=socket(AF_INET, SOCK_STREAM, 0);
    //Setup the addresses
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(11809);
    addr.sin_addr.s_addr=INADDR_ANY;
    //Bind the socket to the address
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    //Listen for connections
    listen(sock, 1);
    //Accept the connect
    int conn=accept(sock,  NULL, NULL);
    //Read and write
    char *buffer=(char *)malloc(1000);
    read(conn, buffer, 1000);
  
    printf("%s\n", buffer);
    write(conn, "ok", strlen("ok")+1);
    
    //Close
    close(conn);
    close(sock);
    return 0;
}