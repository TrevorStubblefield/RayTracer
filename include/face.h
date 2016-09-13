#ifndef FACE_H
#define FACE_H

#include <vector>

using namespace std;

class Face
{
private:
	int size;
	vector<int> vec;

public:
	Face ();
	Face (int s, vector<int> v);
	string toString();
};

#endif