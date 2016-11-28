#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include "color.h"

using namespace std;

class Light {
public:
	vector<double> coordinates;
	double w;
	Color colors;

	Light();
	Light(vector <double> values);

};
#endif