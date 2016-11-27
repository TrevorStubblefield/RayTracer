#include <iostream>
#include <fstream>
#include <vector>
#include "model.h"
#include "vertex.h"
#include "face.h"
#include "util.h"
#include "camera.h"
#include "scene.h"

using namespace std;

int mainPA1(int args, const char* argv[]);
int mainPA2(int args, const char* argv[]);
int mainPA3(int args, const char* argv[]);

int main(int args, const char* argv[]){
	return mainPA3(args, argv);
}

int mainPA1(int args, const char* argv[]){
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

int mainPA2(int args, const char* argv[]){

	string cameraFile = string(argv[1]);
	string modelFile = string(argv[2]);
	string outputFile = string(argv[3]);

	Model model = ReadPLYFile(modelFile);
	Camera camera = ReadCameraFile(cameraFile);

	Scene scene(camera);

	scene.buildScenePA3(outputFile);

	system("pause");

	return 0;
}

int mainPA3(int args, const char* argv[]) {

	string cameraFile = string(argv[1]);
	string outputFile = string(argv[2]);
	Camera camera = ReadCameraFile(cameraFile);

	Scene scene(camera);

	scene.buildScenePA4(outputFile);
	//system("pause");
	
	return 0;
}