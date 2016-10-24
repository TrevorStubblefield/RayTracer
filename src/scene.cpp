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

void Scene::buildScene() {
	//Calculate U,V,W
	vector<double> wVector = vectorSubtraction(camera.look, camera.eye);
	wVector = vectorNormalize(wVector);
	vector<double> uVector = vectorCrossProduct(camera.up, wVector);
	vVector = vectorNormalize(vVector);
	vector<double> vVector = vectorCrossProduct(wVector, uVector);

}