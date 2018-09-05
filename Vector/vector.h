#include <iostream>

using namespace std;

template<class DataType>
class Vector
{
public:
	int capacity = 0;
	int length = 0;
	DataType* data = NULL;

public:
	Vector<DataType>();
	Vector<DataType>(int length);
	Vector<DataType>(int length, DataType value);
	Vector<DataType>(const DataType* array, int length);
	Vector<DataType>(const DataType* array, int lower, int upper);
	Vector<DataType>(const Vector<DataType>& v);
	Vector<DataType>(const Vector<DataType>& v, int lower, int upper);
	Vector<DataType>(initializer_list<DataType> list);
	~Vector<DataType>();

	int size();
	int capacity();
	bool empty();

	void expand();
	void shrink();

	void push_back(DataType x);
	void push_front(DataType x);
	void insert(int r, DataType x);

	DataType erase(int r);
	DataType erase(int lower, int upper);
	DataType pop_back();
	DataType pop_front();

	void replace(int r, DataType x);

	int find(DataType x);
	int find(DataType x, int lower, int upper);

	void sort();
	void sort(int lower, int upper);
	void unsort();
	void unsort(int lower, int upper);
};