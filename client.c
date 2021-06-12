#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define SIZE 1024

void send_file(FILE *fp, int sockfd){
    char data[SIZE]={0};

    while (fgets(data,SIZE,fp)!=NULL)
    {
       if(send(sockfd,data,sizeof(data),0)==-1){
           perror("Error in Sending");
           exit(1);
       }   
       bzero(data,SIZE);
    }
    
}
int main(){
    char *ip="127.0.0.1";
    int port=8000;
    // Socket Discriptors
    int sockfd;
    int e;
    struct sockaddr_in server_addr, new_addr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd<0){
        perror("Error in socket");
        exit(1);
    }
    printf("Server Socket Created Successfully.\n");

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=port;
    server_addr.sin_addr.s_addr=inet_addr(ip);// Making adress to server

    e=connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));

    if(e==-1){
        perror("Error in Connecting");
        exit(1);
    }
    printf("Connected to server \n");

    FILE *fp;

    char *fName="c_file.txt";

    fp=fopen(fName,"r");
    if(fp==NULL){
        perror("Error in File Opening");
        exit(1);
    }

    //Client is sending data to server

    send_file(fp,sockfd);
    printf("File sent successfully \n");
    close(sockfd);
    printf("Disconnecting with server \n");

}