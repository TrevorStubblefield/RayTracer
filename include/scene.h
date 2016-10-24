#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "model.h"

using namespace std;

class Scene {
private:
	Camera camera;
	Model model;
public:
	Scene();
	Scene(Camera c, Model m);
	void buildOrigin();
};


#endif