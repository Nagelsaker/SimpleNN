#pragma once
#include "Neuron.h"
#include "Layer.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <map>
#include <algorithm>

using namespace std;

class NeuralNetwork {
private:
	int		topSize;
	int		epochs;
	int		batch;
	double	lr			= 0.5; // Learning rate
	double	br			= 0.5; // Learning rate for biases
	double	alpha		= 0.9; // 05 - 0.9
	double	margin		= 0.001; // Error margin on the output
	double	actualError	= 0.0;
	double	error		= 0.0;
	vector<int>		predictedOutput;
	vector<int>		topology;
	vector<double>	historicalErrors;
	vector<double>	crossEntropy;
	vector<double>	derivedError;
	vector<double>	inputs;
	vector<double>	target;
	vector<double>	output;
	vector<shared_ptr<Layer>> layers;
public:
	NeuralNetwork(vector<int> topology);
	void feedForward(vector<double> inputs);
	void feedForward();
	void backPropagate();
	void train(map<vector<double>, vector<double>> trainingSet, int e, int batch);

	// set functions
	void setLearningRate(double lr)	{ this->lr = lr; };
	void setBiasLR(double br)		{ this->br = br; };
	void setMargin(double margin)	{ this->margin = margin; };
	void saveWeights(string fname);
	void updateErrors();
	void resetErrors();
	void resetNetwork();

	// get functions
	vector<int>		getPredictedOutput();
	vector<double>	getOutput() { return output; }
	vector<double> getInput() { return inputs; }
	void loadWeights(string fname);
	void saveErrors(string fname);

	// Overloads
	template<typename T> // Overloaded << for vectors
	friend ostream & operator<<(ostream & os, const vector<T> & v);

	friend ostream & operator<<(ostream & os, const NeuralNetwork & nn) {
		for (int i = 1; i < nn.topSize; i++) {
			os << "Matrix " << i << " weights\n";
			for (int j = 0; j < nn.layers.at(i)->size(); j++) {
				os << nn.layers.at(i)->getNeuron(j)->getBias() << "\t";
				for (int a = 0; a < nn.layers.at(i)->getNeuron(j)->getWeightsSize(); a++) {
					os << fixed << nn.layers.at(i)->getNeuron(j)->getWeight(a) << setprecision(6) << "\t";
				}
				os << endl;
			}
			os << endl;
		}
		return os;
	}
};

template<typename T> // Overloaded << for vectors
ostream & operator<<(ostream & os, const vector<T> & v) {
	for (int i = 0; i < v.size(); i++) {
		os << fixed << v.at(i) << setprecision(7);
		if (i != v.size() - 1) os << ", ";
	}
	return os;
}

