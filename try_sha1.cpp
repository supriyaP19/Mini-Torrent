#include<iostream>
#include<openssl/sha.h>
#include<string>
#include<string.h>
#include<stdio.h>
using namespace std;

int main(){
	string s="0377906abd227a4a579b3dc9f24a1bb76ada648720c8bb5241cd239236f1b7a33d1213275ba440ea";
	unsigned char mysha[40]={0};
	SHA1((unsigned char *)s.c_str(), strlen(s.c_str()),mysha);
	for(int i=0;i<20;i++)
		printf("%02x",mysha[i]);
	return 0;
}
