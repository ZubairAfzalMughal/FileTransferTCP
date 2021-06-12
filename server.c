#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SIZE 1024

void write_file(int newsock){
    int n;
    char *fName="s_file.txt";
    FILE *fp;
    char buffer[SIZE];
    fp=fopen(fName,"w");

    if(fp==NULL){
        perror("Error in File creating from server");
        exit(1);
    }
    while(1){
        n=recv(newsock,buffer,SIZE,0);
        if(n==0){
            break;
            return;
        }
        fprintf(fp,"%s",buffer);
        bzero(buffer,SIZE);
    }
    return;
    
}

int main(){
    char *ip="127.0.0.1";
    int port=8000;
    // Socket Discriptors
    int sockfd, new_sock;
    int e;
    struct sockaddr_in server_addr, new_addr;

    socklen_t addr_size;
    char buffer[SIZE];

    //Creating a Socket

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    if(sockfd<0){
        perror("Error in socket");
        exit(1);
    }
    printf("Server Socket Created Successfully.\n");

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=port;
    server_addr.sin_addr.s_addr=inet_addr(ip);// Making adress to server

    // binding

    e=bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    
    if(e<0){
          perror("Error in binding");
          exit(1);
    }
    printf("Binding Created Successfully.\n");

    //Listen the port

    e=listen(sockfd,10);

    if(e==0){
        printf("Listening..........\n");
    }else{
        perror("Error in listening...");
        exit(1);
    }
    addr_size=sizeof(new_addr);
    new_sock=accept(sockfd,(struct sockaddr*)&new_addr,&addr_size);

    write_file(new_sock);
    printf("Data Written in File Successfully \n");

}