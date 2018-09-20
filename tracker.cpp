// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pthread.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#define PORT 8080
using namespace std; 
int i=0;

struct thread_data {
   int thread_id;
   int socket_id;
};

void *thread_process(void *arg) {
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
    struct thread_data *t;
    t = (struct thread_data *) arg;
    int valread = read( t->socket_id , buffer, 1024); 
    printf("%s\n",buffer ); 
    //send(t->socket_id , hello , strlen(hello) , 0 ); 
    //printf("Hello message sent\n");
    printf("thread id %d\n",t->thread_id);
    sleep(5);
    printf("sleep over");
   // cout << "Thread ID : " << t->thread_id ;
   // cout << " Message : " << t->socket_id << endl;

   pthread_exit(NULL);
}

int main(int argc, char const *argv[]) 
{ 
    int server_fd, socket_created, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
   // char buffer[1024] = {0}; 
    
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    
    while(1){
        if (listen(server_fd, 3) < 0) 
        { 
            perror("listen"); 
            exit(EXIT_FAILURE); 
        } 
        if ((socket_created = accept(server_fd, (struct sockaddr *)&address,  
                           (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
       pthread_t th;
       struct thread_data t;
       int rc;
       i++;
       t.thread_id=i;
       t.socket_id=socket_created;

       rc = pthread_create(&th, NULL, thread_process, (void *)&t);

       if(rc){
             cout << "Error:unable to join," << rc << endl;
             exit(-1);
        }
        pthread_detach(th);
       //i++;
        cout<<"returned";
    }
    
   
    return 0; 
}