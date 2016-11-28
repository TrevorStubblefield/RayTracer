#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "model.h"
#include "face.h"
#include "ray.h"
#include "surface.h"
#include "light.h"

using namespace std;

class Scene {
public:
	Camera camera;
	double ex, ey, ez;
	double lx, ly, lz;
	double ux, uy, uz;
	double right, left, top, bottom;
	double near;
	double width, height;
	Color ambient;
	vector<Light> lights;
	vector<Sphere> spheres;
	vector<Model> models;
	vector<double> wVector, uVector, vVector;

	Scene();
	Scene(Camera c);
	void buildScene(string filename);
	Ray calculateRay(int i, int j);
	Surface calculateIntersect(Ray ray);
	vector<double> colorPixel(double t, double tmin, double tmax);
	Color colorPixelPA4(Surface surface, Ray ray);
};


#endif