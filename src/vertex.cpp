//Vertex Class

#include <vector>
#include <iostream>
#include <sstream>
#include "vertex.h"

using namespace std;

Vertex::Vertex(){}

Vertex::Vertex(int i, double x, double y, double z){
	id = i;
	xCoordinate = x;
	yCoordinate = y;
	zCoordinate = z;
}

Vertex::Vertex(int i, vector<double> v){
	id = i;
	xCoordinate = v[0];
	yCoordinate = v[1];
	zCoordinate = v[2];
}

double Vertex::getX(){return xCoordinate;}

double Vertex::getY(){return yCoordinate;}

double Vertex::getZ(){return zCoordinate;}

vector<double> Vertex::getTriangleFromId(int i) {
	if (id == i) {
		vector<double> triangle = {xCoordinate, yCoordinate, zCoordinate};
		return triangle;
	}
}

string Vertex::toString(){
	ostringstream strs;
	strs << xCoordinate;
	strs << " ";
	strs << yCoordinate;
	strs << " ";
	strs << zCoordinate;
	string s = strs.str();
	return s;
}

string Vertex::toStringCommas(){
	ostringstream strs;
	strs << xCoordinate;
	strs << ", ";
	strs << yCoordinate;
	strs << ", ";
	strs << zCoordinate;
	string s = strs.str();
	return s;
}