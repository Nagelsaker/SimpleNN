#include "NeuralNetwork.h"
#include "utils.h"
#include "Mnist.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <map>


// SoftMax
// using softmax, the network works using following hyperparameters
// lr = 0.35, br = 0.1, aplha = 0.9
// batch size = 1, epochs = 100 000
// 
// Sigmoid
// Seriously more difficult choosing hyperparameters 

using namespace std;

int main() {
	srand(time(NULL));
	vector<int> topology;
	topology.push_back(10);
	topology.push_back(8);
	topology.push_back(10);

	map<vector<double>, vector<double>> trainingSet3;
	trainingSet3[{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
	trainingSet3[{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }] = { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
	trainingSet3[{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
	trainingSet3[{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }] = { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
	trainingSet3[{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
	trainingSet3[{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }] = { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
	trainingSet3[{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
	trainingSet3[{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
	trainingSet3[{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	trainingSet3[{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// in, out
	cout << "This program trains a simple neural network" << endl;
	//Mnist mnist;

	enum Choices { TRAIN = 1, LOAD };
	cout << "Train network:\t1\nTest network:\t2" << endl;

	int user;
	cin >> user;

	try {
		NeuralNetwork nn(topology);
		nn.setLearningRate(0.01); // 0.01 - 0.9 (0.05)
		nn.setBiasLR(0.1); // 0.1 - 0.9 (0.1)
		nn.setMargin(0.02); 
		switch (user) {
		case TRAIN:
			cout << "Training network..." << endl;
			nn.train(trainingSet3, 200, 1);
			cout << endl <<  "Weights of the trained network:" << endl;
			cout << "\n\nNeural Network\n" << nn << endl;
			break;
		case LOAD:
			cout << "Loading weights..." << endl;
			nn.loadWeights("textfiles\\tuned_weights.txt");

			// Testing the network
			nn.feedForward({ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
			for (int i = 0; i < trainingSet3.size() - 1; i++) {
				cout << "Input:\t" << utils::decypher(nn.getInput()) << endl;
				cout << "nn thinks the next value is:\t" << utils::decypher(nn.getPredictedOutput()) << endl;
				nn.feedForward(nn.getOutput());
			}

			break;
		}
	}
	catch (string e) {
		cout << e << endl;
	}
	system("pause");
}
