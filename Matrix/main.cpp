#include <matrix.h>

int main()
{
	Matrix<double> A = 10.0 * rand(3);
	Matrix<double> B = 9.0 * rand(3);
	cout << (A + B) << endl;
	// cout << to(3, 6) << endl;


	// for(int i = 0; i < A.rows(); i++)
	// {
	// 	for(int j = 0; j < A.cols(); j++)
	// 	{
	// 		A[i][j] = 1;
	// 	}
	// }
	// cout << B << endl;

	return 0;
}