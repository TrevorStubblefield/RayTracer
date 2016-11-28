#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include "vertex.h"

using namespace std;

class Color
{
public:
	double red, green, blue;

	Color();
	Color(vector <double> c);
	Color(Color* c);
	Color(double red, double green, double blue);
	Color operator=(Color other);
	string printColorsUInt();
};
#endif