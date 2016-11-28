//Model Class

#include <vector>
#include <math.h>
#include <sstream>
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

	for (unsigned int i = 0; i < vertices.size(); i++){
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

	for (unsigned int i = 0; i < vertices.size(); i++) {
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

	for (unsigned int i = 0; i < vertices.size(); i++) {
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

	for (unsigned int i = 0; i < vertices.size(); i++) {
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

string Model::boundingBox(){
	double minX = vertices[0].getX();
	double minY = vertices[0].getY();
	double minZ = vertices[0].getZ();
	double maxX = vertices[0].getX();
	double maxY = vertices[0].getY();
	double maxZ = vertices[0].getZ();

	for (unsigned int i = 0; i < vertices.size(); i++){
		double currentX = vertices[i].getX();
		double currentY = vertices[i].getY();
		double currentZ = vertices[i].getZ();
		if(currentX < minX)
			minX = currentX;
		if(currentY < minY)
			minY = currentY;
		if(currentZ < minZ)
			minZ = currentZ;
		if(currentX > maxX)
			maxX = currentX;
		if(currentY > maxY)
			maxY = currentY;
		if(currentZ > maxZ)
			maxZ = currentZ;
	}
	ostringstream strs;
	strs << "Bounding Box: ";
	strs << minX;
	strs << " <= x <= ";
	strs << maxX;
	strs << ", ";
	strs << minY;
	strs << " <= y <= ";
	strs << maxY;
	strs << ", ";
	strs << minZ;
	strs << " <= z <= ";
	strs << maxZ;

	string s = strs.str();
	return s;
}

vector<double> Model::findTriangle(int id) {

	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (vertices[i].id == id) {
			return vertices[i].getTriangle();
		}
	}
}