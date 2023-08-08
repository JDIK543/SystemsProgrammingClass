/*
Jacob Dickson
Anthony Vuong
Entering "exit" will disconnect
On the final port in the lab, waiting 5 seconds and then entering anything other than exit will display the final message
*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char** argv){

    if(argc != 3){
        printf("[*]USAGE: %s <ipaddr> <port> \n",argv[0]);
        return 0;
    }


    printf("[*]Starting...\n");
    int port = atoi(argv[2]); //We get the port as text, so convert it to an integer with atoi (ascii to integer)
    int sock, addrlen, opt;

    struct sockaddr_in server; //make our sockaddr struct
    sock = socket(AF_INET,SOCK_STREAM,0);//AF_Inet - addresses are in ipv4 format | SOCK_STREAM -> connected, Stream based (TCP) | 0 corresponds to the IP protocol (see man socket)
    server.sin_family = AF_INET; //server's address will be in ipv4
    server.sin_port = htons(port); // convert local machine port representation (little endian most likely) to network representation (Big endian)

    //Next we convert our text based ipv4 address into one that the struct needs (binary)
    if(inet_pton(AF_INET,argv[1],&server.sin_addr) <=0){
        printf("[!]Error processing IP address\n");
        return 1;
    }
    //Connect to server
    if(connect(sock,(struct sockaddr *) &server, sizeof(server))){
        printf("[!]Connection to file server failed\n");
        return 1;
    }
    char buf[4096];
    char key[] = "roux";
    int readCount;
    int isRunning = 2;
    do{
        printf("[*]Begin Message!\n");
        do{
            readCount = recv(sock,buf, 32, 0);
            buf[readCount +1] = '\0';
        //printf("%s",buf);
            if(port == 24194){
                for (int i = 0; i < readCount; i++){
                    printf("%c", buf[i]^key[i%4]);
                }
            }
            else{
                printf("%s", buf);
            }
        } while(readCount == 32);
        printf("\n");
        
        fgets(buf,1024,stdin);
        int len = strlen(buf);
        int sentC;
        //printf("%s", buf);
        if(!strcmp(buf, "exit\n")){
            isRunning = 0;
        }
        else{
            if(port == 24194){
                for(int i = 0; i < len; i++){
                    buf[i] = buf[i]^key[i%4];
                }
            }
            //send data to server
            //return value from send is how many bytes actually sent
            if((sentC = send(sock,buf,len,0)) < len){
                printf("[!]Message not fully sent!\n");
            }
            printf("[*]Message sent! Sent %d bytes!\n",sentC);
        }
        
    } while(isRunning);

    printf("<---------END--------->\n");

    close(sock);
    return 0;
}