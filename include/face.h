#ifndef FACE_H
#define FACE_H

#include <vector>

using namespace std;

class Face
{
public:
	int size;
	vector<int> vec;
	int idA, idB, idC;

	Face ();
	Face (int s, vector<int> v);
	string toString();
};

#endif