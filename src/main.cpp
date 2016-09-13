#include <iostream>
#include <fstream>
#include "model.h"
#include "vertex.h"
#include "face.h"
#include "util.h"
using namespace std;

int main(int args, const char* argv[]){

	//get the filename
	string file = string(argv[1]);

	//create the models
	Model model = ReadPLYFile(file);

	Model* pmodel = &model;
	Model centeredModel = pmodel->center();
	//cout << centeredModel.findStdDev().toString() << endl;
	Model roundedModel = centeredModel.round();

	//create the new filenames
	int found = file.find('.');
	string centered = file.substr(0,found) + string("_centered.ply");
	string rounded = file.substr(0,found) + string("_rounded.ply");

	//TODO: Center
	WritePLYFile(centered,centeredModel);

	//TODO: Round
	WritePLYFile(rounded,roundedModel);
	
	return 0;
}