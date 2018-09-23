#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <pwd.h>
#include <termios.h>
#include <grp.h>
#include <stack>
#include <string>
#include <sys/ioctl.h>
#include <linux/limits.h>
#include <unordered_map>
#include <set>
#include <fstream>
#include "trackernewclient.h"
#define gotoxy(x,y) printf("%s%d%s%d%s","\033[",x,";",y,"H");
using namespace std;
vector <string> files;
unordered_map<string,string>lists;
fstream filepath;
void *requesting_client(void *arg);

struct thread_data
{
   int thread_id;
   int socket_id;
   string cport;
   string cip;
   string sha;
   string sport;
   string cport;
   
};


struct thread_datap
{
   int thread_id;
   
   string myport;
   string myip;
   
   
};
int k=0;

void *accept_peer_request(void *arg){

    struct thread_data *t;
    t = (struct thread_data *) arg;

    char buffer[1024];
    int server_fd, socket_created, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    }
    
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = inet_addr(t->myip); 
    address.sin_port = htons(stoi(t->myport));

    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    while(1){
        if (listen(server_fd, 3) < 0) 
        { 
            perror("listen"); 
            //logfile<<"Error in listen"<<endl;
            exit(EXIT_FAILURE); 
        } 
        //logfile<<"Waiting for the client to approach the tracker to make a connection"<<endl;
        if ((socket_created = accept(server_fd, (struct sockaddr *)&address,  
                           (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
             //logfile<<"Error in accepting connection request with the client"<<endl;
            exit(EXIT_FAILURE); 
        } 
        //logfile<<"Connection is established between client and server, and they are ready to transfer data"<<endl;
        int valread1= read( t->socket_id ,buffer, 1024 );
        cout<<"after read";
        cout<<" content received by peer: "valread1<<endl;

    }

       pthread_exit(NULL);    
}


void *requesting_client(void *arg){

    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024*1024] = {0}; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        c_logfile<<"error in socket creation"<<endl;
        return "-1"; 
    } 
    int opt=1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))) 
    { 
      perror("setsockopt"); 
      exit(EXIT_FAILURE); 
    } 
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(stoi(my_data->sport)); 
    serv_addr.sin_addr.s_addr = inet_addr(my_data->sip); 


    address.sin_family = AF_INET; 
    address.sin_port = htons(stoi(my_data->cport)); 
    address.sin_addr.s_addr = inet_addr(my_data->cip);
     if (bind(sock, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        c_logfile<<"Bind Failed!!"<<endl;
        exit(EXIT_FAILURE); 
    } 
     if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        c_logfile<<"Invalid Address"<<endl;
        return "-1"; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n");
        c_logfile<<"Connect Failed"<<endl; 
        return "-1"; 
    } 
    cout<<"sha to be sent by client in get command :"<<my_data->sha<<endl;
    send(sock,(const char*)(my_data->sha).c_str() , (my_data->sha).length() , 0 );

}

int main(int argc,char *argv[])
{   
    string local_file_path;
    string filename;
    string clientipport;
    string tracker1ipport;
    string tracker2ipport;
    string logfilename;
    string torrent_path;
    string destination;
    clientipport=argv[1];
    tracker1ipport=argv[2];
    tracker2ipport=argv[3];

     
     pthread_t ph;
     struct thread_datap p;
     int pc;
     k++;
     p.thread_id=k;
     
     p.myip=clientipport.substr(0,clientipport.find(":"));
     p.myport=clientipport(clientipport.find(":")+1,clientipport.length());
     pc = pthread_create(&th, NULL, thread_process, (void *)&t);
     //logfile<<"Thread "<<i<<" created"<<endl;
     if(pc){
           cout << "Error:unable to join," << pc<< endl;
           //logfile<<"Thread creation failed:unable to join"<<endl;
           exit(-1);
     }
     pthread_detach(ph);




    
    printf("\033[H\033[J");
    cout<<"\033["<<1<<";"<<1<<"H"<<"Command Mode :";
    gotoxy(1,15);
   
    //logfilename=argv[4];
    char buffer[100];
    char ch;
    int k=0;
    //while(1){cout<<"\n"<<"Command Mode :";
        do{
        cout<<"inside while"<<endl;
        ch=getchar();
        buffer[k++]=ch;
        buffer[k]='\0';

        }while(ch!='\n');
        //buffer[k]='\n';
        cout<<buffer;

        
        char file1[PATH_MAX];
        int i=0,j=0;
        do{
            
            if(buffer[i]!=' ' && buffer[i]!='\\'){
                file1[j]=buffer[i];
                //cout<<"file1:"<<file1[j]<<" buffer:"<<buffer[i]<<endl;
                j++;
                i++;
            }
            else if(buffer[i]=='\\' && buffer[i+1]==' '){
                i++;
                file1[j]=buffer[i];
                //cout<<"file1:"<<file1[j]<<" buffer: "<<buffer[i]<<endl;
                i++;    
                j++;
                
            }
            else if(buffer[i]==' '){
                file1[j]='\0';
                files.push_back(file1);
               // cout<<" file1: "<<file1;
                //cout<<" files current: "<<files.back();
                j=0;
                i++;
            }
            
        }while(buffer[i]!='\0');

        file1[j]='\0';
        files.push_back(file1);

        // for(int l=0;l<files.size();l++){
        //     cout<<files[l]<<endl;
        // }
        string sha1_of_sha1;

        string command=files[0];
        if(command=="share"){
            local_file_path=files[1];
            filename=files[2];
            
            sha1_of_sha1=client_program(local_file_path,filename,clientipport,tracker1ipport,tracker2ipport);
            cout<<"inside command mode showing the sha1_of_sh1: "<<sha1_of_sha1<<endl;
            lists[sha1_of_sha1]=local_file_path;
            unordered_map<string,string>:: iterator it;
            string x=sha1_of_sha1+"-"+lists[sha1_of_sha1];
            filepath.open("filepath.txt",fstream::out|fstream::app);
            filepath<<x<<endl;


            //CHECK WHAT MAP IS STORING--------------------------------->>>>>>>>>
            //cout<<"////////////////////////\n";
            //for(it=lists.begin();it!=lists.end();++it){
                //cout<<it->first<<"-->"<<it->second<<endl;

            //}
            //cout<<"////////////////////////\n";
            //do save this in a file also


        }
        if(command=="get"){
            torrent_path=files[1];
            destination=files[2];
            string s = getcommand(torrent_path,destination,clientipport);

            char delim[1];
            delim[0]='-';
            size_t pos = 0;
            string token;
            vector<string> ipp;
            string delimiter="-";
            int count=0;
            while((pos = s.find(delimiter))!=string::npos) {
                token = s.substr(0, pos);
                ipp.push_back(token);
                //cout << token << endl;
                count++;
                s.erase(0, pos + delimiter.length());
            }
            vector<string>::iterator vit;
            vector<string> ip;
            vector<string> port;
            int j=0;
            for(vit=ipp.begin();vit!=ipp.end();++vit){
                ip[j]=(*vit).substr(0,(*vit).find(":"));
                port[j]= (*vit).substr((*vit).find(":")+1,(*vit).length());
                j++;
            }
            //creation of thread:
             pthread_t th[count];
             struct thread_data t[count];
             int rc;
            for(int i=0;i<count;i++){
                 
                 
                 t[i].thread_id=i;
                 
                 t[i].sport=port[i];
                 t[i].sip=ip[i];
                 t[i].cport=clientipport.substr(0,clientipport.find(":"));
                 t[i].cip=clientipport(clientipport.find(":")+1,clientipport.length());
                 t[i].sha=sha1_of_sha1;

                 rc = pthread_create(&th[i], NULL, requesting_client, (void *)&t[i]);
                 //logfile<<"Thread "<<i<<" created"<<endl;
                 if(rc){
                       cout << "Error:unable to join," << rc << endl;
                       //logfile<<"Thread creation failed:unable to join"<<endl;
                       exit(-1);
                 }
                 pthread_detach(th);
            }

        }
     
       // memset(buffer,0,sizeof(buffer));
       // memset(&files,0,sizeof(files));
       // memset(&filename,0,sizeof(filename));
       // memset(&local_file_path,0,sizeof(local_file_path));
       // memset(&torrent_path,0,sizeof(torrent_path));
       // memset(&destination,0,sizeof(destination));
       // k=0;

    //}
    
    return 0;

}