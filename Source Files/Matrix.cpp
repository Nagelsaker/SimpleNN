#include "Matrix.h"

// Using deep copy
Matrix::Matrix(Matrix* m) {
	this->rows = m->getRows();
	this->cols = m->getCols();
	this->empty = m->empty;
	this->weights.resize(m->getCols() * m->getRows());
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
		//	this->weights.push_back(m->getValue(i, j)); Lol will reverse the matrix
			this->setValue(i, j, m->getValue(i, j));
		}
	}
}

// Returns a transpose to this matrix
Matrix Matrix::transpose() {
	Matrix trans(cols, rows, empty);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			trans.setValue(j, i, this->getValue(i, j));
		}
	}
	return trans;
}

Matrix Matrix::diagonal() {
	if (this->getRows() != 1)
		throw "Error! Matrix-vector does not have legal dimensions!";

	Matrix diagonal(this->getCols(), this->getCols(), true);
	for (int i = 0; i < this->getCols(); i++) {
		diagonal.setValue(i, i, this->getValue(0, i));
	}
	return diagonal;
}

// .colnize() Makes a 1 x n matrix into a n x n matrix with all initial
// cols represented as expanded rows in the new matrix
Matrix Matrix::colnize(int colSize) {
	if (this->getRows() != 1)
		throw "Error! Matrix-vector does not have legal dimensions!";

	Matrix temp(this->getCols(), colSize, true);
	for (int i = 0; i < colSize; i++) {
		for (int j = 0; j < this->getRows(); j++) {
			temp.setValue(j, i, this->getValue(0, j));
		}
	}
	return temp;
}

void Matrix::setValue(int rpos, int cpos, double v) {
	//std::cout << "Set at " << rpos << ", " << cpos << std::endl;
	weights[cols*rpos + cpos] = v;
}

double Matrix::generateRand() {
	//double r = std::rand() % 100;
	//return r;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	return dis(gen);
}


// Overloaded operators
// Deep copy
Matrix & Matrix::operator=(const Matrix& rhs) {
	this->rows = rhs.getRows();
	this->cols = rhs.getCols();
	this->empty = rhs.empty;
	this->weights.resize(rhs.getRows() * rhs.getCols());
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			this->setValue(i, j, rhs.getValue(i, j));
		}
	}
	return *this;
}

Matrix & Matrix::operator-=(const Matrix & rhs) {
	if ((this->getCols() != rhs.getCols()) || (this->getRows() != rhs.getRows())) {
		std::string e = "Error! The matrices have different dimensions\n";
		throw e;
	}

	for (int i = 0; i < this->getRows(); i++) {
		for (int j = 0; j < this->getCols(); j++) {
			this->setValue(i, j, this->getValue(i, j) - rhs.getValue(i, j));
		}
	}
	return *this;
}

Matrix operator-(const Matrix & lhs, const Matrix & rhs) {
	Matrix sum(lhs);
	sum -= rhs;
	return sum;
}

Matrix & Matrix::operator+=(const Matrix & rhs) {
	if ((this->getCols() != rhs.getCols()) || (this->getRows() != rhs.getRows())) {
		std::string e = "Error! The matrices have different dimensions\n";
		throw e;
	}
	for (int i = 0; i < this->getCols(); i++) {
		for (int j = 0; j < this->getRows(); j++) {
			this->setValue(i, j, this->getValue(i, j) + rhs.getValue(i, j));
		}
	}
	return *this;
}

Matrix operator+(const Matrix & lhs, const Matrix & rhs) {
	Matrix sum(lhs);
	sum += rhs;
	return sum;
}

Matrix & Matrix::operator*=(const Matrix & rhs) {
	if (this->getCols() != rhs.getRows()) {
		std::string e = "Error! The matrices have different dimensions\n";
		throw e;
	}

	Matrix temp(this->getRows(), rhs.getCols(), true);
	for (int i = 0; i < temp.getRows(); i++) {
		for (int j = 0; j < temp.getCols(); j++) {
			double newVal = 0;
			for (int l = 0; l < this->getCols(); l++) {
				newVal += this->getValue(i, l) * rhs.getValue(l, j);
			}
			temp.setValue(i, j, newVal);
		}
	}
	*this = temp;
	return *this;
}

Matrix & Matrix::operator *=(const double scalar) {
	for (int i = 0; i < this->getRows(); i++) {
		for (int j = 0; j < this->getCols(); j++) {
			this->setValue(i, j, this->getValue(i, j) * scalar);
		}
	}
	return *this;
}

Matrix operator*(const Matrix & lhs, const Matrix & rhs) {
	Matrix prod(lhs);
	prod *= rhs;
	return prod;
}

Matrix operator*(const double scalar, const Matrix & rhs) {
	Matrix temp(rhs);
	return temp *= scalar;
};


Matrix operator*(const Matrix & lhs, const double scalar) {
	Matrix temp(lhs);
	return temp *= lhs;
}

