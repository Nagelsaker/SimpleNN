// Currently not in use!
// I created this class to enhance my understanding of the math behind
// neural networks. Though it works in theory, this class introduces way too many
// nested for loops causing the program to run substantially slower.

#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

class Matrix {
private:
	int rows;
	int cols;
	bool empty;
	double generateRand();
	std::vector<double> weights;
public:
	Matrix(unsigned int r, unsigned int c, bool e) : rows(r), cols(c), empty(e) {
		for (int i = 0; i < (rows * cols); i++) {
			double r = empty == true ? 0.00 : this->generateRand();
			weights.push_back(r);
		}
	};
	Matrix(Matrix* m);
	Matrix(std::vector<double> * m) : Matrix(1, m->size(), true) {
		for (int i = 0; i < m->size(); i++)
			this->setValue(0, i, m->at(i));
		//	weights.push_back(m->at(i));
	};
	

	void setValue(int r, int c, double v);
	Matrix transpose();
	Matrix diagonal();
	Matrix colnize(int colSize);

	double getValue(int rpos, int cpos) const { return weights.at(cols*rpos + cpos); };
	int getRows() const { return rows; };
	int getCols() const { return cols; };

	// Overloaded operators
	friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
		for (unsigned int i = 0; i < m.getRows(); i++) {
			for (unsigned int j = 0; j < m.getCols(); j++) {
				os << m.getValue(i, j) << "\t";
			}
			os << std::endl;
		}
		return os;
	}

	Matrix & operator=(const Matrix &rhs);
	Matrix & operator-=(const Matrix & rhs);
	Matrix & operator+=(const Matrix & rhs);
	Matrix & operator *=(const Matrix & rhs);
	Matrix & operator *=(const double scalar);
	friend Matrix operator-(const Matrix & lhs, const Matrix & rhs);
	friend Matrix operator+(const Matrix & lhs, const Matrix & rhs);
	friend Matrix operator*(const Matrix & lhs, const Matrix & rhs);
	friend Matrix operator*(const double scalar, const Matrix & rhs);
	friend Matrix operator*(const Matrix & lhs, const double scalar);
};

