#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

using namespace std;

class Vertex
{
private:
	int id;
	double xCoordinate, yCoordinate, zCoordinate;

public:
	Vertex ();
	Vertex (int i, double x, double y, double z);
	Vertex (int i, vector<double> v);
	double getX();
	double getY();
	double getZ();
	string toString();
	string toStringCommas();
};

#endif