#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#define SA struct sockaddr
int main(int argc,char**argv)
{
int sockfd,bytes=0;
char fname[25];
int len;
struct sockaddr_in servaddr,cliaddr;
sockfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(atoi(argv[1]));
inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
char buffer[1025];
FILE *f;
f=fopen("a.out","ab");
long flen;
fseek(f, 0, SEEK_END);          
flen = ftell(f);            
rewind(f);                      
    /* Receive data in chunks of 256 bytes */
while((bytes = read(sockfd, buffer, 256)) > 0)
{
    printf("Bytes received %d\n",bytes);    
    // recvBuff[n] = 0;
    fwrite(buffer, 1,bytes,f);
    printf(buffer);
    // printf("%s \n", recvBuff);
}


// fread(*&buffer, 256, 1, f);
// // printf("================");
// // fread(*&buffer, 1, 1, f);
// printf("%s",buffer);

// // write(sockfd,buffer,256);
// printf("the file was sent successfully");
}