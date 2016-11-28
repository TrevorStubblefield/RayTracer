#ifndef CAMERA_H
#define CAMERA_H

#include <unordered_map>
#include <vector>
#include "model.h"
#include "vertex.h"
#include "face.h"
#include "sphere.h"
#include "light.h"

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
	Color ambient;
	vector<Light> lights;
	vector<Sphere> spheres;
	vector<Model> models;

	Camera();
	Camera(vector<double> eye, vector<double> look, vector<double> up, double distance, vector<double> bounds, vector<double> res, Color ambient,
		vector<Light> lights, vector<Sphere> spheres, vector<Model> models);
	string toString();
};

#endif
