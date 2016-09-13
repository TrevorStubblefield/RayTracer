#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "vertex.h"
#include "face.h"

using namespace std;

class Model
{
private:
	vector<Vertex> vertices;
	vector<Face> faces;

public:
	Model();
	Model(vector<Vertex> v, vector<Face> f);
	Model center();
	Model round();
	vector<Vertex> getVertices();
	vector<Face> getFaces();
	Vertex findMean();
	Vertex findStdDev();
	string boundingBox();
};

#endif