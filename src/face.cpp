//Face Class

#include <vector>
#include <string>
#include "face.h"
#include "vertex.h"

using namespace std;

Face::Face(){}

Face::Face(int s, vector<int> v){
	size = s;
	vec = v;
	idA = v[0];
	idB = v[1];
	idC = v[2];
}

Face::Face(Vertex a, Vertex b, Vertex c) {
	v1 = a;
	v2 = b;
	v3 = c;
}

string Face::toString(){
	string s = to_string(size) + " ";
	for (int i = 0; i < vec.size(); i++) {
		s += to_string(vec[i]) + " ";
	}
	return s;
}