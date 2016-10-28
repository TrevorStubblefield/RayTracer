#include <vector>
#include <string>
#include "pixel.h"
using namespace std;

Pixel::Pixel() {}

Pixel::Pixel(vector <unsigned int> c) {
	colors = c;
}

string Pixel::printColors() {
	string s = to_string(colors[0]) + " " + to_string(colors[2]) + " " + to_string(colors[1]) + " ";
	return s;
}