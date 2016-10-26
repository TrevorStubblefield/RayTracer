//Face Class

#include <vector>
#include <string>
#include "face.h"

using namespace std;

Face::Face(){}

Face::Face(int s, vector<int> v){
	size = s;
	vec = v;
	idA = v[0];
	idB = v[1];
	idC = v[2];
}

string Face::toString(){
	string s = to_string(size) + " ";
	for (int i = 0; i < vec.size(); i++) {
		s += to_string(vec[i]) + " ";
	}
	return s;
}