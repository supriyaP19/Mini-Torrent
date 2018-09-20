#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <cstdlib>
#define PORT 8080 
#define SHA_DIGEST_LENGTH 10
#define chunks_length 512*1024
using namespace std;

string complete_sha1;
string complete_sha1_to_tracker;

int main() {
  //socket programming
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024*1024] = {0}; 

     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

//socket programming
    int i = 0;
    char buf[SHA_DIGEST_LENGTH*2];
    char ch[3];
   	int size;
    char file_read[1024]="VID-20131005-WA0003.mp4";
   	std::ifstream file (file_read, ios::in|ios::binary|ios::ate);

  	if (file.is_open())
  	{
  		printf("file opening\n");
	    size = file.tellg();
	    file.seekg(0, ios::beg);
	   
  	}
    
    char filen[100]="output.mtorrent";
    char ofile[100]="output.mtorrent";
    // char f[100]="output(";
    // char ext[100]=").txt";
    // struct stat b;
    // int flag=0;

    // if (stat(filen, &b) != -1)
    // {	
    //     flag=1;
    //     printf("existing");
        
    // }
    // int x=1;
    // if(flag==1){
    	
  		// //printf("file opening\n");
  		// strcat(f,(to_string(x)).c_str());
  		// strcat(f,ext);
  		// printf("the filename is %s\n",f);
  		
		 
    // }
    
  	string tracker1ipport="128.111.23.1:8080";
    string tracker2ipport="128.12.14.1:8000";
    complete_sha1=tracker1ipport+"\n"+tracker2ipport+"\n"+ofile+"\n"+to_string(size)+"\n";
    complete_sha1_to_tracker=complete_sha1_to_tracker+file_read+"\n";
  	FILE *fs;
  	fs =fopen(filen,"w");
    cout<<"o file name: "<<filen<<endl;
		 i=0;
  			while(chunks_length*(i+1)<size)
  			{	
  				
  				unsigned char temp[10];
  				char buff[chunks_length];
  				char buf[SHA_DIGEST_LENGTH];
  				file.read(buff,chunks_length);
  				file.seekg(chunks_length*(i+1),ios::beg);
	  			SHA1((unsigned char *)buff, chunks_length, temp);
	  			for (int j=0; j < SHA_DIGEST_LENGTH; j++) {
	  				
             //printf("%02x ",temp[j] );
              snprintf(ch,sizeof(ch),"%02x",temp[j]);
              complete_sha1=complete_sha1+ch;
              complete_sha1_to_tracker=complete_sha1_to_tracker+ch;
            
	    		}	
          complete_sha1=complete_sha1+"\n";
          complete_sha1_to_tracker=complete_sha1_to_tracker+"\n";
	    		i++;
	    		printf("\n");	
  			}
  			if(chunks_length*(i+1)>size){

  			 	int p =size-chunks_length*i;
        	char buf[SHA_DIGEST_LENGTH];
  				char buff2[p];
  				unsigned char temp[10];
  				file.read(buff2,p);
	  			SHA1((unsigned char *)buff2,p, temp);
	  			for (int j=0; j < SHA_DIGEST_LENGTH; j++) {

              //printf("%02x ",temp[j] );
              snprintf(ch,sizeof(ch),"%02x",temp[j]);
              complete_sha1=complete_sha1+ch;
              complete_sha1_to_tracker=complete_sha1_to_tracker+ch;
            
	        		
	    		}
          //complete_sha1=complete_sha1+"\n";


  			}
  			
  complete_sha1_to_tracker=complete_sha1_to_tracker+"\0";
  complete_sha1=complete_sha1+"\0";
  cout<<"\n"<<complete_sha1<<endl;
  fprintf(fs,"%s",complete_sha1.c_str());


  //length of mtorrent file
  int len=complete_sha1_to_tracker.length();
  //char msg[len];
  char msg2[1024];
  //reading output file and sending to client
 //  cout<<"output file name "<<ofile<<endl;
 //  cout<<"length "<<len<<endl;
 // std::ifstream mtorrentfd (ofile);
  // mtorrentfd << complete_sha1;
  // cout << complete_sha1;
  // int k=0;
  // while(!mtorrentfd.eof()){
  //     cout<<"inside "<<endl;
  //     mtorrentfd.read(msg,len);
  //     mtorrentfd.seekg(k+1,ios::beg);
  //     snprintf(msg2,len,"%s",msg[k]);
  //     k++;
  // }
 // strcpy(msg2,complete_sha1.c_str());

  send(sock , complete_sha1_to_tracker.c_str() , len , 0 ); 
  
  //valread = read( sock , msg2, strlen(msg2)); 
  
   
	file.close();
  return 0;
 
}