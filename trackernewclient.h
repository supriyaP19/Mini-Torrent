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
#include <pthread.h>
#include <unordered_map>
#include <vector>
#include <set>
#include <fstream>
#define PORT 8080 
#define SHA_DIGEST 10
#define chunks_length 512*1024
using namespace std;



string client_program(string file_read_str,string filen_str,string clientipport,string tracker1ipport,string tracker2ipport);
string getcommand(string torrent_path,string dest_path,string clientipport);
