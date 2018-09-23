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
#include "trackernewclient.h"
#define gotoxy(x,y) printf("%s%d%s%d%s","\033[",x,";",y,"H");
using namespace std;
vector <string> files;

int main(int argc,char *argv[])
{   
    printf("\033[H\033[J");
    cout<<"\033["<<1<<";"<<1<<"H"<<"Command Mode :";
    gotoxy(1,15);
    string local_file_path;
    string filename;
    string clientipport;
    string tracker1ipport;
    string tracker2ipport;
    string logfilename;

    clientipport=argv[1];
    tracker1ipport=argv[2];
    tracker2ipport=argv[3];
    //logfilename=argv[4];
    char buffer[100];
    char ch;
    int k=0;
    do{
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

    string command=files[0];
    if(command=="share"){
        local_file_path=files[1];
        filename=files[2];
        client_program(local_file_path,filename,clientipport,tracker1ipport,tracker2ipport);
    }
 
   
    return 0;

}