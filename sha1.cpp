#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <fstream>
#include<iostream>
#define SHA_DIGEST_LENGTH 20
#define chunks_length 512*1024
using namespace std;

int main() {
 
    int i = 0;
    //unsigned char temp[SHA_DIGEST_LENGTH];
    char buf[SHA_DIGEST_LENGTH*2];
 
 	char *buffer;
 	int size;
    memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
   // memset(temp, 0x0, SHA_DIGEST_LENGTH);
 	char filename[100]="./file";
    std::ifstream file ("VID-20131005-WA0003.mp4", ios::in|ios::binary|ios::ate);
  	if (file.is_open())
  	{
  		printf("file opening\n");
	    size = file.tellg();
	    //printf("%d",size);
	    //buffer = new char [size];
	    file.seekg(0, ios::beg);
	   
  	}
  	else
  		return 0;
  	
  	std :: fstream fs;
  	// printf("size: %d",size);
  	// printf("inside code");
  	// for(int i=0;!file.eof();i++){
		 i=0;
  			while(chunks_length*(i+1)<size)
  			{
  				unsigned char temp[20];
  				char buff[chunks_length];
  				file.read(buff,chunks_length);
  				//cout<<"typeid:"<<typeid(buff[0]).name();
  				file.seekg(chunks_length*(i+1),ios::beg);
	  			// printf("read buff: %s",buff);
	  			SHA1((unsigned char *)buff, chunks_length, temp);
	  			// printf("%dgttgtthtyh",chunks_length);
	  			for (int j=0; j < SHA_DIGEST_LENGTH; j++) {
	        		//sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
	        		printf("%02x ", temp[j]);
	        		 // printf("helllooo\n");
	        		
	    		}
	    		i++;
	    		printf("\n");	
  			}
  			if(chunks_length*(i+1)>size){
  				// printf("jkkoo\n");
	        	int p =size-chunks_length*i;
	        	// printf("%d  %d\n",p,size);
  				char buff2[p];
  				// printf("jkkopppppppppppo\n");
  				unsigned char temp[20];
  				// printf("%d\n",size-chunks_length*i);
  				file.read(buff2,p);
  				//cout<<"typeid:"<<typeid(buff[0]).name();
  				// printf("jkkopppppppppppo\n");//file.seekg(chunks_length*(i+1),ios::beg);
	  			// printf("%s\n",buff);
	  			SHA1((unsigned char *)buff2,p, temp);
	  			for (int j=0; j < SHA_DIGEST_LENGTH; j++) {
	        		//sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
	        		printf("%02x ", temp[j]);
	        		// printf("\n");
	        		// printf("helllooo");
	    		}
  			}
  			
 


  	
    
 
   
    


     // file.read (memblock, size);
	    file.close();

	    // cout << "the complete file content is in memory";

	    // delete[] memblock;
 
    return 0;
 
}