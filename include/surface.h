#ifndef SURFACE_H
#define SURFACE_H

#include <vector>
#include "color.h"
using namespace std;


class Surface {
public:
	double distance = -1;
	vector<double> point;
	vector<double> surfaceNormal;
	Color ambient, diffuse, specular;

	Surface();
	Surface(double distance, vector<double> point, vector<double> surfaceNormal, Color ambient, Color diffuse, Color specular);
};
#endif