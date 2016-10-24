//Camera Class

#include <vector>
#include <math.h>
#include <sstream>
#include "camera.h"
#include "model.h"
#include "vertex.h"
#include "face.h"

using namespace std;

Camera::Camera() {}
Camera::Camera(vector<int> a, vector<int> b, vector<int> c, vector<int> d, vector<int> e, vector<int> f) {
	eye = a;
	look = b;
	up = c;
	distance = d;
	bounds = e;
	res = f;
}