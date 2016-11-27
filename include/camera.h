#ifndef CAMERA_H
#define CAMERA_H

#include <unordered_map>
#include <vector>
#include "model.h"
#include "vertex.h"
#include "face.h"

using namespace std;

class Camera
{
public:
	vector<double> eye;
	vector<double> look;
	vector<double> up;
	double distance;
	vector<double> bounds;
	vector<double> res;
	vector<double> ambient;
	unordered_map<string, vector<double>> lights;
	unordered_map<string, vector<double>> spheres;
	unordered_map<string, Model> models;

	Camera();
	Camera(vector<double> eye, vector<double> look, vector<double> up, double distance, vector<double> bounds, vector<double> res, vector<double> ambient, 
		unordered_map<string, vector<double>> lights, unordered_map<string, vector<double>> spheres, unordered_map<string, Model> models);
	string toString();
};

#endif
