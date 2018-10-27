#ifndef SORT_H
#define SORT_H

#include <vector.h>
#include <list.h>
#include <heap.h>

// 1. 插入排序类
// 1.1 直接插入排序
template<class DataType>
void insert_sort(Vector<DataType>& v, int lower, int upper);

template<class DataType>
void insert_sort(Vector<DataType>& v)
{
	insert_sort(v, 0, v.size());
}

// 1.2 折半插入排序
template<class DataType>
void half_insert_sort(Vector<DataType>& v, int lower, int upper);

template<class DataType>
void half_insert_sort(Vector<DataType>& v)
{
	half_insert_sort(v, 0, v.size());
}

// 1.3 希尔排序
template<class DataType>
void shell_sort(Vector<DataType>& v, int lower, int upper, const Vector<int>& steps);

template<class DataType>
void shell_sort(Vector<DataType>& v, const Vector<int>& steps)
{
	shell_sort(v, 0, v.size(), steps);
}

Vector<int> shell(int n);
Vector<int> papernov(int n);
Vector<int> pratt(int n);
Vector<int> sedgewick(int n);


// 2. 快速排序
template<class DataType>
void quick_sort(Vector<DataType>& v, int lower, int upper);

template<class DataType>
void quick_sort(Vector<DataType>& v)
{
	quick_sort(v, 0, v.size());
}

// 3. 归并排序
template<class DataType>
void merge_sort(Vector<DataType>& v, int lower, int upper);

template<class DataType>
void merge_sort(Vector<DataType>& v)
{
	merge_sort(v, 0, v.size());
}

// 4. 选择排序类
// 4.1 直接选择排序
template<class DataType>
void select_sort(Vector<DataType>& v, int lower, int upper);

template<class DataType>
void select_sort(Vector<DataType>& v)
{
	select_sort(v, 0, v.size());
}

// 4.2 堆排序
template<class DataType>
void heap_sort(Vector<DataType>& v, int lower, int upper);

template<class DataType>
void heap_sort(Vector<DataType>& v)
{
	heap_sort(v, 0, v.size());
}

// 5. 非比较排序
// 5.1 计数排序
void count_sort(Vector<int>& v, int lower, int upper);
void count_sort(Vector<int>& v)
{
	count_sort(v, 0, v.size());
}

// 5.2 桶排序

#include <sort.cpp>
#endif