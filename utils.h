// A toolbox of general functions used for different calculations
// such as conversions, random numbers or decyphering.

#pragma once
#include <random>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

namespace utils {
	double normalize(double num);
	double generateRand();

	// How do you create a vector<Template> ??????
	int decypher(std::vector<int> inp);
	int decypher(std::vector<double> inp);
	std::vector<double> cypher(int i, int size);
	int hexToInt(char * c);
}
