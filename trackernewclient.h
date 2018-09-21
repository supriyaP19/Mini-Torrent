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
#define PORT 8080 
#define SHA_DIGEST 10
#define chunks_length 512*1024
using namespace std;



int client_program(string file_read_str,string filen_str);