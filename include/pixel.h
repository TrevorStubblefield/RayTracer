#ifndef PIXEL_H
#define PIXEL_H

#include <vector>
#include "vertex.h"
#include "face.h"

using namespace std;

class Pixel
{
public:
	vector<unsigned int> colors;

	Pixel();
	Pixel(vector <unsigned int> c);
	string printColors();
};
#endif