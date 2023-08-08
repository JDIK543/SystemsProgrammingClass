#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define READCOUNT 1024

int main(int argc, char** argv){  
    if (argc != 2)
    {
        printf("[*]USAGE: %s <local port>\n",argv[0]);
        return 0;
    }

    printf("[*]Starting...\n");
    int port = atoi(argv[1]); //convert ascii text representation of port number to integer
    int listen_fd, sock_fd, addrlen, opt;

    struct sockaddr_in addr; //For IP addressin we need the sockaddr_in struct
    addrlen = sizeof(addr); //For function calls we also need the size of the addr struct
    listen_fd = socket(AF_INET,SOCK_STREAM,0);//AF_Inet - addresses are in ipv4 format | SOCK_STREAM -> connected, Stream based (TCP) | 0 corresponds to the IP protocol (see man socket)
    if(!listen_fd){
        printf("[!]Error creating socket. Exiting...\n");
        return 1;
    }
    printf("[*]Socket created...\n");
    //SOL_SOCKET indicates we are setting an option at the socket API level
    //Sets REUSEADDR option, useful for when we bind a socket & listen for connections
    if(setsockopt(listen_fd,SOL_SOCKET, SO_REUSEADDR,&opt,sizeof(opt))){
        printf("[!]Error creating socket. Exiting...\n");
        return 1;
    }
    printf("[*]Options set...\n");
    //Set up addr struct
    addr.sin_family = AF_INET; //Use IPv4 address scheme
    addr.sin_addr.s_addr = INADDR_ANY; //Any address, since we are listening for outside connections
    addr.sin_port = htons(port); //convert port to network byte order

    //binds our socket, registering that we want to use the port in the sockaddr struct
    if(bind(listen_fd, (struct sockaddr *) &addr, (socklen_t ) addrlen) < 0){
        printf("[!]Failure binding socket. Exiting...\n");
        return 1;
    }
    printf("[*]Socket bound...\n");
    //now we wait for connections. the second argument to listen (4) is how many connection requests to backlog before rejecting new ones
    if(listen(listen_fd,4) < 0){
        printf("[!]Unable to listen to socket. Exiting...\n");
        return 1;
    }
    printf("[*]Socket listening on port %d\n",port);
    //Accept the connection. Note that this will block (wait) if there is no connections pending
    sock_fd = accept(listen_fd,(struct sockaddr *)&addr, (socklen_t*)&addrlen);
    printf("[*]Socket Accepted!\n");

    if(sock_fd <= 0){
        printf("[!]Error creating socket from accept!\n");
        close(listen_fd);
        return 1;
    }
    
    char * buf = (char * ) malloc(sizeof(char) * 1024);
    if (buf == NULL){
        printf("[!]Error allocating message buffer!\n");
        close(listen_fd);
        return 1;
    }
    //After accepting a connection, we can read from it using recv, much like a file
    int readCount;
    printf("[*]Begin Message!\n");
    do{
        readCount = recv(sock_fd,buf, READCOUNT, 0);
        buf[1023] = '\0';
        printf("%s",buf);
    } while(readCount == READCOUNT);
    printf("<---------END--------->\n");

    char* goodbyeMessage = "Gooooooooodbye!\n";
    

    if(send(sock_fd,goodbyeMessage,strlen(goodbyeMessage),0) < strlen(goodbyeMessage)){
        printf("[!]Error sending goodbye!\n");
    }
    printf("[*]Sent goodbye!\n");
    close(sock_fd);

    printf("[*]Ending now!\n");


}