#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "model.h"
#include "face.h"

using namespace std;

class Scene {
public:
	Camera camera;
	Model model;
	double ex, ey, ez;
	double lx, ly, lz;
	double ux, uy, uz;
	double right, left, top, bottom;
	double near;
	double width, height;
	vector<double> ambient;
	unordered_map<string, vector<double>> lights;
	unordered_map<string, vector<double>> spheres;
	unordered_map<string, Model> models;
	vector<double> wVector, uVector, vVector;

	Scene();
	Scene(Camera c);
	void buildScenePA3(string filename);
	void buildScenePA4(string filename);
	vector<double> calculateRayForTriangle(int i, int j);
	double calculateT(vector <double> ray);
	vector<unsigned int> colorPixel(double t, double tmin, double tmax);
};


#endif