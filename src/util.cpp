//Utilites

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "model.h"
#include "util.h"
using namespace std;

Model ReadPLYFile(string filename){

	string line;
	ifstream input;

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
        			Face f(size, tokens);
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