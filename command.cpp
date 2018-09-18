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
#include <sys/ioctl.h>
#include <linux/limits.h>

void command_mode(){

    // struct termios initial_settings, new_settings;
    // FILE *input;
    // FILE *output;
    // input = fopen("/dev/tty", "r");
    // output = fopen("/dev/tty", "w");
    // tcgetattr(fileno(input),&initial_settings);
    // new_settings = initial_settings;
    // new_settings.c_lflag &= ~ECHO;
    // new_settings.c_lflag &= ~ICANON;

    // tcsetattr(fileno(input), TCSANOW, &new_settings);
    cout<<"\033["<<37<<";"<<1<<"H"<<"--------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

   cout<<"\033["<<38<<";"<<1<<"H"<<"                                                                                                                            ";
    cout<<"\033["<<38<<";"<<0<<"H"<<"Command Mode :";
    gotoxy(38,15);
    char buffer[PATH_MAX];
    buffer[0]='\0';

    char ch,nul_char;
    int i=0;
    string string2;
    cout<<"Enter Command "<<endl;
    getline(cin,string2);
   
    cout<<string2;
    cout<<endl;
    

     

    }


    int main(){
        char ch;
        while(1){

            ch=getchar();
            if(ch==58){
                command_mode();
            }
        }
        return 0;
    }