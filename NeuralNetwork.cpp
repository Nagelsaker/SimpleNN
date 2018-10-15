#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(vector<int> topology) {
	topSize = topology.size();
	this->topology = topology;
	Layer inputLayer(topology.at(0), topology.at(0));
	layers.push_back(make_shared<Layer>(inputLayer));

	for (int i = 1; i < topSize; i++) {
		Layer l(topology.at(i), topology.at(i-1));
		layers.push_back(make_shared<Layer>(l));
	}
}

void NeuralNetwork::feedForward(vector<double> input) {
	// Input - Hidden
	this->inputs = input;
	for (int i = 0; i < layers.at(0)->size(); i++) {
		layers.at(0)->setInputs(inputs);
		layers.at(0)->setOutputs(inputs);
	}

	// Hidden - Hidden | Hidden - Output
	for (int i = 1; i < layers.size(); i++) {
		layers.at(i)->setInputs(layers.at(i - 1)->getOutputs());
		layers.at(i)->calculate();
	}
	output = layers.at(layers.size() - 1)->getSofts(); // Softmax for the final layer
	predictedOutput.clear();
}

void NeuralNetwork::feedForward() {
	// Input - Hidden
	for (int i = 0; i < layers.at(0)->size(); i++) {
		layers.at(0)->setInputs(inputs);
		layers.at(0)->setOutputs(inputs);
	}

	// Hidden - Hidden | Hidden - Output
	for (int i = 1; i < layers.size(); i++) {
		layers.at(i)->setInputs(layers.at(i - 1)->getOutputs());
		layers.at(i)->calculate();
	}
	output = layers.at(layers.size() - 1)->getSofts(); // Softmax for the final layer
	predictedOutput.clear();
}

void NeuralNetwork::backPropagate() {
	double currentError = 0;
	double errorSum = 0;
	double tempSum = 0;
	double upDelta;
	double delta;
	actualError = 0;

	// Output - Hidden
	Layer curLayer(*layers.at(topSize - 1));
	for (int i = 0; i < layers.at(topSize - 1)->size(); i++) {
		currentError = crossEntropy.at(i);
		// Update neuron
		for (int j = 0; j < curLayer.getInputSize(); j++) {
			delta = curLayer.getNeuron(i)->getDelta(j);
			upDelta = lr * derivedError.at(i) * curLayer.getNeuron(i)->getDerSoft() * curLayer.getInputs().at(j) + delta * alpha;
			layers.at(topSize - 1)->getNeuron(i)->updateWeight(j, upDelta);
			layers.at(topSize - 1)->getNeuron(i)->setDelta(j, upDelta);
			errorSum += derivedError.at(i) * curLayer.getNeuron(i)->getDerSoft() * curLayer.getNeuron(i)->getWeight(j); // Needed in the next layer;
		}
		layers.at(topSize - 1)->getNeuron(i)->updateWbias(curLayer.getNeuron(i)->getBias() * br * derivedError.at(i));
		currentError = 0;
	}

	// Hidden - Hidden | Hidden Input
	for (int a = topSize - 2; a >= 0; a--) {
		curLayer = *layers.at(a);
		for (int i = 0; i < curLayer.size(); i++) {
			currentError = errorSum * curLayer.getNeuron(i)->getDerAct();
			// Update weights
			for (int j = 0; j < curLayer.getInputSize(); j++) {
				delta = curLayer.getNeuron(i)->getDelta(j);
				upDelta = lr * currentError * curLayer.getInputs().at(j) + delta * alpha;
				layers.at(a)->getNeuron(i)->updateWeight(j, upDelta);
				layers.at(a)->getNeuron(i)->setDelta(j, upDelta);
				delta = upDelta;
				tempSum += currentError * curLayer.getNeuron(i)->getWeight(j);
			}
			layers.at(a)->getNeuron(i)->updateWbias(curLayer.getNeuron(i)->getBias() * br * currentError);
		}
		errorSum = tempSum;
		tempSum = 0;
	}

}


void NeuralNetwork::train(map<vector<double>, vector<double>> trainingSet, int e, int batch) {
	// ******************************************************************************************************
	// * This function shall randomly select a batch containing k training values							*
	// * from the training set. This is needed since the cross entropy error must be an average				*
	// * of all training values. We therefore select a batch of training values to keep things efficient	*
	// ******************************************************************************************************
	epochs = 1;
	this->batch = batch;
	vector<vector<double>> keys;
	for (auto it : trainingSet) {
		keys.push_back(it.first);
	}
	int k = 1;
	do {
		while (epochs <= e) {
			cout << "Epoch nr: " << epochs << endl;
			resetErrors();
			random_shuffle(keys.begin(), keys.end());
			for (int i = 0; i < batch; i++) {
				inputs = keys.at(i);
				target = trainingSet.at(keys.at(i));
				feedForward();
				updateErrors();
			}
			historicalErrors.push_back(error);
			backPropagate();
			cout << "Error:\t" << error << endl << endl;
			epochs++;
		}
		cout << "Error:\t" << error << endl;
		cout << "\tCross:\t" << crossEntropy << endl;
		epochs = 1;
		//saveErrors("textfiles\\hist_err_" + to_string(k) + ".txt");
		
		// Should make an average of the 10 last errors,
		// and compare it with margin
		if (error > margin) resetNetwork();
		k++;
		historicalErrors.clear();
	} while (fabs(error) > margin);

	saveWeights("textfiles\\tuned_weights.txt");
}

void NeuralNetwork::updateErrors() {
	// Error check
	if (this->target.size() == 0)
		throw "No target for this neural network!\n";
	if (this->target.size() != this->output.size())
		throw "Error! target size is not the same as the output size!";
	// End error check


	// **********************************
	Layer outLayer(*layers.at(layers.size() - 1));
	for (int i = 0; i < outLayer.size(); i++) {
		double y = target.at(i);
		double a = output.at(i);
		if (a < 0.00001) a = 0.00001;
		if (a > 0.99999) a = 0.99999; 
		crossEntropy.at(i) += (1.0 / batch * ((y == 1) ? log(a) : log(1 - a)));
		derivedError.at(i) += (  (y - a));
		actualError += 1.0 / (batch * outLayer.size()) * fabs(y - a);
		error += crossEntropy.at(i) / outLayer.size();
	}
}

// Necessary after each epoch
void NeuralNetwork::resetErrors() {
	crossEntropy.clear();
	crossEntropy.resize(topology.at(topSize - 1));
	derivedError.clear();
	derivedError.resize(topology.at(topSize - 1));
	error = 0.0;
	actualError = 0.0;
}

void NeuralNetwork::saveWeights(string fname) {
	// File should be on the form:
	//
	// L 1
	// b_1 w_11 w_12 ... w_1n
	// b_2 w_21 w_22 ... w_2n
	//  :	 :   :	 ¨-.  :
	// b_m w_m1 w_m2 ... w_mn
	//  :
	// L j
	// ....
	ofstream file(fname);

	for (int i = 1; i < layers.size(); i++) {
		file << "L " << i + 1 << endl;
		for (int j = 0; j < layers.at(i)->size(); j++) {
			file << fixed << layers.at(i)->getNeuron(j)->getWbias() << "\t";
			for (int a = 0; a < layers.at(i)->getNeuron(j)->getWeightsSize(); a++) {
				file << layers.at(i)->getNeuron(j)->getWeight(a) << setprecision(8) << "\t";
			}
			file << endl;
		}
		file << endl;
	}

	file.flush();
	file.close();
}

void NeuralNetwork::loadWeights(string fname) {
	// See saveWeights()
	try {
		ifstream file(fname);
		if (file.fail()) throw "Error! Could not open file, when trying to update weights";

		string line = "";
		string word = "";
		string key = "";
		int layerIndex, biasIndex;
		int row = -1;
		int col = -1;
		while (getline(file, line)) {
			stringstream ss(line);
			while (ss >> word) {
				if (word == "L") {
					key = "L";
					ss >> word;
					layerIndex = stoi(word) - 1;
					row = -1;
				}
				else if (key == "L"){ // update indexed layer
					if (col == -1)
						layers.at(layerIndex)->getNeuron(row)->setWbias(stod(word));
					else
						layers.at(layerIndex)->getNeuron(row)->setWeight(col, stod(word));
					col++;
				}
			}
			col = -1, row++;
		}
		file.close();
	}
	catch (out_of_range & oor) {
		cerr << "Error! File not compatible, exception thrown: " << oor.what() << endl;
	}
}

void NeuralNetwork::saveErrors(string fname) {
	ofstream file(fname);

	for (int i = 0; i < historicalErrors.size(); i++) {
		file << historicalErrors.at(i) << endl;
	}
	file.flush();
	file.close();
}

// Converts the output into binary
vector<int> NeuralNetwork::getPredictedOutput() {
	double max = 0;
	predictedOutput.clear();
	for (int i = 0; i < output.size(); i++) {
		if (max < output.at(i)) max = output.at(i);
	}

	for (int i = 0; i < output.size(); i++) {
		predictedOutput.push_back((output.at(i) == max) ? 1 : 0);
	}
	return predictedOutput;
}

// Necessary if training for e epochs fails
void NeuralNetwork::resetNetwork() {
	layers.clear();
	Layer inlay(topology.at(0), topology.at(0));
	layers.push_back(make_shared<Layer>(inlay));
	for (int i = 1; i < topSize; i++) {
		Layer l(topology.at(i), topology.at(i - 1));
		layers.push_back(make_shared<Layer>(l));
	}
}