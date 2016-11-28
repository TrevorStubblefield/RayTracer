#ifndef FACE_H
#define FACE_H

#include <vector>
#include "vertex.h"
#include "color.h"

using namespace std;

class Face
{
public:
	int size;
	Vertex v1, v2, v3;
	Color ambient;
	Color diffuse;
	Color specular;
	vector<double> surfaceNormal;

	Face();
	Face(Vertex a, Vertex b, Vertex c, Color ambient, Color diffuse, Color specular);
	string toString();
};

#endif