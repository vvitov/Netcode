#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet>

#define MAXLINE 100
int main(int argc, char **argv)
{
    //initialized sockets
    int sockfd,n;
    //holds character buffer
    char recvline[MAXLINE + 1];
    //instanciates the sockaddr
    struct sockaddr_in servaddr;
    if(argc!=2)
     {
        printf("usage:a.out <IPaddress>");
        return -1;
     }
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
         err_sys("socket error");

    //clear the memory for the serva initialization
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    if(inet_pton(AF_INET_INET,argv[1],&servaddr.sin_addr)<=0)
          err_sys("connect error");
    while((n=read(sockfd,recvline,MAXLINE))>0)
    {
         recvline[n] = 0;
         if(fputs(recvline,stdout)==EOF)
              err_sys("fputs error");
    }
    if(n<0)
       err_sys("read error");
}