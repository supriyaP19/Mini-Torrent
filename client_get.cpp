#include "trackernewclient.h"

string getcommand(string torrent_path,string dest_path,string clientipport){
    string complete_sha1;
    string complete_sha1_to_tracker;
    cout<<"in client123"<<endl;
   
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024*1024] = {0}; 

     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        //c_logfile<<"error in socket creation"<<endl;
        return "-1"; 
    } 
    cout<<"socket creation"<<endl;
    // c_logfile<<"**********************************************"<<endl;
    // c_logfile<<"Socket created successfully"<<endl;
    int opt=1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))) 
    { 
      perror("setsockopt"); 
      exit(EXIT_FAILURE); 
    } 
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    cout<<"after setsockopt"<<endl;    
     serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    serv_addr.sin_addr.s_addr = INADDR_ANY;

     address.sin_family = AF_INET; 
     string ip(clientipport.substr(0,clientipport.find(':')));
     string port(clientipport.substr(clientipport.find(':')+1,clientipport.length()));
    address.sin_port = htons(stoi(port)); 
    address.sin_addr.s_addr = inet_addr(ip.c_str()); 

       
    // Forcefully attaching socket to the port 8080
    if (bind(sock, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        //c_logfile<<"Bind Failed!!"<<endl;
        exit(EXIT_FAILURE); 
    } 

    cout<<"after bind"<<endl;
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        //c_logfile<<"Invalid Address"<<endl;
        return "-1"; 
    } 
    cout<<"after inet-ptons"<<endl;
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n");
        //c_logfile<<"Connect Failed"<<endl; 
        return "-1"; 
    } 
    cout<<"After connect"<<endl;
    std::ifstream f("xyz.mtorrent");
    string line="";
    string sha1="";
    string ipport="";
   // string complete_sha1_to_tracker="";
    int i=0;
    if(f.is_open()){
           cout<<"file opened "<<endl;
    }
    while(getline(f, line)) {
        if(i>=4){
            complete_sha1_to_tracker=complete_sha1_to_tracker+line;
        }
        i++;
    }
    cout<<"read the file "<<endl;
    string sha1_of_sha1;
    unsigned char temp_string[40];
    char ch1[3];
    SHA1((unsigned char *)complete_sha1_to_tracker.c_str(),complete_sha1_to_tracker.length(),temp_string);
    for (int h=0; h < 20; h++) {

              snprintf(ch1,sizeof(ch1),"%02x",temp_string[h]);
              sha1_of_sha1=sha1_of_sha1+ch1;          
              
    }
    cout<<"inside client_get.cpp----"<<sha1_of_sha1<<endl;

    char command[10];
    command[0]='1';
    send(sock , command , strlen(command) , 0 ); 
    printf("command code sent...\n");
    sleep(1);
    send(sock , sha1_of_sha1.c_str() , sha1_of_sha1.length() , 0 );
    int valread1= read( sock ,buffer, 100 );
    cout<<"response received from server :"<<buffer;
    //c_logfile<<"response received from server"<<endl;
    cout<<"closing nConnection with tracker"<<endl;
   

  close(sock);


//   c_logfile<<"connection closed with the tracker"<<endl;
//   c_logfile<<"establishing connection with the other client"<<endl;

//     int sock = 0, valread; 
//     string port1="5000";
//     string ip1="111.22.33.36";
//     struct sockaddr_in new_client_addr; 
//     address.sin_family = AF_INET;
//     address.sin_port = htons(stoi(port1)); 
//     address.sin_addr.s_addr = inet_addr(ip1.c_str());
//     c_logfile<<"trying to connect with client who has the required file"<<endl;

//     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
//     { 
//         printf("\nConnection Failed \n");
//         c_logfile<<"Connect Failed"<<endl; 
//         return -1; 
//     } 
//     c_logfile<<"connection completed"<<endl;

//     char arr[10]="hey who are you";

//     send(sock , arr , strlen(arr) , 0 ); 
//     printf("sent message to client");

// // 
    //file.close();
  return buffer;
 
}