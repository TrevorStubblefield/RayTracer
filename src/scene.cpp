//Scene class

#include "scene.h"
#include "camera.h"
#include "model.h"
#include "util.h"

using namespace std;

Scene::Scene() {}
Scene::Scene(Camera c, Model m) {
	camera = c;
	model = m;
}

void Scene::buildOrigin() {
	vector<double> wVector = vectorSubtraction(camera.eye, camera.look);
	wVector = vectorNormalize(wVector);
	vector<double> uVector = vectorCrossProduct(camera.up, wVector);
	vector<double> vVector = vectorCrossProduct(wVector, uVector);


}