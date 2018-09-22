#include <stdio.h>
#include <string.h>
#include <string>
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
#include <fstream>
#define PORT 8080 
#define SHA_DIGEST 10
#define chunks_length 512*1024
using namespace std;
std::fstream c_logfile;
string client_log_file="client_log_file.txt";

int client_program(string file_read_str,string filen_str,string clientipport,string tracker1ipport,string tracker2ipport);