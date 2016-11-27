//Scene class

#include <iostream>
#include <fstream>
#include <math.h>
#include "scene.h"
#include "camera.h"
#include "model.h"
#include "util.h"
#include "face.h"
#include "vertex.h"
#include "pixel.h"

using namespace std;

Scene::Scene() {}
Scene::Scene(Camera c) {
	camera = c;

	ex = camera.eye[0];
	ey = camera.eye[1];
	ez = camera.eye[2];

	lx = camera.look[0];
	ly = camera.look[1];
	lz = camera.look[2];

	ux = camera.up[0];
	uy = camera.up[1];
	uz = camera.up[2];

	bottom = camera.bounds[0];
	left = camera.bounds[1];
	top = camera.bounds[2];
	right = camera.bounds[3];

	near = -camera.distance;

	width = camera.res[0];
	height = camera.res[1];

	ambient = camera.ambient;
	lights = camera.lights;
	spheres = camera.spheres;
	models = camera.models;

	//Calculate U,V,W
	wVector = vectorSubtraction(camera.eye, camera.look);
	wVector = vectorNormalize(wVector);
	
	uVector = vectorCrossProduct(camera.up, wVector);
	uVector = vectorNormalize(uVector);

	vVector = vectorCrossProduct(wVector, uVector);
}

void Scene::buildScenePA3(string filename) {

	vector<Face> faces = model.getFaces();
	vector<Vertex> vertices = model.getVertices();

	vector<double> ray;
	vector<double> tVector;
	vector<unsigned int> coloredPixel;

	vector< vector<double> > tMatrix;
	vector<double> tRows;

	double t;
	double tmin = INFINITY;
	double tmax = 0;


	for (int i = 0; i < height; i++) {
		tRows.clear();
		for (int j = width-1; j >= 0; j--) {

			ray = calculateRay(j, i);
			t = calculateT(ray);
			tRows.push_back(t);
			if (t < tmin)
				tmin = t;
			if (t != INFINITY && t > tmax)
				tmax = t;
		}
		tMatrix.push_back(tRows);
	}

	ofstream outfile(filename);
	if (outfile.is_open())
	{
		outfile << "P3\n";
		outfile << width << " " << height << " 255\n";
		for (int i = height - 1; i >= 0; i--) {
			for (int j = width-1; j >= 0; j--) {
				Pixel p = colorPixel(tMatrix[i][j], tmin, tmax);
				outfile << p.printColors();
			}
			outfile << "\n";
		}
	}
}

void Scene::buildScenePA4(string filename) {
	
}


vector<double> Scene::calculateRayForTriangle(int i , int j) {
	double px = i / (width - 1)*(right - left) + left;
	px *= width / height;
	double py = j / (height - 1)*(top - bottom) + bottom;
	py *= height / width;
	vector<double> pixpt = vectorAddition(camera.eye,
		vectorAddition(vectorScalar(wVector, near),
			vectorAddition(vectorScalar(uVector,px),vectorScalar(vVector,py))));

	vector<double> ray = vectorSubtraction(pixpt, camera.eye);
	ray = vectorNormalize(ray);

	return ray;
}

vector<unsigned int> Scene::colorPixel(double t, double tmin, double tmax) {
	
	double ratio = 2 * (t - tmin) / (tmax - tmin);
	unsigned int r = fmax(0, 255 * (1 - ratio));
	unsigned int b = fmax(0, 255 * (ratio - 1));
	unsigned int g = 255 - b - r;

	if (t >= INFINITY) {
		r = 239;
		b = 239;
		g = 239;
	}

	vector<unsigned int> coloredPixel = {r,b,g};
	return coloredPixel;
}

double Scene::calculateT(vector <double> ray) {
	//x = 0, y = 1, z = 2
	vector<Face> *faces = &model.faces;

	double minDistance = INFINITY;
	double t = -1;

	for (int currentFace = 0; currentFace < faces->size(); currentFace++) {

		Vertex* vertex1 = &(faces->at(currentFace).v1);
		Vertex* vertex2 = &(faces->at(currentFace).v2);
		Vertex* vertex3 = &(faces->at(currentFace).v3);
		
		double ax = vertex1->xCoordinate;
		double ay = vertex1->yCoordinate;
		double az = vertex1->zCoordinate;

		double bx = vertex2->xCoordinate;
		double by = vertex2->yCoordinate;
		double bz = vertex2->zCoordinate;

		double cx = vertex3->xCoordinate;
		double cy = vertex3->yCoordinate;
		double cz = vertex3->zCoordinate;

		double dx = ray[0];
		double dy = ray[1];
		double dz = ray[2];

		double lx = camera.eye[0];
		double ly = camera.eye[1];
		double lz = camera.eye[2];

		double a = (az - cz);
		double b = (ay - cy);
		double c = (ax - bx);
		double d = (ax - cx);
		double e = (az - bz);
		double f = (ay - by);
		double j = (a*dy - b*dz);
		double k = (a*dx - d*dz);
		double l = (b*dx - d*dy);

		double denom = (j*c) - (k*f) + (l*e);
		if (denom != 0) {
			double g = (ax - lx);
			double h = (ay - ly);
			double i = (az - lz);

			double beta = ((j*g) - (k*h) + (l*i)) / denom;
			if (beta >= 0) {

				double gamma = (((i*dy - h*dz)*c) - ((i*dx - g*dz)*f) + ((h*dx - g*dy)*e)) / denom;

				if ((gamma >= 0) && ((beta + gamma) <= 1)) {

					t = (((h*a - b*i)*c) - ((g*a - d*i)*f) + ((g*b - d*h)*e)) / denom;

					if (t > 0 && t < minDistance) {
						minDistance = t;
					}
				}
			}
		}
	}

	return minDistance;
}