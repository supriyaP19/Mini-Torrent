#include<iostream>
#include<string.h>
#include<string>
#include<fstream>
using namespace std;

int main(){
	std::ifstream f("seeder_list.txt");
	string line="";
	string sha1="";
	string ipport="";
	while(getline(f, line)) {
		sha1=line.substr(0,line.find('-'));
		cout<<"sha1: "<<sha1<<endl;
		int i=line.find_last_of("-");
		cout<<"ipport: "<<line.substr(i+1)<<endl;
	    //cout<<line<<endl;
    }
	return 0;
}