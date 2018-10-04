#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;

template<class DataType>
class Matrix
{
public:
	class Index
	{
	public:
		int n_cols;
		int i;
		DataType* a;
		Index(int cols, int ii, DataType* aa):n_cols(cols), i(ii), a(aa){};
		DataType& operator [](int j)
		{
			if(j < 0 || j >= n_cols)
			{
				cout << "Error using Matrix<DataType>[i][j]:" << endl
					 << "j is out of bande [0, cols]!" << endl;
				exit(-1);
			}
			return a[i*n_cols+j];
		}
		DataType operator [](int j)const
		{
			if(j < 0 || j >= n_cols)
			{
				cout << "Error using Matrix<DataType>[i][j]:" << endl
					 << "j is out of bande [0, cols]!" << endl;
				exit(-1);
			}
			return a[i*n_cols+j];
		}
	};

public:
	static string cout2string(const DataType& element)
	{
	    ostringstream oss;
	    oss << element;
	    return oss.str();
	}

public:
	int n_rows = 0;
	int n_cols = 0;
	DataType *data = NULL;

public:
	Matrix(){}
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, const DataType& value);
	Matrix(const Matrix<DataType>& A);
	Matrix(const vector<DataType>& x);
	Matrix(const vector< vector<DataType> >& X);
	Matrix(const initializer_list<DataType>& x);
	Matrix(const initializer_list< initializer_list<DataType> >& X);
	Matrix(const DataType& x);
	~Matrix();

	void clear();
	bool empty()const;
	int rows()const;
	int cols()const;

	int rank()const;
	DataType trace()const;
	DataType det()const;
	DataType max()const;
	DataType min()const;

	Matrix<DataType> t()const;
	Matrix<DataType> inv()const;
	Matrix<DataType> reshape(int m, int n)const;
	Matrix<DataType> repmat(int m, int n)const;
	Matrix<DataType> repelem(int m, int n)const;

	Matrix<DataType>& operator =(const Matrix<DataType>& A);
	Index operator [](int i);
	Index operator [](int i)const;
	Matrix<DataType>  operator -()const;

	template<class ElemType>
	friend ostream& operator <<(ostream& o, Matrix<ElemType> A);

	template<class ElemType>
	Matrix<ElemType> friend operator +(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator -(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator *(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator %(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator /(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator ^(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator +(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator -(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator *(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator %(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator /(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator ^(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator +(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator -(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator *(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator %(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator /(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator ^(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator >(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator <(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator >=(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator <=(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator ==(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator !=(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>

	Matrix<bool> friend operator >(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator <(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator >=(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator <=(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator ==(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator !=(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator >(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator <(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator >=(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator <=(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator ==(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator !=(const ElemType& b, const Matrix<ElemType>& A);
};


Matrix<double> to(double start, double step, double end);
Matrix<double> to(double start, double end);
Matrix<double> zeros(int rows, int cols);
Matrix<double> zeros(int n);

template<class DataType>
Matrix<double> zeros(const Matrix<DataType>& A);

Matrix<double> ones(int rows, int cols);
Matrix<double> ones(int n);

template<class DataType>
Matrix<double> ones(const Matrix<DataType>& A);


Matrix<double> eye(int rows, int cols);
Matrix<double> eye(int n);

template<class DataType>
Matrix<double> eye(const Matrix<DataType>& A);

Matrix<double> rand(int rows, int cols);
Matrix<double> rand(int n);

template<class DataType>
Matrix<double> rand(const Matrix<DataType>& A);


Matrix<double> randn(int rows, int cols);
Matrix<double> randn(int n);

template<class DataType>
Matrix<double> randn(const Matrix<DataType>& A);

template<class DataType>
Matrix<DataType> reshape(const Matrix<DataType>& A, int m, int n);

template<class DataType>
Matrix<DataType> repmat(const Matrix<DataType>& A, int m, int n);

template<class DataType>
Matrix<DataType> repelem(const Matrix<DataType>& A, int m, int n);

template<class DataType>
bool same_size(const Matrix<DataType>& A, const Matrix<DataType>& B);


Matrix<double> sin(const Matrix<double>& A);
Matrix<double> cos(const Matrix<double>& A);
Matrix<double> tan(const Matrix<double>& A);
Matrix<double> asin(const Matrix<double>& A);
Matrix<double> acos(const Matrix<double>& A);
Matrix<double> atan(const Matrix<double>& A);
Matrix<double> atan2(const Matrix<double>& Y, const Matrix<double>& X);
Matrix<double> sinh(const Matrix<double>& A);
Matrix<double> cosh(const Matrix<double>& A);
Matrix<double> tanh(const Matrix<double>& A);
Matrix<double> asinh(const Matrix<double>& A);
Matrix<double> acosh(const Matrix<double>& A);
Matrix<double> atanh(const Matrix<double>& A);
Matrix<double> exp(const Matrix<double>& A);
Matrix<double> log(const Matrix<double>& A);
Matrix<double> log2(const Matrix<double>& A);
Matrix<double> log10(const Matrix<double>& A);
Matrix<double> abs(const Matrix<double>& A);
Matrix<int> floor(const Matrix<double>& A);
Matrix<int> ceil(const Matrix<double>& A);
Matrix<int> round(const Matrix<double>& A);

// Matrix<DataType> fix(const Matrix<DataType>& A);

Matrix<double> linspace(double start, double end, int n = 100);

template<class DataType>
vector< Matrix<DataType> > meshgrid(Matrix<DataType> x, Matrix<DataType> y);

#include "matrix.cpp"

#endif