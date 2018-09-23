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
#include <unordered_map>
#include <fstream>
#include <set>
#define PORT 8080
using namespace std; 

int i=0;
fstream f;
string seederlist_file="seeder_list.txt";
ofstream logfile;
void *getcommand(void *threadarg);
void *thread_process(void *arg);


//string seeder="seeder_list.txt";
unordered_map<string, set<string>> seederlist;

struct thread_data {
   int thread_id;
   int socket_id;
   string seed;
};
struct thread_data1 {
   int thread_id1;
   int socket_id1;
   string seed1;
};

void *thread_process(void *arg) {

    set<string>::iterator setitr;
    unordered_map<string, set<string>>::iterator mapitr;
    char buffer[1024*1024] = {0}; 
    char ipport[21];
    char command[20];
    struct thread_data *t;
    t = (struct thread_data *) arg;
    int valread0 = read(  t->socket_id ,command,20 );
    //cout<<"inside thread and command is :"<<command<<endl;
    string clients;
    if(command[0]=='1'){

      int valread1= read( t->socket_id ,buffer, 40 );
      //cout<<"in get command thread and sha1 is: "<<buffer<<endl;
      mapitr = seederlist.find(buffer);

      if(mapitr!=seederlist.end()){
        cout<<"found"<<endl;
            for(setitr=(mapitr->second).begin();setitr!=(mapitr->second).end();++setitr){
               
               clients=clients+(*setitr)+"\n";

            }
      }
      clients[clients.length()-1]='\0';
      cout<<clients<<endl;

      memset(buffer,0,sizeof(buffer));
      send(t->socket_id , (const char*)clients.c_str(),clients.length(),0);
    }
    else if(command[0]=='2'){
       int valread = read( t->socket_id , buffer, 40);
       //cout<<t->seed<<"here"<<endl;
       char buffer2[40];
       strcpy(buffer2,buffer);
       char seed[57];
       char delimeter[1];
       delimeter[0]='-';
       cout<<"buffer before "<<buffer<<endl;
       
       strcat(buffer,delimeter);
       buffer[41]='\0';
       cout<<"buffe now "<<buffer<<endl;  
       // strcat(buffer2,ipport);
       //    cout<<"buffer2 "<<buffer2<<endl;
        printf("seeder lst:%s\n",buffer);
        sleep(1);
        //f.open()
        int valread1 = read( t->socket_id , ipport, 16); 
        strcat(buffer,ipport);
        
        cout<<"After concatenating ipport: "<<buffer<<endl;
        ofstream fs;
        fs.open(t->seed,std::fstream::out|std::fstream::app);
        fs<<buffer<<endl;
        logfile<<"writing in seeder_list file"<<endl;
        printf("ipport: %s\n",ipport);
        printf("sha1: %s\n",buffer); 
       
       //printf("===============================\n");

       

        mapitr = seederlist.find(buffer);
        if(mapitr!=seederlist.end()){
            (mapitr->second).insert(ipport);
        }
        else{
            set<string> ip;
            ip.insert(ipport);
            seederlist[buffer]=ip;
        }

        logfile<<"adding the data in the map data structure"<<endl;
       

        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));
        memset(ipport, 0, sizeof(ipport));
        logfile<<"buffer cleared"<<endl;

        printf("thread id %d\n",t->thread_id);

    }
    memset(command,0,sizeof(command));

   pthread_exit(NULL);
}


int main(int argc, char const *argv[]) 
{ 
    //read seerlist file and add in the map------------------------------------
    //f.open(seeder.c_str(),ios::ate);
    set<string>::iterator setitr;
    unordered_map<string, set<string>>::iterator mapitr;
    string line="";
    string sha1="";
    string ipport="";
    string fil(argv[3]);
    cout<<"fil "<<fil<<endl;
    f.open(fil,ios::in);
    int size = f.tellg();
    //f<<"supriya"<<endl;
    cout<<"size: "<<size<<endl;
    while(getline(f, line)) {
      //cout<<"gggggggggg";
      sha1=line.substr(0,line.find('-'));
      int i=line.find_last_of("-");
      ipport=line.substr(i+1);

      mapitr = seederlist.find(sha1);
      if(mapitr!=seederlist.end()){
          (mapitr->second).insert(ipport);
      }
      else{
          set<string> ip;
          ip.insert(ipport);
          seederlist[sha1]=ip;
      }

    }
    // cout<<"============================================================DS content\n";
    // for(mapitr=seederlist.begin();mapitr!=seederlist.end();++mapitr){
    //     cout<<"size"<<(mapitr->first).size()<<endl;
    //     cout<<mapitr->first<<"->";
    //     for(setitr=(mapitr->second).begin();setitr!=(mapitr->second).end();++setitr){
    //         cout<<*setitr<<endl;
    //     }
    //     cout<<endl;
    // }
    // cout<<"============================================================DS content\n";

    //-------------------------------------------------------------------------

    int server_fd, socket_created, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 

    //opening log file to stor the logs
    string log_file(argv[4]);
    logfile.open(log_file,ofstream::app);    
    if(logfile.is_open()){
      cout<<"correct";
    }
    logfile<<"*******************************************************"<<endl;
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    logfile<<"tracker socket created"<<endl;
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
    logfile<<"binding the socket to the address and port number"<<endl;

    
    while(1){
        if (listen(server_fd, 3) < 0) 
        { 
            perror("listen"); 
            logfile<<"Error in listen"<<endl;
            exit(EXIT_FAILURE); 
        } 
        logfile<<"Waiting for the client to approach the tracker to make a connection"<<endl;
        if ((socket_created = accept(server_fd, (struct sockaddr *)&address,  
                           (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
             logfile<<"Error in accepting connection request with the client"<<endl;
            exit(EXIT_FAILURE); 
        } 
        logfile<<"Connection is established between client and server, and they are ready to transfer data"<<endl;
       //char command[10];
       //int valread = read(socket_created , command, 1);
       //logfile<<"command received : "<<command;
       //sleep(1);
      
   
       
     
         pthread_t th;
         struct thread_data t;
         int rc;
         i++;
         t.thread_id=i;
         t.socket_id=socket_created;
         t.seed=fil;
         rc = pthread_create(&th, NULL, thread_process, (void *)&t);
         logfile<<"Thread "<<i<<" created"<<endl;
         if(rc){
               cout << "Error:unable to join," << rc << endl;
               logfile<<"Thread creation failed:unable to join"<<endl;
               exit(-1);
          }
          pthread_detach(th);
          logfile<<"thread "<<i<<" detached"<<endl;
       
     
    }
    
   
    return 0; 
}