#ifndef FACE_H
#define FACE_H

#include <vector>
#include "vertex.h"

using namespace std;

class Face
{
public:
	int size;
	vector<int> vec;
	int idA, idB, idC;
	Vertex v1, v2, v3;

	Face ();
	Face (int s, vector<int> v);
	Face(Vertex a, Vertex b, Vertex c);
	string toString();
};

#endif