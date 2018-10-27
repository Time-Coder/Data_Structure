#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <ctime>

using namespace std;

#define DEFAULT_CAPACITY 4

template<class DataType>
class Vector
{
public:
	DataType* _data;
	int _capacity;
	int _size;

private:
	DataType* new_DataType(int n);
	void copy_from(const DataType* array, int lower, int upper);
	void expand();
	void shrink();
	void merge(int lower, int middle, int upper);

public:
	Vector();
	Vector(int size);
	Vector(int size, const DataType& value);
	Vector(const DataType* array, int size);
	Vector(const DataType* array, int lower, int upper);
	Vector(const Vector<DataType>& v);
	Vector(const Vector<DataType>& v, int lower, int upper);
	Vector(initializer_list<DataType> list);
	~Vector();

	void check_limit(int lower, int upper, const char* function_name)const;
	void clear();
	int size()const;
	int capacity()const;
	bool empty()const;

	Vector<DataType>& operator =(const Vector<DataType>& v);
	DataType& operator [](int i)const;

	void push_back(const DataType& x);
	void push_front(const DataType& x);
	void insert(int r, const DataType& x);

	DataType erase(int r);
	void erase(int lower, int upper);
	DataType pop_back();
	DataType pop_front();

	int find(const DataType& x);
	int find(const DataType& x, int lower, int upper);

	bool sorted()const;
	Vector<DataType>& sort();
	Vector<DataType>& sort(int lower, int upper);
	Vector<DataType>& unsort();
	Vector<DataType>& unsort(int lower, int upper);

	int uniquify();

	template<class ElemType>
	friend ostream& operator <<(ostream& out, const Vector<ElemType>& v);
};

Vector<int> int_rand(int lower, int upper, int n);
Vector<double> rand(double lower, double upper, int n);

#include <vector.cpp>
#endif