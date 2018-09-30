#include "vector.h"

template<class DataType>
void print_vector_info(const Vector<DataType>& v, const char* name)
{
	cout << name << ".size() = " << v.size() << endl;
	cout << name << ".capacity() = " << v.capacity() << endl;
	cout << name << " = " << v << endl << endl;
}

int main()
{
	// 1. 
	// Vector<int> v1;
	// print_vector_info(v1, "v1");

	// Vector<int> v2(5);
	// print_vector_info(v2, "v2");

	// Vector<int> v3(5, 1);
	// print_vector_info(v3, "v3");

	// int a[5] = {1, 2, 3, 4, 5};
	// Vector<int> v4(a, 5);
	// print_vector_info(v4, "v4");

	// Vector<int> v5(a, 1, 4);
	// print_vector_info(v5, "v5");

	// Vector<int> v6 = v4;
	// print_vector_info(v6, "v6");

	// Vector<int> v7(v4, 0, 3);
	// print_vector_info(v7, "v7");

	// Vector<int> v8 = {0, 7, 2, 12, 83};
	// print_vector_info(v8, "v8");

	// v8.clear();
	// cout << "After clear," << endl;
	// print_vector_info(v8, "v8");

	// v8 = v6;
	// cout << "After assign value from v6 to v8," << endl;
	// print_vector_info(v8, "v8");

	Vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	cout << v << endl;
	v.unsort();
	cout << v << endl;
	return 0;
}
