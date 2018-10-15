#include "Layer.h"

Layer::Layer(int nSize, int inSize) {
	this->neuronsSize = nSize;
	this->inputSize = inSize;
	inputs.resize(inputSize);
	for (int i = 0; i < neuronsSize; i++) {
		neurons.push_back(make_shared<Neuron>(Neuron(inSize)));
	}
}

// Copy constructor
Layer::Layer(Layer & layer) {
	this->neurons = layer.neurons;
	this->inputs = layer.inputs;
	this->neuronsSize = layer.neuronsSize;
	this->inputSize = layer.inputSize;
	this->softDenum = layer.softDenum;
	this->softMax = layer.softMax;
}

void Layer::calculate() {
	double sum = 0;
	softDenum = 0;
	for (int i = 0; i < neuronsSize; i++) {
		for (int j = 0; j < inputSize; j++) {
			sum += inputs.at(j) * neurons.at(i)->getWeight(j);
		}
		sum += neurons.at(i)->getBias();
		double act = log(1 + exp(sum)); // ReLU activation
		double derAct = 1.0 / (1 + exp(-sum));
		double derSig = derAct * (1 - derAct);
		double tanhAct = tanh(sum);
		double derTanh = -tanhAct * tanhAct + 1;
		softDenum += exp(sum);
		if (isinf(softDenum)) softDenum = 10000;
		neurons.at(i)->setActive(act);
		neurons.at(i)->setDerAct(derAct);
		neurons.at(i)->setDerSig(derSig);
		neurons.at(i)->setTanh(tanhAct);
		neurons.at(i)->setDerTanh(derTanh);
		sum = 0;
	}
}

void Layer::setInputs(vector<double> in) {
	this->inputs = in;
	inputSize = inputs.size();
}

void Layer::setOutputs(vector<double> out) {
	vector<double> outputs = out;
	for (int i = 0; i < outputs.size(); i++) {
		neurons.at(i)->setActive(outputs.at(i));
	}
}

vector<double> Layer::getOutputs() {
	vector<double> outputs;
	for (int i = 0; i < neuronsSize; i++) {
		outputs.push_back(neurons.at(i)->getActive());
	}
	return outputs;
}

vector<double> Layer::getDerOuts() {
	vector<double> der;
	for (int i = 0; i < neuronsSize; i++) {
		der.push_back(neurons.at(i)->getDerAct());
	}
	return der;
}

void Layer::calcSoft() {
	double softm;
	softMax.resize(neuronsSize);
	for (int i = 0; i < neuronsSize; i++) {
		double sum = 0;
		for (int j = 0; j < inputSize; j++) {
			sum += inputs.at(j) * neurons.at(i)->getWeight(j);
		}
		sum += neurons.at(i)->getBias();
		double esum = exp(sum);
		softm = esum / softDenum;
		if (isnan(softm)) softm = 0.0;
		if (isinf(softm)) softm = 1.0;
		softMax.at(i) = softm;
	}
}

vector<double> Layer::getSofts() {
	calcSoft();
	return softMax;
}

vector<double> Layer::getDerSigmoids() {
	vector<double> der;
	for (int i = 0; i < neuronsSize; i++) {
		der.push_back(neurons.at(i)->getDerSig());
	}
	return der;
}

vector<double> Layer::getTanhs() {
	vector<double> der;
	for (int i = 0; i < neuronsSize; i++) {
		der.push_back(neurons.at(i)->getTanh());
	}
	return der;
}
