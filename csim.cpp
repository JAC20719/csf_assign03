#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using std::cin; using std::cout; using std::endl;
using std::string;
using std::getline;
int main(){
	char ls = '\0'; // store instruction
	string address; // store address
	string line; // get whole lines from file
	
	// start main loop, reading 1 instruction at a time
	while (getline(cin,line)) {
		ls = line[0];
		address = line.substr(2,10);
		cout << ls << " " << address << endl;
	}
	return 0;
}
