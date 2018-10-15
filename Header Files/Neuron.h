#pragma once
#include "utils.h"
#include <vector>

using namespace std;

class Neuron {
private:
	double active;
	double derSig;
	double softMax;
	double derAct	= 1.0;
	double derSoft	= 1.0;
	double tanhAct;
	double derTanh;
	double bias		= 1;
	double wbias	= 0.5;
	vector<double> weights;
	vector<double> deltaWeights;
public:
	Neuron(int inputCount);
	Neuron(const Neuron & neuron);

	int		getWeightsSize()	{ return weights.size(); };
	double	getActive()			{ return active; };
	double	getDerAct()			{ return derAct; };
	double	getDerSig()			{ return derSig; };
	double	getDerSoft()		{ return derSoft; };
	double	getTanh()			{ return tanhAct; };
	double	getDerTanh()		{ return derTanh; };
	double	getWeight(int index){ return weights.at(index); };
	double	getBias()			{ return bias * wbias; };
	double	getWbias()			{ return wbias; };
	double	getDelta(int index)	{ return deltaWeights.at(index); };

	void updateWeight(int index, double val)	{ this->weights.at(index) += val; };
	void updateWbias(double val)				{ this->wbias += val; };
	void setWeight(int index, double val)		{ this->weights.at(index) = val; };
	void setDelta(int index, double val)		{ this->deltaWeights.at(index) = val; };
	void setBias(double bias)					{ this->bias = bias; };
	void setWbias(double wbias)					{ this->wbias = wbias; };
	void setActive(double active)				{ this->active = active; };
	void setDerAct(double der)					{ this->derAct = der; };
	void setDerOut(double der)					{ this->derSoft = der; };
	void setDerSig(double der)					{ this->derSig = der; };
	void setTanh(double tanhAct)				{ this->tanhAct = tanhAct; };
	void setDerTanh(double der)					{ this->derTanh = der; };


	Neuron & operator=(const Neuron & rhs);
};

