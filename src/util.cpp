//Utilites

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include "model.h"
#include "util.h"
#include "camera.h"
#include "pixel.h"

using namespace std;

Model ReadPLYFile(string filename){

	string line;
	ifstream input;

	unordered_map<int, Vertex> vertexMap;

	vector<Vertex> vertices;
	vector<Face> faces;

	int numVertices = 0;
	int numFaces = 0;

	input.open(filename);

	if (input.is_open()){
		while( getline(input,line) ){
			if (line.find("element vertex ") != string::npos) {
				int index = line.rfind(' ');
				string a = line.substr(index, line.length()-1);
				numVertices = stoi(a);
			}
			if (line.find("element face ") != string::npos) {
				int index = line.rfind(' ');
				string a = line.substr(index, line.length()-1);
				numFaces = stoi(a);
			}
			if (line.find("end_header") != string::npos) {

				for (int i = 0; i < numVertices; i++) {
					getline(input,line);
    				string buf;
    				stringstream ss(line);
    				vector<double> tokens;
    				while (ss >> buf){
        				tokens.push_back(stod(buf));
        			}
        			Vertex v(i, tokens);
        			vertices.push_back(v);
					vertexMap.insert({ i, v });
				}

				for (int i = 0; i < numFaces; i++) {
					getline(input,line);
    				string buf;
    				stringstream ss(line);
    				vector<int> tokens;
    				ss >> buf;
    				int size = stod(buf);
    				while (ss >> buf){
        				tokens.push_back(stod(buf));
        			}
					Vertex a = vertexMap[tokens[0]];
					Vertex b = vertexMap[tokens[1]];
					Vertex c = vertexMap[tokens[2]];
        			Face f(a, b, c);
        			faces.push_back(f);
				}
			}
		}
		input.close();
	}
	Model m(vertices,faces);
	return m;
}

int WritePLYFile(string filename, Model model){

	vector<Vertex> vertices = model.getVertices();
	vector<Face> faces = model.getFaces();

	ofstream outfile (filename);
	if(outfile.is_open())
	{
		outfile << "ply\n";
		outfile << "format ascii 1.0\n";
		string s = to_string(vertices.size());
		outfile << "element vertex " + s + "\n";
		outfile << "property float32 x\n";
		outfile << "property float32 y\n";
		outfile << "property float32 z\n";
		s = to_string(faces.size());
		outfile << "element face " + s + "\n";
		outfile << "property list uint8 int32 vertex_indices\n";
		outfile << "end_header\n";
		for (int i = 0; i < vertices.size(); i++){
			outfile << vertices[i].toString() + "\n";
		}
		for (int i = 0; i < faces.size(); i++) {
			outfile << faces[i].toString() + "\n";
		}
	}

	return 0;
}

Camera ReadCameraFile(string filename){

	int i = 1;
	int numberOfLights = 0;
	int numberOfSpheres = 0;
	int numberOfModels = 0;
	vector<double> eye;
	vector<double> look;
	vector<double> up;
	double distance = 0;
	vector<double> bounds;
	vector<double> res;
	vector<double> ambient;
	unordered_map<string, vector<double>> lights;
	unordered_map<string, vector<double>> spheres;
	unordered_map<string, Model> models;

	string line;
	ifstream input;
	input.open(filename);

	if (input.is_open()){
		while( getline(input,line) ){
			vector<double> temp;
			int index = line.find(' ');
			string fixedLine = line.substr(index, line.length()-1);

			string buf;
			stringstream ss(fixedLine);
    		while (ss >> buf){
        		if (i == 1)
					eye.push_back(stod(buf));
				else if (i == 2)
					look.push_back(stod(buf));
				else if (i == 3)
					up.push_back(stod(buf));
				else if (i == 4)
					distance = stod(buf);
				else if (i == 5)
					bounds.push_back(stod(buf));
				else if (i == 6)
					res.push_back(stod(buf));
				else if (line.find("ambient") != string::npos) {
					ambient.push_back(stod(buf));
				}
				else if (line.find("light") != string::npos) {
					temp.push_back(stod(buf));
				}
				else if (line.find("sphere") != string::npos) {
					temp.push_back(stod(buf));
				}
        	}
			if (line.find("light") != string::npos) {
				numberOfLights++;
				pair<std::string, vector<double>> light("light" + to_string(numberOfLights), temp);
				lights.insert(light);
			}
			else if (line.find("sphere") != string::npos) {
				numberOfSpheres++;
				pair<std::string, vector<double>> light("sphere" + to_string(numberOfSpheres), temp);
				spheres.insert(light);
			}
			else if (line.find("model") != string::npos) {
				numberOfModels++;
				Model model = ReadPLYFile(fixedLine);
				pair<std::string, Model> light("model" + to_string(numberOfModels), model);
				models.insert(light);
			}
			i++;
		}
	}
	return Camera(eye, look, up, distance, bounds, res, ambient, lights, spheres, models);
}

Model ReadOBJFile(string filename) {
	return Model();
}


vector<double> vectorSubtraction(vector<double> a, vector<double> b){
	vector <double> c;
	c.push_back(a[0]-b[0]);
	c.push_back(a[1]-b[1]);
	c.push_back(a[2]-b[2]);

	return c;
}
vector<double> vectorAddition(vector<double> a, vector<double> b){
	vector <double> c;
	c.push_back(a[0]+b[0]);
	c.push_back(a[1]+b[1]);
	c.push_back(a[2]+b[2]);

	return c;
}
vector<double> vectorNormalize(vector<double> a){
	vector <double> b;
	double length = (a[0]*a[0]) + (a[1]*a[1]) + (a[2]*a[2]);
	double sqrtLength = sqrt(length);
	b.push_back(a[0]/sqrtLength);
	b.push_back(a[1]/sqrtLength);
	b.push_back(a[2]/sqrtLength);

	return b;
}
vector<double> vectorScalar(vector<double> a, double b) {
	vector <double> c = { a[0]*b,a[1]*b,a[2]*b };
	return c;
}
vector<double> vectorCrossProduct(vector<double> a, vector<double> b){
	vector<double> c;
	c.push_back( (a[1]*b[2]) - (a[2]*b[1]) );
	c.push_back( (a[2]*b[0]) - (a[0]*b[2]) );
	c.push_back( (a[0]*b[1]) - (a[1]*b[0]) );

	return c;
}

