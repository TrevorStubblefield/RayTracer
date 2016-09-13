//Model Class

#include <vector>
#include <math.h>
#include "model.h"
#include "vertex.h"
#include "face.h"

using namespace std;

Model::Model(){}

Model::Model(vector<Vertex> v, vector<Face> f){
	vertices = v;
	faces = f;
}

vector<Vertex> Model::getVertices(){return vertices;}
vector<Face> Model::getFaces(){return faces;}

Model Model::center() {

	vector<Vertex> newVertices;
	Vertex mean = findMean();
	double meanX = mean.getX();
	double meanY = mean.getY();
	double meanZ = mean.getZ();

	for (int i = 0; i < vertices.size(); i++){
		double newX = vertices[i].getX() - meanX;
		double newY = vertices[i].getY() - meanY;
		double newZ = vertices[i].getZ() - meanZ;
		Vertex v(i, newX, newY, newZ);
		newVertices.push_back(v);
	}
	Model m(newVertices,this->getFaces());
	return m;
}

Model Model::round() {
	vector<Vertex> newVertices;
	Vertex stdDev = findStdDev();
	double stdDevX = stdDev.getX();
	double stdDevY = stdDev.getY();
	double stdDevZ = stdDev.getZ();

	for (int i = 0; i < vertices.size(); i++) {
		double newX = vertices[i].getX() / stdDevX;
		double newY = vertices[i].getY() / stdDevY;
		double newZ = vertices[i].getZ() / stdDevZ;
		Vertex v(i, newX, newY, newZ);
		newVertices.push_back(v);
	}
	Model m(newVertices,this->getFaces());
	return m;
}

Vertex Model::findMean(){

	double meanX = 0;
	double meanY = 0;
	double meanZ = 0;

	for (int i = 0; i < vertices.size(); i++) {
		meanX += vertices[i].getX();
		meanY += vertices[i].getY();
		meanZ += vertices[i].getZ();
	}
	meanX /= vertices.size();
	meanY /= vertices.size();
	meanZ /= vertices.size();

	Vertex mean(0, meanX, meanY, meanZ);
	return mean;
}

Vertex Model::findStdDev(){
	
	Vertex mean = findMean();
	double meanX = mean.getX();
	double meanY = mean.getY();
	double meanZ = mean.getZ();
	double varianceX = 0;
	double varianceY = 0;
	double varianceZ = 0;
	double stdDevX = 0;
	double stdDevY = 0;
	double stdDevZ = 0;

	for (int i = 0; i < vertices.size(); i++) {
		varianceX += (vertices[i].getX() - meanX)*(vertices[i].getX() - meanX);
		varianceY += (vertices[i].getY() - meanY)*(vertices[i].getY() - meanY);
		varianceZ += (vertices[i].getZ() - meanZ)*(vertices[i].getZ() - meanZ);
	}

	varianceX /= vertices.size();
	varianceY /= vertices.size();
	varianceZ /= vertices.size();

	stdDevX = sqrt(varianceX);
	stdDevY = sqrt(varianceY);
	stdDevZ = sqrt(varianceZ);

	Vertex stdDev(0, stdDevX, stdDevY, stdDevZ);
	return stdDev;
}

