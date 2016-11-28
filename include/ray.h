#ifndef RAY_H
#define RAY_H

#include <vector>
using namespace std;

class Ray {
public:
	vector<double> direction, origin;

	Ray();
	Ray(vector<double> direction, vector<double> origin);
};

#endif