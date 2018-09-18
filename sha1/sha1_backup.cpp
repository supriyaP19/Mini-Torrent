#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <fstream>
#include<iostream>
#include <sys/stat.h>
#define SHA_DIGEST_LENGTH 20
#define chunks_length 512*1024
using namespace std;

int main() {
 
    int i = 0;
    //unsigned char temp[SHA_DIGEST_LENGTH];
    char buf[SHA_DIGEST_LENGTH*2];
 
  char *buffer;
  int size;
    //memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
  std::ifstream file ("VID-20131005-WA0003.mp4", ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
      printf("file opening\n");
      size = file.tellg();
      //printf("%d",size);
      //buffer = new char [size];
      file.seekg(0, ios::beg);
     
    }
    
    char filen[100]="output.txt";
    char f[100]="output(";
    char ext[100]=").txt";
    struct stat b;
    int flag=0;

    if (stat(filen, &b) != -1)
    { 
        flag=1;
        printf("existing");
        
    }
    int x=1;
    if(flag==1){
      
      //printf("file opening\n");
      strcat(f,(to_string(x)).c_str());
      strcat(f,ext);
      printf("%s\n",f);
      
     
    }
   
    
    FILE *fs;
    fs =fopen(f,"a+");
    // if(!fs.is_open()){
    //  printf("hey ");
    // }
     i=0;
        while(chunks_length*(i+1)<size)
        { 
          // char filename[100]="file";
          // strcat(filename,(to_string(i)).c_str());
          // printf("%s\n",filename);
          unsigned char temp[20];
          char buff[chunks_length];
          char buf[SHA_DIGEST_LENGTH];
          file.read(buff,chunks_length);
          file.seekg(chunks_length*(i+1),ios::beg);
          SHA1((unsigned char *)buff, chunks_length, temp);
          for (int j=0; j < SHA_DIGEST_LENGTH; j++) {
            printf("%02x",temp[j]);
              fprintf(fs,"%02x",temp[j]);
              //printf("--%d\n",buf[j]);
              //fs << buf[j];
              
          } 
          i++;
          //printf("\n"); 
        }
        if(chunks_length*(i+1)>size){

          // char filename[100]="file";
          // strcat(filename,(to_string(i)).c_str());
          // printf("%s\n",filename);
            int p =size-chunks_length*i;
            char buf[SHA_DIGEST_LENGTH];
          char buff2[p];
          unsigned char temp[20];
          file.read(buff2,p);
          SHA1((unsigned char *)buff2,p, temp);
          for (int j=0; j < SHA_DIGEST_LENGTH; j++) {
            printf("%02x",temp[j]);
              fprintf(fs,"%02x",temp[j]);
              //printf("--%02x",buf[j]);
              //fs << buf[j];
          }

        }
        
 


    
    
 
   
    


     // file.read (memblock, size);
      file.close();

      // cout << "the complete file content is in memory";

      // delete[] memblock;
 
    return 0;
 
}