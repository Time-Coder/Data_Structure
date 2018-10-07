#include <stack.h>

int main()
{
	Stack<double> S1;

	S1.push(0.75);
	S1.push(8.64);
	S1.push(9.67);
	S1.push(4.51);
	S1.push(4.63);
	S1.push(8.53);
	S1.push(4.90);

	cout << "S1 = " << S1 << endl;

	Stack<double> S2 = S1;

	cout << "S2 = " << S2 << endl;

	Stack<double> S3;

	if(S3.empty())
	{
		cout << "Before assignment, S3 is an empty stack." << endl;
	}

	S3 = S2;

	if(!S3.empty())
	{
		cout << "After assignment, S3 = " << S3 << endl;
	}

	cout << "The top element of S3 is: " << S3.top() << endl;

	double x = S3.pop();
	cout << "After pop out the top element " << x << " of S3, S3 = " << S3 << endl;

	cout << "The length of S3 is: " << S3.size() << endl;

	S3.inverse();

	cout << "After inverse of S3, S3 = " << S3 << endl;

	S3.clear();
	cout << "After clear, S3 = " << S3 << endl;

	return 0;
}