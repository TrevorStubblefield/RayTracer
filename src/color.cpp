#include <vector>
#include <string>
#include "color.h"
using namespace std;

Color::Color() {}

Color::Color(vector <double> c) {
	red = c[0];
	green = c[1];
	blue = c[2];

}

Color::Color(double red, double green, double blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Color::Color(Color* c) {
	this->red = c->red;
	this->blue = c->blue;
	this->green = c->green;
}

Color Color::operator=(Color other) {
	red = other.red;
	green = other.green;
	blue = other.blue;

	return this;
}

string Color::printColorsUInt() {
	unsigned int UIntRed = static_cast<unsigned int>(red + 0.5);
	unsigned int UIntGreen = static_cast<unsigned int>(green + 0.5);
	unsigned int UIntBlue = static_cast<unsigned int>(blue + 0.5);
	string s = to_string(UIntRed) + " " + to_string(UIntGreen) + " " + to_string(UIntBlue) + " ";
	return s;
}