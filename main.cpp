#include <iostream>
#include <fstream>
using namespace std;

int main(int args, char* argv[]){

	string line;
	ifstream inputFile;
	inputFile.open(argv[1]);

	if (inputFile.is_open()){
		while( getline(inputFile,line) ){
			cout << line << endl;
		}
		inputFile.close();
	}
	
	return 0;
}