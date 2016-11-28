#ifndef SPHERE_H
#define SPHERE_H

#include "color.h"

using namespace std;

class Sphere
{
public:

	vector <double> coordinates;
	double radius;
	Color ambient = Color({ 0.1, 0.1, 0.1 });
	Color diffuse, specular;

	Sphere();
	Sphere(double x, double y, double z, double radius, Color colors);
	Sphere(vector<double> values);
};

#endif
