#include "Neuron.h"

Neuron::Neuron(int inputCount) {
	weights.resize(inputCount);
	deltaWeights.resize(inputCount);
	wbias = utils::generateRand();

	for (int i = 0; i < inputCount; i++) {
		weights.at(i) = utils::generateRand();
		deltaWeights.at(i) = 0;
	}
}

// Copy constructor
Neuron::Neuron(const Neuron & neuron) {
	this->active = neuron.active;
	this->derAct = neuron.derAct;
	this->derSig = neuron.derSig;
	this->softMax = neuron.softMax;
	this->derSoft = neuron.derSoft;
	this->tanhAct = neuron.tanhAct;
	this->derTanh = neuron.derTanh;
	this->bias = neuron.bias;
	this->wbias = neuron.wbias;
	this->weights = neuron.weights;
	this->deltaWeights = neuron.weights;
}

Neuron & Neuron::operator=(const Neuron & rhs) {
	this->active = rhs.active;
	this->derAct = rhs.derAct;
	this->derSig = rhs.derSig;
	this->softMax = rhs.softMax;
	this->derSoft = rhs.derSoft;
	this->tanhAct = rhs.tanhAct;
	this->derTanh = rhs.derTanh;
	this->bias = rhs.bias;
	this->wbias = rhs.wbias;
	this->weights = rhs.weights;
	this->deltaWeights = rhs.weights;
	return *this;
}
