#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "vertex.h"
#include "face.h"

using namespace std;

class Camera
{
public:
	vector<double> eye;
	vector<double> look;
	vector<double> up;
	vector<double> distance;
	vector<double> bounds;
	vector<double> res;

	Camera();
	Camera(vector<double> a, vector<double> b, vector<double> c, vector<double> d, vector<double> e, vector<double> f);
	string toString();
};

#endif

	/**
	eye 4 4 4
	look 0 0 0
	up 0 0 1
	d 2
	bounds -1 -1 1 1
	res 256 256

	The first three lines supply the location of the focal point, the look at point, and the up vector. 
	Then comes the focal length, i.e. the distance from the focal point to the image plane. Pay particular 
	attention to the last two arguments. The 'bounds' values indicate the minimum and maximum extend of the 
	bounded image rectangle on the infinite image plane in the camera horizontal and vertical directions 
	respectively. Then the resolution values seperately indicate the pixel sampling resolution across the 
	horizontal and vertical dimensions of the bounded rectangle.
	**/