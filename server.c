#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SA struct sockaddr
#define LISTENQ 5
// using namespace std;

int main(int argc,char**argv)
{
int fd,sockfd,listenfd,connfd;
pid_t childpid;
socklen_t client;
struct sockaddr_in servaddr,cliaddr;
listenfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(atoi(argv[1]));
bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
listen(listenfd,LISTENQ);
client=sizeof(cliaddr);


connfd=accept(listenfd,(SA*)&cliaddr,&client);
char buffer[256];
FILE *fp;
// read(connfd,buffer,256);
// //  string filename,word;
// // filename="add1.txt";
// fp=fopen("a1.out","ab");
// // while(filename>>word){
// //     cout<<word<<endl;
// // }
// // for(int i=0;i<4;i++){
   
// // }

// fprintf(fp,"%s",buffer);
  while(1)
    {		
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);

        /* Open the file that we wish to transfer */
        FILE *fp = fopen("a.out","rb");
        if(fp==NULL)
        {
            printf("File opern error");
            return 1;   
        }   

        /* Read data from file and send it */
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            printf("Bytes read %d \n", nread);        
            // printf("%s\n",buff );
            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(connfd, buff, nread);
                printf(buff);
            }

            /*
             * There is something tricky going on with read .. 
             * Either there was error, or we reached end of file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }


        }

        close(connfd);
        sleep(1);
    }

// printf("the file was received successfully");
// printf("the new file created is add1.txt");
}