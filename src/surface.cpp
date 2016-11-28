#include "surface.h"
#include "color.h"

Surface::Surface() {
	distance = -1;
}
Surface::Surface(double distance, vector<double> point, vector<double> surfaceNormal, Color ambient, Color diffuse, Color specular) {
	this->distance = distance;
	this->point = point;
	this->surfaceNormal = surfaceNormal;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}
