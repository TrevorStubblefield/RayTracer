#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "vertex.h"
#include "face.h"

using namespace std;

class Model
{
public:
	vector<Vertex> vertices;
	vector<Face> faces;

	Model();
	Model(vector<Vertex> v, vector<Face> f);
	Model center();
	Model round();
	vector<Vertex> getVertices();
	vector<Face> getFaces();
	Vertex findMean();
	Vertex findStdDev();
	string boundingBox();
	vector<double> findTriangle(int id);
};

#endif