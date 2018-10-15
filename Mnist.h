#pragma once
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>

using namespace std;

class Mnist {
private:
	int magic;
	int dimensions;
	int tval;
	int setSize;
	char datatype;
	char * buffer;
	string infname;
	string outfname;
	vector<int> sizeOfDim;
	vector<vector<double>> input;
	vector<vector<double>> output;
	map<vector<double>, vector<double>> mapping;
public:
	Mnist() {};
	Mnist(string in, string out);
	~Mnist();
	void initialize(string in, string out);

	void readFile(string fname);
	int reverseHead(int i);
	int size() { return setSize; }

	vector<double> getInputAt(int index) { return input.at(index); };
	vector<double> getOutputAt(int index) { return output.at(index); };
	map<vector<double>, vector<double>> getMapping();
};