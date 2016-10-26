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
		double by = triangleB[1];
		double bz = triangleB[2];

		double cx = triangleC[0];
		double cy = triangleC[1];
		double cz = triangleC[2];

		double dx = ray[0];
		double dy = ray[1];
		double dz = ray[2];

		double lx = camera.eye[0];
		double ly = camera.eye[1];
		double lz = camera.eye[2];

		double z = ((az-cz)*dy-(ay-cy)*dz)*(ax-bx)-((az-cz)*dx - (ax-cx)*dz)*(ay - by) + ((ay-cy)*dx - (ax - cx)*dy*(az-bz));

		if (z != 0) {
			double beta = (((az - cz)*dy - (ay-cy)*dz)*(ax-lx) - ((az-cz)*dx - (ax-cx)*dz)*(ay - ly) + ((ay-cy)*dx - (ax-cx)*dy)*(az-lz)) / z;

			double gamma = (((az-lz)*dy - (ay-ly)*dz)*(ax-bx) - ((az - lz)*dx - (ax-lx)*dz)*(ay-by) + ((ay - ly)*dx - (ax - lx)*dy)*(az-bz)) / z;

			if ( beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && (beta+gamma) <= 1 )
				t = (((ay-ly)*(az-cz)-(ay-cy)*(az-lz))*(ax-bx) - ((ax-lx)*(az-cz)-(ax-cx)*(az-lz))*(ay-by)+((az-lz)*(ay-cy)-(ax-cx)*(ay-ly)) *(az-bz)) / z;

			if (t >= 0 && t < minDistance)
				minDistance = t;
		}

	}

	return minDistance;
}