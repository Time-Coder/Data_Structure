#ifndef HEAP_H
#define HEAP_H

#include <vector.h>
#include <cmath>

template<class DataType>
class Heap
{
public:
	Vector<DataType> v;

private:
	static int lchild(int i);
	static int rchild(int i);
	static int parent(int i);
	static int depth(int i);

	void up_percolate();
	void down_percolate(int i);

	static void up_percolate(Vector<DataType>& v, int lower, int upper);
	static void down_percolate(Vector<DataType>& v, int lower, int upper, int i);

public:
	Heap(){};
	Heap(const Vector<DataType>& vec){v = vec; heapify(v, 0, v.size());};

	void clear(){v.clear();}
	int size()const{return v.size();}
	bool empty()const{return v.empty();}

	DataType top();
	DataType pop();
	void insert(const DataType& x);

	// 当把向量直接当堆用时，可以使用这些接口
	static bool isheap(const Vector<DataType>& v, int lower, int upper);
	static bool isheap(const Vector<DataType>& v){return isheap(v, 0, v.size());}

	static void heapify(Vector<DataType>& v, int lower, int upper);
	static void heapify(Vector<DataType>& v){heapify(v, 0, v.size());}

	static DataType top(Vector<DataType>& v, int lower, int upper){return v[lower];}
	static DataType top(Vector<DataType>& v){return v[0];}

	static DataType pop(Vector<DataType>& v, int lower, int& upper);
	static DataType pop(Vector<DataType>& v);

	static void insert(Vector<DataType>& v, int lower, int& upper, const DataType& x);
	static void insert(Vector<DataType>& v, const DataType& x);
	static void insert(Vector<DataType>& v, int lower, int& upper);
};

#include <heap.cpp>
#endif