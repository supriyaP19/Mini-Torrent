#include "trackernewclient.h"

int client_program(string file_read_str,string filen_str) {
  //socket programming
    string complete_sha1;
    string complete_sha1_to_tracker;

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
    char buf[10];
    char ch[3];
   	int size;

   	std::ifstream file (file_read_str.c_str(), ios::in|ios::binary|ios::ate);

  	if (file.is_open())
  	{
	    size = file.tellg();
	    file.seekg(0, ios::beg); 
	   
  	}

    string clientipport="127.0.0.1:8001";
  	string tracker1ipport="128.111.23.1:8080";
    string tracker2ipport="128.12.14.1:8000";
    complete_sha1=tracker1ipport+"\n"+tracker2ipport+"\n"+filen_str.c_str()+"\n"+to_string(size)+"\n";
  	FILE *fs;
  	fs =fopen(filen_str.c_str(),"w");
		 i=0;
  			while(chunks_length*(i+1)<size)
  			{	
  				
  				unsigned char temp[10];
  				char buff[chunks_length];
  				char buf[10];
  				file.read(buff,chunks_length);
  				file.seekg(chunks_length*(i+1),ios::beg);
	  			SHA1((unsigned char *)buff, chunks_length, temp);
	  			for (int j=0; j < 10; j++) {
	  				
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
        	char buf[10];
  				char buff2[p];
  				unsigned char temp[10];
  				file.read(buff2,p);
	  			SHA1((unsigned char *)buff2,p, temp);
	  			for (int j=0; j < 10; j++) {

              snprintf(ch,sizeof(ch),"%02x",temp[j]);
              complete_sha1=complete_sha1+ch;
              complete_sha1_to_tracker=complete_sha1_to_tracker+ch;
            
	        		
	    		}


  			}
  			
  complete_sha1_to_tracker=complete_sha1_to_tracker+"\0";
  complete_sha1=complete_sha1+"\0";
  cout<<"\n"<<complete_sha1<<endl;
  fprintf(fs,"%s",complete_sha1.c_str());

  //doing hash of the generated sha1 to send to tracker
  string sha1_of_sha1;
  char temp_string[complete_sha1_to_tracker.length()];
  char ch1[3];
  SHA1((unsigned char *)complete_sha1_to_tracker.c_str(),complete_sha1_to_tracker.length(),(unsigned char *)temp_string);
  for (int h=0; h < 20; h++) {

              snprintf(ch1,sizeof(ch1),"%02x",temp_string[h]);
              sha1_of_sha1=sha1_of_sha1+ch1+" ";
            
              
    }
    int len=sha1_of_sha1.length();
    char msg2[1024];
    
    send(sock , clientipport.c_str(),clientipport.length(),0); 
    send(sock , sha1_of_sha1.c_str() , len , 0 );
  
   
	file.close();
  return 0;
 
}