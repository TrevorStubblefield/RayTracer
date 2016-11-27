//Camera Class

#include <unordered_map>
#include <vector>
#include <math.h>
#include <sstream>
#include "camera.h"
#include "model.h"
#include "vertex.h"
#include "face.h"

using namespace std;

Camera::Camera() {}
Camera::Camera(vector<double> eye, vector<double> look, vector<double> up, double distance, vector<double> bounds, vector<double> res, vector<double> ambient,
	unordered_map<string, vector<double>> lights, unordered_map<string, vector<double>> spheres, unordered_map<string, Model> models) {
	this->eye = eye;
	this->look = look;
	this->up = up;
	this->distance = distance;
	this->bounds = bounds;
	this->res = res;
	this->ambient = ambient;
	this->lights = lights;
	this->spheres = spheres;
	this->models = models;
}
string Camera::toString(){
	string s = "";

	for (int i = 0; i < eye.size(); i++) {
		s += to_string(eye[i]) + " ";
	}
	s += "\n";

	for (int i = 0; i < look.size(); i++) {
		s += to_string(look[i]) + " ";
	}
	s += "\n";

	for (int i = 0; i < up.size(); i++) {
		s += to_string(up[i]) + " ";
	}
	s += "\n";

	s += to_string(distance) + " ";
	s += "\n";

	for (int i = 0; i < bounds.size(); i++) {
		s += to_string(bounds[i]) + " ";
	}
	s += "\n";
	for (int i = 0; i < res.size(); i++) {
		s += to_string(res[i]) + " ";
	}

	return s;
}