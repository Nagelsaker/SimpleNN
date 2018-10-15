#pragma once
#include "Neuron.h"
#include <vector>
#include <memory>
#include <math.h>

using namespace std;

class Layer {
private:
	int		neuronsSize;
	int		inputSize;
	double	softDenum;
	vector<double> inputs;
	vector<double> softMax;
	vector<double> derSoft;
	vector<shared_ptr<Neuron>> neurons;

public:
	Layer(int nSize, int inSize);
	Layer(Layer & layer);
	void setInputs(vector<double> in);
	void setOutputs(vector<double> out);
	void calculate();
	void calcSoft();

	// Get functions for multiple activation functions. Used for testing.
	// Currently using Softplus and Softmax
	int size()			{ return neuronsSize; };
	int getInputSize()	{ return inputSize; };
	shared_ptr<Neuron>	getNeuron(int index)	{ return neurons.at(index); };
	vector<double>		getInputs()				{ return inputs; }
	vector<double>		getOutputs();
	vector<double>		getDerOuts();
	vector<double>		getDerSigmoids();
	vector<double>		getTanhs();
	vector<double>		getSofts();
};

