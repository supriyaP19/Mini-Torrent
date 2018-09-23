#include "trackernewclient.h"

string client_program(string file_read_str,string filen_str,string clientipport,string tracker1ipport,string tracker2ipport){
  //socket programming
    std::fstream c_logfile;
    string client_log_file="client_log_file.txt"; 
    c_logfile.open(client_log_file.c_str(),ofstream::app);
    string complete_sha1;
    string complete_sha1_to_tracker;

    string ip_c="", port_c="", ip_t1="", port_t1="", ip_t2="" , port_t2="";
    ip_c=clientipport.substr(0,clientipport.find(':'));
    port_c = clientipport.substr(clientipport.find(':')+1,clientipport.length());
    ip_t1=tracker1ipport.substr(0,tracker1ipport.find(':'));
    port_t1=tracker1ipport.substr(tracker1ipport.find(':')+1,tracker1ipport.length());
    ip_t2=tracker2ipport.substr(0,tracker2ipport.find(':'));
    port_t2=tracker2ipport.substr(tracker2ipport.find(':')+1,tracker2ipport.length());

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
    c_logfile<<"**********************************************"<<endl;
    c_logfile<<"Socket created successfully"<<endl;
    int opt=1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))) 
    { 
      perror("setsockopt"); 
      exit(EXIT_FAILURE); 
    } 
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(stoi(port_t1)); 
    serv_addr.sin_addr.s_addr = inet_addr(ip_t2.c_str()); 


    address.sin_family = AF_INET; 
    address.sin_port = htons(stoi(port_c)); 
    address.sin_addr.s_addr = inet_addr(ip_c.c_str()); 
    c_logfile<<"binding client port no and address to the socket"<<endl;
       
    // Forcefully attaching socket to the port 8080
    if (bind(sock, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        c_logfile<<"Bind Failed!!"<<endl;
        exit(EXIT_FAILURE); 
    } 

    c_logfile<<"Bind successful"<<endl;
    // Convert IPv4 and IPv6 addresses from text to binary form 
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
    c_logfile<<"Connect successful"<<endl;

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
      c_logfile<<file_read_str<<" file is opened in read mode"<<endl;
     
    }

    complete_sha1=tracker1ipport+"\n"+tracker2ipport+"\n"+filen_str.c_str()+to_string(size)+"\n";
    FILE *fs;
    filen_str[filen_str.length()-1]='\0';
    fs =fopen(filen_str.c_str(),"w");
    c_logfile<<filen_str<<"opened in write mode"<<endl;
     i=0;
        while(chunks_length*(i+1)<size)
        { 
          
          unsigned char temp[20];
          char buff[chunks_length];
          char buf[20];
          file.read(buff,chunks_length);
          file.seekg(chunks_length*(i+1),ios::beg);
          SHA1((unsigned char *)buff, chunks_length, temp);
          for (int j=0; j < 10; j++) {
            
              snprintf(ch,sizeof(ch),"%02x",temp[j]);
              complete_sha1=complete_sha1+ch;
              complete_sha1_to_tracker=complete_sha1_to_tracker+ch;
            
          } 
          complete_sha1=complete_sha1+"\n";
          // complete_sha1_to_tracker=complete_sha1_to_tracker+"\n";
          i++;
          printf("\n"); 
        }
        if(chunks_length*(i+1)>size){

          int p =size-chunks_length*i;
          char buf[20];
          char buff2[p];
          unsigned char temp[20];
          file.read(buff2,p);
          SHA1((unsigned char *)buff2,p, temp);
          for (int j=0; j < 10; j++) {

              snprintf(ch,sizeof(ch),"%02x",temp[j]);
              complete_sha1=complete_sha1+ch;
              complete_sha1_to_tracker=complete_sha1_to_tracker+ch;
            
              
          }


        }
        c_logfile<<"SHA1 of file in chunks of 512KB created"<<endl;
  complete_sha1_to_tracker=complete_sha1_to_tracker+"\0";
  complete_sha1=complete_sha1+"\0";
  cout<<"\n"<<complete_sha1<<endl;
  //fs<<complete_sha1<<endl;
  fprintf(fs,"%s",complete_sha1.c_str());
  cout<<"------------";
  cout<<complete_sha1_to_tracker<<endl;
  cout<<"------------";

  //doing hash of the generated sha1 to send to tracker
  string sha1_of_sha1;
  unsigned char temp_string[40];
  char ch1[3];
  SHA1((unsigned char *)complete_sha1_to_tracker.c_str(),complete_sha1_to_tracker.length(),temp_string);
  for (int h=0; h < 20; h++) {

              snprintf(ch1,sizeof(ch1),"%02x",temp_string[h]);
              sha1_of_sha1=sha1_of_sha1+ch1;
            
              
    }
    c_logfile<<"SHA1 of SHA1 is created to send the tracker"<<endl;
    int len=sha1_of_sha1.length();
    char msg2[1024];  
    cout<<"sha1_of_sha1 from client: "<<sha1_of_sha1;
    c_logfile<<"Ready to send SHA1 to tracker using send"<<endl;
    char command[10];
    command[0]='2';
    send(sock , (const char*)command , strlen(command) , 0 ); 
    printf("command code sent...\n");
    sleep(1);

    send(sock , (const char*)sha1_of_sha1.c_str() , len , 0 );

    sleep(1);
    c_logfile<<"Ready to send ip and port of client to tracker using send"<<endl;
    send(sock , (const char*)clientipport.c_str(),clientipport.length(),0); 
  
  close(sock);
  file.close();
  return sha1_of_sha1;
 
}