#ifndef UTIL_H
#define UTIL_H

#include "model.h"
#include "camera.h"
#include <string>
#include <vector>

using namespace std;

Model ReadPLYFile(string filename);
int WritePLYFile(string filename, Model model);
Camera ReadCameraFile(string filename);

vector<double> vectorSubtraction(vector<double> a, vector<double> b);
vector<double> vectorAddition(vector<double> a, vector<double> b);
vector<double> vectorCrossProduct(vector<double> a, vector<double> b);
vector<double> vectorNormalize(vector<double> a);
vector<double> vectorScalar(vector<double> a, double b);

#endif