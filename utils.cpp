#include "utils.h"

double utils::normalize(double num) {
	if (isnormal(num)) {
		return num;
	}
	else if (isinf(num)){
		return 1000000;
	}
	else return 0;
}

double utils::generateRand() {
	//double r = std::rand() % 100;
	//return r;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	return dis(gen);
}


int utils::decypher(std::vector<int> inp) {
	int max = inp.at(0);
	int predicted = 0;
	for (int i = 0; i < inp.size(); i++) {
		if (inp.at(i) >= max) {
			max = inp.at(i);
			predicted = i;
		}
	}
	return predicted;
}

int utils::decypher(std::vector<double> inp) {
	double max = inp.at(0);
	int predicted = 0;
	for (int i = 0; i < inp.size(); i++) {
		if (inp.at(i) >= max) {
			max = inp.at(i);
			predicted = i;
		}
	}
	return predicted;
}

std::vector<double> utils::cypher(int i, int size) {
	std::vector<double> vec;
	for (int j = 0; j < size; j++) {
		vec.push_back((j == i) ? 1 : 0);
	}
	return vec;
}

int utils::hexToInt(char * c) {
	int size = strlen(c);
	int number = 0, temp = 0;
	for (int i = 0; i < 4; i++) {
		temp = toascii(c[i]);
		if (temp > 9) temp -= 55;
		number += temp * pow(16, 3 - i);
	}
	return number;
}