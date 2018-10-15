#include "Mnist.h"
#include "utils.h"


Mnist::Mnist(string in, string out) {
	infname = in, outfname = out;
	readFile(outfname);
	readFile(infname);
}


Mnist::~Mnist() {
	delete[] buffer;
}

void Mnist::initialize(string in, string out) {
	infname = in, outfname = out;
	readFile(outfname);
	readFile(infname);
}

void Mnist::readFile(string fname) {
	// Read magic number
	// Read next x lines, containing the size of all x dimensions
	ifstream file(fname, ios::in | ios::binary | ios::ate);
	if (file.fail()) throw "Could not read from " + fname;

	auto size = file.tellg();

	// By some reason I must flip the int after the code has read it
	// Possibly since I use an Intel processor??
	// Others have read the entire file at once, or simply read it partwise
	// I think partwise is the way to go

	// The buffer value must be reversed, let's look at the magic number:
	// It should be 0x00000801 = 2049 (int)
	// However it reads out as 17301504 (int) = 0x10800000

	// *** Header ***
	// Magic number
	file.seekg(file.beg);
	file.read((char*)&magic, 4);
	magic = reverseHead(magic);

	// Dimensions
	if (magic == 2049) dimensions = 1;
	else if (magic == 2051) dimensions = 3;
	else throw "Error reading the magic number!";
	sizeOfDim.resize(dimensions);
	for (int i = 0; i < dimensions; i++) {
		file.read((char*)&sizeOfDim.at(i), 4);
		sizeOfDim.at(i) = reverseHead(sizeOfDim.at(i));
	}

	// *** Read and store values ***
	// One dimensional - output layer
	if (magic == 2049) {
		for (int i = 0; i < 60000; i++) {
			file.read((char*)&tval, 1);
			//tval = reverseVal(tval);
			output.push_back(utils::cypher(tval, 10));
		}
	}
	// Three dimensional - input layer
	else {
		int picSize = sizeOfDim.at(1) * sizeOfDim.at(2);
		setSize = 60000; /*sizeOfDim.at(0);*/
		for (int i = 0; i < setSize; i++) {
			vector<double> tempVec;
			for (int j = 0; j < picSize; j++) {
				file.read((char*)&tval, 1);
				tempVec.push_back(tval);
			}
			input.push_back(tempVec);
			mapping[tempVec] = output.at(i);

		}
	}

	file.close();
}

int Mnist::reverseHead(int i) {
	unsigned char c1, c2, c3, c4;

	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

map<vector<double>, vector<double>> Mnist::getMapping() {
	return mapping;
}