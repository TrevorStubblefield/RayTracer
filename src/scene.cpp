//Scene class

#include <iostream>
#include <math.h>
#include "scene.h"
#include "camera.h"
#include "model.h"
#include "util.h"
#include "face.h"
#include "vertex.h"

using namespace std;

Scene::Scene() {}
Scene::Scene(Camera c, Model m) {
	camera = c;
	model = m;

	ex = camera.eye[0];
	ey = camera.eye[1];
	ez = camera.eye[2];

	lx = camera.look[0];
	ly = camera.look[1];
	lz = camera.look[2];

	ux = camera.up[0];
	uy = camera.up[1];
	uz = camera.up[2];

	right = camera.bounds[0];
	left = camera.bounds[1];
	top = camera.bounds[2];
	bottom = camera.bounds[3];

	near = -camera.distance[0];

	width = camera.res[0];
	height = camera.res[1];

	//Calculate U,V,W
	wVector = vectorSubtraction(camera.eye, camera.look);
	wVector = vectorNormalize(wVector);
	
	uVector = vectorCrossProduct(camera.up, wVector);
	uVector = vectorNormalize(uVector);

	vVector = vectorCrossProduct(wVector, uVector);
}

void Scene::buildScene() {

	vector<Face> faces = model.getFaces();
	vector<Vertex> vertices = model.getVertices();

	vector<double> ray;
	vector<double> tVector;
	vector<double> coloredPixel;

	vector< vector<double> > tMatrix;
	vector<double> tRows;

	double t;
	double tmin = INFINITY;
	double tmax = 0;

	//1. create rays
	//2. calculate t for rays.
	//3. Find tmin and tmax.

	//Second iteration
	//3. color pixel.
	//4. write to file.
	for (int i = 0; i < width; i++) {
		tRows.clear();
		for (int j = 0; j < height; j++) {

			ray = calculateRay(i, j);
			t = calculateT(ray);
			tRows.push_back(t);
			if (t < tmin)
				tmin = t;
			if (t > tmax)
				tmax = t;
		}
		tMatrix.push_back(tRows);
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			coloredPixel = colorPixel(tMatrix[i][j], tmin, tmax);
			cout << tMatrix[i][j] << endl;
			//cout << coloredPixel[0] << " " << coloredPixel[1] << " " << coloredPixel[2] << endl;
		}
	}

}


vector<double> Scene::calculateRay(int i , int j) {
	double px = i / (width - 1)*(right - left) + left;
	double py = j / (height - 1)*(top - bottom) + bottom;
	vector<double> pixpt = vectorAddition(camera.eye,
		vectorAddition(vectorScalar(wVector, near),
			vectorAddition(vectorScalar(uVector,px),vectorScalar(vVector,py))));

	vector<double> ray = vectorSubtraction(pixpt, camera.eye);
	ray = vectorNormalize(ray);

	return ray;
}

vector<double> Scene::colorPixel(double t, double tmin, double tmax) {
	double ratio = 2 * (t - tmin) / (tmax - tmin);
	double r = fmax(0, 255 * (1 - ratio));
	double b = fmax(0, 255 * (ratio - 1));
	double g = 255 - b - r;

	vector<double> coloredPixel = {r,b,g};
	return coloredPixel;
}

double Scene::calculateT(vector <double> ray) {
	//x = 0, y = 1, z = 2
	vector<Face> faces = model.faces;
	vector<double> triangleA, triangleB, triangleC;

	double minDistance = INFINITY;
	double t = -1;

	for (int currentFace = 0; currentFace < faces.size(); currentFace++) {

		triangleA = model.findTriangle(faces[currentFace].idA);
		triangleB = model.findTriangle(faces[currentFace].idB);
		triangleC = model.findTriangle(faces[currentFace].idC);
		
		double ax = triangleA[0];
		double ay = triangleA[1];
		double az = triangleA[2];

		double bx = triangleB[0];

		if (z != 0) {
			beta = ((j*d) - (k*e) + (l*f)) / z;

			gamma = ((m*g) - (n*h) + (o*i)) / z;

			if ( beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && (beta+gamma) <= 1 )
				t = (p - q + r) / z;

			if (t >= 0 && t < minDistance)
				minDistance = t;
		}

	}

	return minDistance;
}