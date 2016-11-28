#include <vector>
#include "light.h"
#include "color.h"

using namespace std;

Light::Light() {}
Light::Light(vector <double> values) {
	this->coordinates = { values[0],values[1],values[2] };
	this->w = values[3];
	this->colors = Color(values[4], values[5], values[6]);
}