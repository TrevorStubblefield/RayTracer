#include "sphere.h"
#include "color.h"

using namespace std;

Sphere::Sphere() {}

Sphere::Sphere(double x, double y, double z, double radius, Color colors) {
	this->coordinates = { x,y,z };
	this->radius = radius;
	this->diffuse = colors;
	this->specular = colors;
}

Sphere::Sphere(vector<double> values) {
	this->coordinates = { values[0], values[1], values[2] };
	this->radius = values[3];
	Color color(values[4], values[5], values[6]);
	this->diffuse = color;
	this->specular = color;
}