//Camera Class

#include <vector>
#include <math.h>
#include <sstream>
#include "camera.h"
#include "model.h"
#include "vertex.h"
#include "face.h"

using namespace std;

Camera::Camera() {}
Camera::Camera(vector<double> a, vector<double> b, vector<double> c, vector<double> d, vector<double> e, vector<double> f) {
	eye = a;
	look = b;
	up = c;
	distance = d;
	bounds = e;
	res = f;
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

	for (int i = 0; i < distance.size(); i++) {
		s += to_string(distance[i]) + " ";
	}
	s += "\n";

	for (int i = 0; i < bounds.size(); i++) {
		s += to_string(bounds[i]) + " ";
	}
	s += "\n";
	for (int i = 0; i < res.size(); i++) {
		s += to_string(res[i]) + " ";
	}

	return s;
	return "";
}