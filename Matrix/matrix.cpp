#ifdef MATRIX_H

template<class DataType>
Matrix<DataType>::Matrix(int rows, int cols)
{
	n_rows = rows;
	n_cols = cols;
	data = new DataType[rows * cols];
}

template<class DataType>
Matrix<DataType>::Matrix(int rows, int cols, const DataType& value)
{
	n_rows = rows;
	n_cols = cols;
	data = new DataType[rows * cols];
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			data[i*cols+j] = value;
		}
	}
}

template<class DataType>
Matrix<DataType>::Matrix(const Matrix<DataType>& A)
{
	n_rows = A.n_rows;
	n_cols = A.n_cols;
	data = new DataType[n_rows * n_cols];
	for(int i = 0; i < n_rows; i++)
	{
		for(int j = 0; j < n_cols; j++)
		{
			data[i*n_cols+j] = A.data[i*n_cols+j];
		}
	}
}

template<class DataType>
Matrix<DataType>::Matrix(const vector<DataType>& x)
{
	n_rows = 1;
	n_cols = x.size();
	data = new DataType[n_rows * n_cols];
	for(int j = 0; j < n_cols; j++)
	{
		data[j] = x[j];
	}
}

template<class DataType>
Matrix<DataType>::Matrix(const vector< vector<DataType> >& X)
{
	n_rows = X.size();
	if(n_rows == 0)
	{
		return;
	}

	n_cols = X[0].size();
	data = new DataType[n_rows * n_cols];
	for(int i = 0; i < n_rows; i++)
	{
		if(X[i].size() != n_cols)
		{
			cout << "Warning in \'Matrix<DataType>::Matrix<DataType>(const vector< vector<double> >& X)\'" << endl
				 << "Each vector<double> doesn't has the same size." << endl;
			clear();
			return;
		}
		for(int j = 0; j < n_cols; j++)
		{
			data[i*n_cols+j] = X[i][j];
		}
	}
}

template<class DataType>
Matrix<DataType>::Matrix(const initializer_list<DataType>& x)
{
	n_cols = x.size();
	if(!n_cols)
	{
		return;
	}
	n_rows = 1;

	data = new DataType[n_rows * n_cols];
	typename initializer_list<DataType>::const_iterator it = x.begin();
	for(int j = 0; j < n_cols; j++, it++)
	{
		data[j] = *it;
	}
}

template<class DataType>
Matrix<DataType>::Matrix(const initializer_list< initializer_list<DataType> >& X)
{
	n_rows = X.size();
	if(n_rows == 0)
	{
		return;
	}

	typename initializer_list< initializer_list<DataType> >::const_iterator it = X.begin();
	n_cols = it->size();
	data = new DataType[n_rows * n_cols];
	for(int i = 0; i < n_rows; i++, it++)
	{
		if(it->size() != n_cols)
		{
			cout << "Warning in \'Matrix<DataType>::Matrix<DataType>(const initializer_list< initializer_list<double> >& X)\'" << endl
				 << "Each initializer_list<double> doesn't has the same size." << endl;
			clear();
			return;
		}
		typename initializer_list<DataType>::iterator subit = it->begin();
		for(int j = 0; j < n_cols; j++, subit++)
		{
			data[i*n_cols+j] = *subit;
		}
	}
}

template<class DataType>
Matrix<DataType>::Matrix(const DataType& x)
{
	n_rows = 1;
	n_cols = 1;
	data = new DataType[n_rows * n_cols];
	data[0] = x;
}

template<class DataType>
Matrix<DataType>::~Matrix()
{
	n_rows = 0;
	n_cols = 0;
	if(data)
	{
		delete[] data;
		data = NULL;
	}
}

template<class DataType>
void Matrix<DataType>::clear()
{
	n_rows = 0;
	n_cols = 0;
	if(data)
	{
		delete[] data;
		data = NULL;
	}
}

template<class DataType>
Matrix<DataType>& Matrix<DataType>::operator =(const Matrix<DataType>& A)
{
	clear();
	n_rows = A.n_rows;
	n_cols = A.n_cols;

	data = new DataType[n_rows * n_cols];

	for(int i = 0; i < n_rows; i++)
	{
		for(int j = 0; j < n_cols; j++)
		{
			data[i*n_cols+j] = A.data[i*n_cols+j];
		}
	}

	return *this;
}

template<class DataType>
typename Matrix<DataType>::Index Matrix<DataType>::operator [](int i)
{
	if(i < 0 || i >= n_rows)
	{
		cout << "Error using Matrix<DataType>[i][j]:" << endl
			 << "i is out of bande [0, rows]!" << endl;
		exit(-1);
	}
	
	return Index(n_cols, i, data);
}

template<class DataType>
typename Matrix<DataType>::Index Matrix<DataType>::operator [](int i)const
{
	if(i < 0 || i >= n_rows)
	{
		cout << "Error using Matrix<DataType>[i][j]:" << endl
			 << "i is out of bande [0, rows]!" << endl;
		exit(-1);
	}

	return Index(n_cols, i, data);
}

template<class DataType>
int Matrix<DataType>::rows()const
{
	return n_rows;
}

template<class DataType>
int Matrix<DataType>::cols()const
{
	return n_cols;
}

template<class DataType>
bool Matrix<DataType>::empty()const
{
	return (n_rows == 0 || n_cols == 0);
}

template<class DataType>
DataType Matrix<DataType>::trace()const
{
	if(empty())
	{
		cout << "Error using \'double trace()const\':" << endl
			 << "Matrix<DataType> is empty!" << endl;
		exit(-1);
	}
	if(n_rows != n_cols)
	{
		cout << "Error using \'double trace()const\':" << endl
			 << "Matrix<DataType> must be square!" << endl;
		exit(-1);
	}

	DataType tr = (*this)[0][0];
	for(int i = 1; i < n_rows; i++)
	{
		tr += (*this)[i][i];
	}

	return tr;
}

template<class DataType>
Matrix<DataType> Matrix<DataType>::t()const
{
	Matrix<DataType> A(n_cols, n_rows);
	for(int i = 0; i < A.n_rows; i++)
	{
		for(int j = 0; j < A.n_cols; j++)
		{
			A[i][j] = (*this)[j][i];
		}
	}

	return A;
}

template<class DataType>
Matrix<DataType> Matrix<DataType>::reshape(int m, int n)const
{
	if(m * n != n_rows * n_cols)
	{
		cout << "Error using \'A.reshape(m ,n)\'" << endl
			 << "m * n != A.n_rows * A.n_cols" << endl;
		exit(-1);
	}

	if(m == n_rows)
	{
		return *this;
	}

	Matrix<DataType> C(m, n);
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			int N = i * n + j;
			C[i][j] = (*this)[N / n_cols][N % n_cols];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> Matrix<DataType>::repmat(int m, int n)const
{
	if(m == 1 && n == 1)
	{
		return *this;
	}

	Matrix<DataType> B(m * n_rows, n * n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = (*this)[i % m][j % n];
		}
	}

	return B;
}

template<class DataType>
Matrix<DataType> Matrix<DataType>::repelem(int m, int n)const
{
	if(m == 1 && n == 1)
	{
		return (*this);
	}

	Matrix<DataType> B(m * n_rows, n * n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = (*this)[i / m][j / n];
		}
	}

	return B;
}

template<class DataType>
DataType Matrix<DataType>::max()const
{
	DataType Max = (*this)[0][0];
	for(int i = 0; i < n_rows; i++)
	{
		for(int j = 0; j < n_cols; j++)
		{
			if( (*this)[i][j] > Max )
			{
				Max = (*this)[i][j];
			}
		}
	}

	return Max;
}

template<class DataType>
DataType Matrix<DataType>::min()const
{
	DataType Min = (*this)[0][0];
	for(int i = 0; i < n_rows; i++)
	{
		for(int j = 0; j < n_cols; j++)
		{
			if( (*this)[i][j] < Min )
			{
				Min = (*this)[i][j];
			}
		}
	}

	return Min;
}

template<class DataType>
Matrix<DataType> Matrix<DataType>::operator -()const
{
	Matrix<DataType> A(n_rows, n_cols);
	for(int i = 0; i < A.n_rows; i++)
	{
		for(int j = 0; j < A.n_cols; j++)
		{
			A[i][j] = -(*this)[i][j];
		}
	}

	return A;
}

template<class DataType>
Matrix<DataType> operator +(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A + B\':" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator -(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A - B\':" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator *(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(A.n_cols != B.n_rows)
	{
		cout << "Error using \'A * B\':" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<DataType> C(A.n_rows, B.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			double S = 0;
			for(int k = 0; k < A.n_cols; k++)
			{
				S += A[i][k] * B[k][j];
			}
			C[i][j] = S;
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator %(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A % B\':" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = A[i][j] * B[i][j];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator ^(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A ^ B\':" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = pow(A[i][j], B[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator +(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = A[i][j] + b;
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator -(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = A[i][j] - b;
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator *(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = A[i][j] * b;
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator %(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = A[i][j] * b;
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator /(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = A[i][j] / b;
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator ^(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<DataType> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = pow(A[i][j], b);
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator +(const DataType& a, const Matrix<DataType>& B)
{
	Matrix<DataType> C(B.n_rows, B.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = a + B[i][j];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator -(const DataType& a, const Matrix<DataType>& B)
{
	Matrix<DataType> C(B.n_rows, B.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = a - B[i][j];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator *(const DataType& a, const Matrix<DataType>& B)
{
	Matrix<DataType> C(B.n_rows, B.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = a * B[i][j];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator %(const DataType& a, const Matrix<DataType>& B)
{
	Matrix<DataType> C(B.n_rows, B.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = a * B[i][j];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator /(const DataType& a, const Matrix<DataType>& B)
{
	Matrix<DataType> C(B.n_rows, B.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = a / B[i][j];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> operator ^(const DataType& a, const Matrix<DataType>& B)
{
	Matrix<DataType> C(B.n_rows, B.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_cols; j++)
		{
			C[i][j] = pow(a, B[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator >(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A > B\'" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] > B[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator <(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A < B\'" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] < B[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator >=(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A >= B\'" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] >= B[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator <=(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A <= B\'" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] <= B[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator ==(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A == B\'" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] == B[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator !=(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	if(!same_size(A, B))
	{
		cout << "Error using \'A != B\'" << endl
			 << "Matrix<DataType> dimension is not match!" << endl;
		exit(-1);
	}

	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] != B[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator >(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] > b);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator <(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] < b);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator >=(const Matrix<DataType>& A, const DataType b)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] >= b);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator <=(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] <= b);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator ==(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] == b);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator !=(const Matrix<DataType>& A, const DataType& b)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (A[i][j] != b);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator >(const DataType& b, const Matrix<DataType>& A)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (b > A[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator <(const DataType& b, const Matrix<DataType>& A)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (b < A[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator >=(const DataType& b, const Matrix<DataType>& A)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (b >= A[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator <=(const DataType& b, const Matrix<DataType>& A)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (b <= A[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator ==(const DataType& b, const Matrix<DataType>& A)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (b == A[i][j]);
		}
	}

	return C;
}

template<class DataType>
Matrix<bool> operator !=(const DataType& b, const Matrix<DataType>& A)
{
	Matrix<bool> C(A.n_rows, A.n_cols);
	for(int i = 0; i < C.n_rows; i++)
	{
		for(int j = 0; j < C.n_rows; j++)
		{
			C[i][j] = (b != A[i][j]);
		}
	}

	return C;
}

Matrix<double> to(double start, double step, double end)
{
	int n = floor((end-start)/step);
	Matrix<double> x(1, n+1);
	
	x[0][0] = start;
	for(int i = 1; i < n; i++)
	{
		x[0][i] = x[0][i-1] + step;
	}
	x[0][n] = end;

	return x;
}

Matrix<double> to(double start, double end)
{
	return to(start, 1.0, end);
}

Matrix<double> zeros(int rows, int cols)
{
	return Matrix<double>(rows, cols, 0.0);
}

Matrix<double> zeros(int n)
{
	return Matrix<double>(n, n, 0.0);
}

Matrix<double> zeros(const Matrix<double>& A)
{
	return Matrix<double>(A.n_rows, A.n_cols, 0.0);
}

Matrix<double> ones(int rows, int cols)
{
	return Matrix<double>(rows, cols, 1.0);
}

Matrix<double> ones(int n)
{
	return Matrix<double>(n, n, 1.0);
}

template<class DataType>
Matrix<double> ones(const Matrix<DataType>& A)
{
	return Matrix<double>(A.n_rows, A.n_cols, 1.0);
}

Matrix<double> eye(int rows, int cols)
{
	Matrix<double> In(rows, cols, 0.0);
	int n = std::min(rows, cols);
	for(int i = 0; i < n; i++)
	{
		In[i][i] = 1.0;
	}

	return In;
}

Matrix<double> eye(int n)
{
	return eye(n, n);
}

template<class DataType>
Matrix<double> eye(const Matrix<DataType>& A)
{
	return eye(A.n_rows, A.n_cols);
}

Matrix<double> rand(int rows, int cols)
{
	Matrix<double> A(rows, cols);
	srand((unsigned)time(NULL));
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			A[i][j] = rand() / double(RAND_MAX);
		}
	}

	return A;
}

Matrix<double> rand(int n)
{
	return rand(n, n);
}

template<class DataType>
Matrix<double> rand(const Matrix<DataType>& A)
{
	return rand(A.n_rows, A.n_cols);
}

// template<class DataType>
// Matrix<DataType> randn(int rows, int cols)
// {
// 	Matrix<DataType> A(rows, cols);

// 	random_device rd;
//     mt19937 gen(rd());
//     normal_distribution<double> normal(0, 1);
//     for(int i = 0; i < rows; i++)
//     {
//         for(int j = 0; j < cols; j++)
//         {
//             A[i][j] = normal(gen);
//         }   
//     }

//     return 0;
// }

// Matrix<DataType> randn(int n)
// {
// 	return randn(n, n);
// }

// Matrix<DataType> randn(const Matrix<DataType>& A)
// {
// 	return randn(A.n_rows, A.n_cols);
// }

template<class DataType>
Matrix<DataType> reshape(const Matrix<DataType>& A, int m, int n)
{
	if(m * n != A.n_rows * A.n_cols)
	{
		cout << "Error using \'Matrix<DataType> reshape(const Matrix<DataType>& A, int m, int n)\'" << endl
			 << "m * n != A.n_rows * A.n_cols" << endl;
		exit(-1);
	}

	Matrix<DataType> C(m, n);
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			int N = i * n + j;
			C[i][j] = A[N / A.n_cols][N % A.n_cols];
		}
	}

	return C;
}

template<class DataType>
Matrix<DataType> repmat(const Matrix<DataType>& A, int m, int n)
{
	Matrix<DataType> B(m * A.n_rows, n * A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = A[i % m][j % n];
		}
	}

	return B;
}

template<class DataType>
Matrix<DataType> repelem(const Matrix<DataType>& A, int m, int n)
{
	Matrix<DataType> B(m * A.n_rows, n * A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = A[i / m][j / n];
		}
	}

	return B;
}

template<class DataType>
bool same_size(const Matrix<DataType>& A, const Matrix<DataType>& B)
{
	return (A.n_rows == B.n_rows) && (A.n_cols == B.n_cols);
}

Matrix<double> sin(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = sin(A[i][j]);
		}
	}

	return B;
}

Matrix<double> cos(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = cos(A[i][j]);
		}
	}

	return B;
}

Matrix<double> tan(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = tan(A[i][j]);
		}
	}

	return B;
}

Matrix<double> asin(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = asin(A[i][j]);
		}
	}

	return B;
}

Matrix<double> acos(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = acos(A[i][j]);
		}
	}

	return B;
}

Matrix<double> atan(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = atan(A[i][j]);
		}
	}

	return B;
}

Matrix<double> atan2(const Matrix<double>& Y, const Matrix<double>& X)
{
	Matrix<double> Z(Y.n_rows, Y.n_cols);
	for(int i = 0; i < Z.n_rows; i++)
	{
		for(int j = 0; j < Z.n_cols; j++)
		{
			Z[i][j] = atan2(Y[i][j], X[i][j]);
		}
	}

	return Z;
}

Matrix<double> sinh(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = sinh(A[i][j]);
		}
	}

	return B;
}

Matrix<double> cosh(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = cosh(A[i][j]);
		}
	}

	return B;
}

Matrix<double> tanh(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = tanh(A[i][j]);
		}
	}

	return B;
}

Matrix<double> asinh(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = asinh(A[i][j]);
		}
	}

	return B;
}

Matrix<double> acosh(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = acosh(A[i][j]);
		}
	}

	return B;
}

Matrix<double> atanh(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = atanh(A[i][j]);
		}
	}

	return B;
}

Matrix<double> exp(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = exp(A[i][j]);
		}
	}

	return B;
}

Matrix<double> log(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = log(A[i][j]);
		}
	}

	return B;
}

Matrix<double> log2(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = log2(A[i][j]);
		}
	}

	return B;
}

Matrix<double> log10(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = log10(A[i][j]);
		}
	}

	return B;
}

Matrix<double> abs(const Matrix<double>& A)
{
	Matrix<double> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = abs(A[i][j]);
		}
	}

	return B;
}

Matrix<int> floor(const Matrix<double>& A)
{
	Matrix<int> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = floor(A[i][j]);
		}
	}

	return B;
}

Matrix<int> ceil(const Matrix<double>& A)
{
	Matrix<int> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = ceil(A[i][j]);
		}
	}

	return B;
}

Matrix<int> round(const Matrix<double>& A)
{
	Matrix<int> B(A.n_rows, A.n_cols);
	for(int i = 0; i < B.n_rows; i++)
	{
		for(int j = 0; j < B.n_cols; j++)
		{
			B[i][j] = round(A[i][j]);
		}
	}

	return B;
}

//
// Matrix<DataType> fix(const Matrix<DataType>& A)
// {
// 	Matrix<DataType> B(A.n_rows, A.n_cols);
// 	for(int i = 0; i < B.n_rows; i++)
// 	{
// 		for(int j = 0; j < B.n_cols; j++)
// 		{
// 			B[i][j] = fix(A[i][j]);
// 		}
// 	}

// 	return B;
// }

Matrix<double> linspace(double start, double end, int n)
{
	Matrix<double> x(1, n);
	x[0][0] = start;
	x[0][n-1] = end;

	double delta = (end-start)/(n-1);
	for(int i = 1; i < n-1; i++)
	{
		x[0][i] = x[0][i-1] + delta;
	}

	return x;
}

template<class DataType>
vector< Matrix<DataType> > meshgrid(Matrix<DataType> x, Matrix<DataType> y)
{
	x = reshape(x, 1, x.n_rows*x.n_cols);
	y = reshape(y, 1, y.n_rows*y.n_cols);
	Matrix<DataType> X = ones(y.t()) * x;
	Matrix<DataType> Y = y.t() * ones(x);
	vector< Matrix<DataType> > XY;
	XY.push_back(X);
	XY.push_back(Y);

	return XY;
}

string multi_space(const int& n)
{
	string space;
	for(int i = 0; i < n; i++)
	{
		space += " ";
	}

	return space;
}

template<class DataType>
ostream & operator <<(ostream& o, Matrix<DataType> A)
{
	o << endl;
	int *longest_size = new int[A.n_cols];
	for(int j = 0; j < A.n_cols; j++)
	{
		longest_size[j] = Matrix<DataType>::cout2string(A[0][j]).size();
		for(int i = 1; i < A.n_rows; i++)
		{
			int current_size = Matrix<DataType>::cout2string(A[i][j]).size();
			if(current_size > longest_size[j])
			{
				longest_size[j] = current_size;
			}
		}
	}
	
	for(int i = 0; i < A.n_rows; i++)
	{
		for(int j = 0; j < A.n_cols; j++)
		{
			int space_length = longest_size[j] - Matrix<DataType>::cout2string(A[i][j]).size() + 2;
			if(A[i][j] >= 0)
			{
				o << " " << A[i][j] << multi_space(space_length);
			}
			else
			{
				o << A[i][j] << multi_space(space_length+1);
			}
		}
		o << endl;
	}
	delete longest_size;

	return o;
}

#endif