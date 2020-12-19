#ifndef MATRIX_H
#define MATRIX_H

#include<vector>

//----------------------------------------------------
//matrix struct definition
//----------------------------------------------------
typedef struct 
{
	unsigned int n_rows;
	unsigned int n_cols;
	std::vector<std::vector<long double>> values;
} matrix;


//----------------------------------------------------
//matrix create functions
//----------------------------------------------------
matrix create_matrix(unsigned int n_rows, unsigned int n_cols);
matrix create_matrix(unsigned int n_rows, unsigned int n_cols, double value);
matrix create_random_matrix(unsigned int n_rows, unsigned int n_cols, double lower_bound = 0, double upper_bound = 1);
matrix create_matrix_from_vector(const std::vector<std::vector<long double>>& vec);
matrix diag(const std::vector<long double>& vec);



//----------------------------------------------------
//matrix operations on single matrix
//----------------------------------------------------
matrix transpose(const matrix& mat);
matrix pow(const matrix& mat, const double exponent);
long double trace(const matrix& mat);
long double frobenius_norm(const matrix& mat);



//----------------------------------------------------
//matrix and matrix operators
//----------------------------------------------------
matrix dot(const matrix& mat_left, const matrix& mat_right);
matrix operator+ (const matrix& mat_left, const matrix& mat_right);
matrix operator- (const matrix& mat_left, const matrix& mat_right);
matrix operator* (const matrix& mat_left, const matrix& mat_right);
matrix operator/ (const matrix& mat_left, const matrix& mat_right);

void operator+= (matrix& mat_left, const matrix& mat_right);
void operator-= (matrix& mat_left, const matrix& mat_right);
void operator/= (matrix& mat_left, const matrix& mat_right);



//----------------------------------------------------
//matrix and vector operators
//----------------------------------------------------
matrix operator+ (const matrix& mat, const std::vector<long double>& vec);
matrix operator- (const matrix& mat, const std::vector<long double>& vec);
matrix operator* (const matrix& mat, const std::vector<long double>& vec);
matrix operator/ (const matrix& mat, const std::vector<long double>& vec);



//----------------------------------------------------
//matrix and scalar operators
//----------------------------------------------------
matrix operator+ (const matrix& mat, const long double scalar);
matrix operator- (const matrix& mat, const long double scalar);
matrix operator* (const matrix& mat, const long double scalar);
matrix operator/ (const matrix& mat, const long double scalar);



matrix apply_function(const matrix& mat, long double(*function)(long double) );
void print_matrix(const matrix& ref);

#endif