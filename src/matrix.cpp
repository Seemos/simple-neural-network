#include <vector>
#include <iostream>
#include <random>
#include <cmath>
#include <assert.h>
#include "matrix.h"

matrix create_matrix(unsigned int n_rows, unsigned int n_cols)
{
	matrix mat;
	mat.n_cols = n_cols;
	mat.n_rows = n_rows;

	mat.values.resize(n_rows);
	for (unsigned int i = 0; i < n_rows; i++) {
		mat.values[i].resize(n_cols);
	}

	return mat;
}
matrix create_matrix(unsigned int n_rows, unsigned int n_cols, double value)
{
	matrix mat;
	mat.n_cols = n_cols;
	mat.n_rows = n_rows;

	mat.values.resize(n_rows);
	for (unsigned int i = 0; i < n_rows; i++) {
		mat.values[i].resize(n_cols, value);
	}

	return mat;
}
matrix create_random_matrix(unsigned int n_rows, unsigned int n_cols, double lower_bound, double upper_bound) {

	std::uniform_real_distribution<double> distribution (lower_bound, upper_bound);
	std::default_random_engine engine;

	matrix mat_res = create_matrix(n_rows, n_cols);

	for (unsigned i = 0; i < n_rows; i++) {
		for (unsigned j = 0; j < n_cols; j++) {
			mat_res.values[i][j] = distribution(engine);
		}
	}

	return mat_res;
}
matrix create_matrix_from_vector(const std::vector<std::vector<long double>>& vec) {
	unsigned rows = vec.size();
	unsigned cols = vec[0].size();
	matrix mat_res = create_matrix(rows, cols);
	mat_res.values = vec;
	return mat_res;
}
matrix diag(const std::vector<long double>& vec) {
	unsigned n_rows = vec.size();
	matrix mat_res = create_matrix(n_rows, n_rows, 0);
	for (unsigned i = 0; i < n_rows; i++) {
		mat_res.values[i][i] = vec[i];
	}
	return mat_res;
}

//----------------------------------------------------
//matrix operations on single matrix
//----------------------------------------------------
matrix transpose(const matrix& mat) {

	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = create_matrix(cols, rows);
	for (unsigned i = 0; i < cols; i++) {
		for (unsigned j = 0; j < rows; j++) {
			mat_res.values[i][j] = mat.values[j][i];
		}
	}

	return mat_res;
}
matrix pow(const matrix& mat, double exponent) {
	matrix mat_res = mat;
	for (unsigned i = 0; i < mat.n_rows; i++) {
		for (unsigned j = 0; j < mat.n_cols; j++)
		{
			mat_res.values[i][j] = pow(mat_res.values[i][j], exponent);
		}
	}
	return mat_res;
}
long double trace(const matrix& mat) {
	double val_traced = 0;
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;
	if (cols < rows) {
		for (unsigned i = 0; i < cols; i++) {
			val_traced += mat.values[i][i];
		}
	}
	else
	{
		for (unsigned i = 0; i < rows; i++) {
			val_traced += mat.values[i][i];
		}
	}
	return val_traced;
}
long double frobenius_norm(const matrix& mat) {
	long double norm = 0;
	for (unsigned i = 0; i < mat.n_rows; i++) {
		for (unsigned j = 0; j < mat.n_cols; j++) {
			norm += pow(mat.values[i][j], 2);
		}
	}
	return sqrt(norm);
}


//----------------------------------------------------
//matrix and matrix operators
//----------------------------------------------------
matrix dot(const matrix& mat_left, const matrix& mat_right) {

	unsigned rows = mat_left.n_rows;
	unsigned cols = mat_right.n_cols;
	unsigned lost_dim = mat_right.n_rows;

	matrix mat_res = create_matrix(rows, cols);

	for (unsigned i = 0; i < rows; ++i) {
		for (unsigned j = 0; j < cols; ++j) {
			for (unsigned k = 0; k < lost_dim; ++k) {
				mat_res.values[i][j] += mat_left.values[i][k] * mat_right.values[k][j];
			}
		}
	}

	return mat_res;
}
matrix operator+ (const matrix& mat_left, const matrix& mat_right) {

	unsigned rows = mat_left.n_rows;
	unsigned cols = mat_left.n_cols;

	matrix mat_res = create_matrix(rows, cols);
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] = mat_left.values[i][j] + mat_right.values[i][j];
		}
	}

	return mat_res;
}
matrix operator- (const matrix& mat_left, const matrix& mat_right) {

	unsigned rows = mat_left.n_rows;
	unsigned cols = mat_left.n_cols;

	matrix mat_res = create_matrix(rows, cols);
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] = mat_left.values[i][j] - mat_right.values[i][j];
		}
	}

	return mat_res;
}
matrix operator/ (const matrix& mat_left, const matrix& mat_right) {

	unsigned rows = mat_left.n_rows;
	unsigned cols = mat_left.n_cols;

	matrix mat_res = create_matrix(rows, cols);
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] = mat_left.values[i][j] / mat_right.values[i][j];
		}
	}

	return mat_res;
}
matrix operator* (const matrix& mat_left, const matrix& mat_right) {

	matrix mat_res = mat_left;

	for (unsigned i = 0; i < mat_left.n_rows; ++i) {
		for (unsigned j = 0; j < mat_left.n_cols; ++j) {
			mat_res.values[i][j] *= mat_right.values[i][j];
		}
	}

	return mat_res;
}

void operator+= (matrix& mat_left, const matrix& mat_right) {
	unsigned rows = mat_left.n_rows;
	unsigned cols = mat_left.n_cols;

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			mat_left.values[i][j] += mat_right.values[i][j];
		}
	}
}
void operator-= (matrix& mat_left, const matrix& mat_right) {
	unsigned rows = mat_left.n_rows;
	unsigned cols = mat_left.n_cols;

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			mat_left.values[i][j] -= mat_right.values[i][j];
		}
	}
}
void operator/= (matrix& mat_left, const matrix& mat_right) {
	unsigned rows = mat_left.n_rows;
	unsigned cols = mat_left.n_cols;

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			mat_left.values[i][j] /= mat_right.values[i][j];
		}
	}
}

//----------------------------------------------------
//matrix and vector operators
//----------------------------------------------------
matrix operator+ (const matrix& mat, const std::vector<long double>& vec) {
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = create_matrix(rows, cols);

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] = mat.values[i][j] + vec[i];
		}
	}

	return mat_res;
}
matrix operator- (const matrix& mat, const std::vector<long double>& vec) {
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = create_matrix(rows, cols);

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] = mat.values[i][j] - vec[i];
		}
	}

	return mat_res;
}
matrix operator* (const matrix& mat, const std::vector<long double>& vec) {
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = create_matrix(rows, cols);

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] = mat.values[i][j] * vec[j];
		}
	}

	return mat_res;
}
matrix operator/ (const matrix& mat, const std::vector<long double>& vec) {
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = create_matrix(rows, cols);

	for (unsigned int i = 0; i   < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] = mat.values[i][j] / vec[i];
		}
	}

	return mat_res;
}

//----------------------------------------------------
//matrix and scalar operators
//----------------------------------------------------
matrix operator+ (const matrix& mat, const long double scalar) {
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = mat;

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] += scalar;
 		}
	}

	return mat_res;
}
matrix operator- (const matrix& mat, const long double scalar) {
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = mat;

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] -= scalar;
		}
	}

	return mat_res;
}
matrix operator* (const matrix& mat, const long double scalar) {
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = mat;

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] *= scalar;
		}
	}

	return mat_res;
}
matrix operator/ (const matrix& mat, const long double scalar) {
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = mat;

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			mat_res.values[i][j] /= scalar;
		}
	}

	return mat_res;
}

matrix apply_function(const matrix& mat, long double(*function)(long double)) {
	unsigned rows = mat.n_rows;
	unsigned cols = mat.n_cols;

	matrix mat_res = mat;

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			mat_res.values[i][j] = function(mat_res.values[i][j]);
		}
	}

	return mat_res;
}

void print_matrix(const matrix& ref)
{
	for (unsigned int i = 0; i < ref.n_rows; ++i) {
		for (unsigned int j = 0; j < ref.n_cols; ++j) {
			std::cout << ref.values[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}