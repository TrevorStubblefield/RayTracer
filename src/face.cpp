//Face Class

#include <vector>
#include <string>
#include "face.h"
#include "vertex.h"
#include "color.h"
#include "util.h"

using namespace std;

Face::Face(){}

Face::Face(Vertex a, Vertex b, Vertex c, Color ambient, Color diffuse, Color specular){
	v1 = a;
	v2 = b;
	v3 = c;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;

	vector<double> U = vectorSubtraction(v2.getTriangle(), v1.getTriangle());
	vector<double> V = vectorSubtraction(v3.getTriangle(), v1.getTriangle());
	surfaceNormal = vectorCrossProduct(U, V);
	surfaceNormal = vectorNormalize(surfaceNormal);
}

string Face::toString() {
	string s = v1.toString() + v2.toString() + v3.toString();
	return s;
}