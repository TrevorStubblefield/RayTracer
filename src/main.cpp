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

	//OUTPUT FOR ORIGINAL MODEL.
	cout << "=== Before centering" << endl;
	cout << pmodel->getVertices().size() << " vertices, " << pmodel->getFaces().size() << " polygons" << endl;
	cout << "Mean Vertex = (" << pmodel->findMean().toStringCommas() << ")" << endl;
	cout << pmodel->boundingBox() << endl;

	Vertex v = pmodel->findStdDev();
	double stdDevX = v.getX();
	double stdDevY = v.getY();
	double stdDevZ = v.getZ();

	cout << "Standard Deviations: x = " << stdDevX << ", y = " << stdDevY << ", z = " << stdDevZ << endl;


	//OUTPUT AFTER CENTERING THE MODEL.
	Model centeredModel = pmodel->center();

	cout << "=== After Centering" << endl;
	cout << centeredModel.getVertices().size() << " vertices, " << centeredModel.getFaces().size() << " polygons" << endl;
	cout << "Mean Vertex = (" << centeredModel.findMean().toStringCommas() << ")" << endl;
	cout << centeredModel.boundingBox() << endl;

	v = centeredModel.findStdDev();
	stdDevX = v.getX();
	stdDevY = v.getY();
	stdDevZ = v.getZ();

	cout << "Standard Deviations: x = " << stdDevX << ", y = " << stdDevY << ", z = " << stdDevZ << endl;


	//OUTPUT AFTER ROUNDING THE MODEL.
	Model roundedModel = centeredModel.round();

	cout << "=== After Whitening" << endl;
	cout << roundedModel.getVertices().size() << " vertices, " << roundedModel.getFaces().size() << " polygons" << endl;
	cout << "Mean Vertex = (" << roundedModel.findMean().toStringCommas() << ")" << endl;
	cout << roundedModel.boundingBox() << endl;

	v = roundedModel.findStdDev();
	stdDevX = v.getX();
	stdDevY = v.getY();
	stdDevZ = v.getZ();

	cout << "Standard Deviations: x = " << stdDevX << ", y = " << stdDevY << ", z = " << stdDevZ << endl;

	//create the new filenames
	int found = file.find('.');
	string centered = file.substr(0,found) + string("_centered.ply");
	string rounded = file.substr(0,found) + string("_rounded.ply");

	//Write the centered model to file.
	WritePLYFile(centered,centeredModel);

	//Write the rounded model to file.
	WritePLYFile(rounded,roundedModel);
	
	return 0;
}