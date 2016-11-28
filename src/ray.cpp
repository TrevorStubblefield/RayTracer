
#include <vector>
#include "ray.h"
using namespace std;

Ray::Ray() {}

Ray::Ray(vector <double> direction, vector<double> origin) {
	this->direction = direction;
	this->origin = origin;
}