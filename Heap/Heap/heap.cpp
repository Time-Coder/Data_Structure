#ifdef HEAP_H

template<class DataType>
int Heap<DataType>::lchild(int i)
{
	return 2 * i + 1;
}

template<class DataType>
int Heap<DataType>::rchild(int i)
{
	return 2 * i + 2;
}

template<class DataType>
int Heap<DataType>::parent(int i)
{
	return ceil(0.5 * i - 1);
}

template<class DataType>
int Heap<DataType>::depth(int i)
{
	return ceil(log2(i+2)) - 1;
}

template<class DataType>
void Heap<DataType>::up_percolate(Vector<DataType>& v, int lower, int upper)
{
	int n = upper - lower;
	int i = n - 1;
	while(parent(i) >= 0 && v[parent(i) + lower] < v[i + lower])
	{
		i = parent(i);
		(rchild(i) >= n || v[lchild(i) + lower] >= v[rchild(i) + lower]) ?
		swap(v[i + lower], v[lchild(i) + lower]) : swap(v[i + lower], v[rchild(i) + lower]);
	}
}

template<class DataType>
void Heap<DataType>::down_percolate(Vector<DataType>& v, int lower, int upper, int i)
{
	int n = upper - lower;
	i -= lower;
	while(true)
	{
		if(lchild(i) >= n)
		{
			return;
		}

		(rchild(i) >= n || v[lchild(i) + lower] >= v[rchild(i) + lower]) ?
		i = lchild(i) : i = rchild(i);

		if(v[i + lower] <= v[parent(i) + lower])
		{
			return;
		}

		swap(v[i + lower], v[parent(i) + lower]);
	}
}

template<class DataType>
void Heap<DataType>::up_percolate()
{
	int i = v.size()-1;
	while(parent(i) >= 0 && v[parent(i)] < v[i])
	{
		i = parent(i);
		(rchild(i) >= size() || v[lchild(i)] >= v[rchild(i)]) ?
		swap(v[i], v[lchild(i)]) : swap(v[i], v[rchild(i)]);
	}
}

template<class DataType>
void Heap<DataType>::down_percolate(int i)
{
	while(true)
	{
		if(lchild(i) >= size())
		{
			return;
		}

		(rchild(i) >= size() || v[lchild(i)] >= v[rchild(i)]) ?
		i = lchild(i) : i = rchild(i);

		if(v[i] <= v[parent(i)])
		{
			return;
		}

		swap(v[i], v[parent(i)]);
	}
}

template<class DataType>
DataType Heap<DataType>::top()
{
	return v[0];
}

template<class DataType>
DataType Heap<DataType>::pop()
{
	if(empty())
	{
		cout << "Error in 'DataType Heap<DataType>::pop()'" << endl
			 << "The heap is empty, nothing to pop!" << endl;
		exit(-1);
	}

	if(size() == 1)
	{
		return v.pop_back();
	}

	DataType x = v[0];
	DataType v0 = v.pop_back();
	v[0] = v0;
	down_percolate(0);

	return x;
}

template<class DataType>
void Heap<DataType>::insert(const DataType& x)
{
	v.push_back(x);
	up_percolate();
}

// 当把向量直接当堆用时，可以使用这些接口
template<class DataType>
bool Heap<DataType>::isheap(const Vector<DataType>& v, int lower, int upper)
{
	v.check_limit(lower, upper, "bool Heap<DataType>::isheap(const Vector<DataType>& v, int lower, int upper)");

	int n = upper - lower;
	for(int i = 0; i < n; i++)
	{
		if( (lchild(i)+lower < upper && v[lchild(i)+lower] > v[i+lower]) ||
			(rchild(i)+lower < upper && v[rchild(i)+lower] > v[i+lower])    )
		{
			return false;
		}
	}

	return true;
}

template<class DataType>
void Heap<DataType>::heapify(Vector<DataType>& v, int lower, int upper)
{
	v.check_limit(lower, upper, "void Heap<DataType>::heapify(Vector<DataType>& v, int lower, int upper)");

	for(int i = upper - 1; i >= lower; i--)
	{
		down_percolate(v, lower, upper, i);
	}
}

template<class DataType>
DataType Heap<DataType>::pop(Vector<DataType>& v, int lower, int& upper)
{
	v.check_limit(lower, upper, "DataType Heap<DataType>::pop(Vector<DataType>& v, int lower, int& upper)");

	if(upper - lower == 1)
	{
		upper--;
		return v[lower];
	}

	DataType x = v[lower];
	v[lower] = v[upper-1];
	upper--;
	down_percolate(v, lower, upper, lower);

	return x;
}

template<class DataType>
DataType Heap<DataType>::pop(Vector<DataType>& v)
{
	if(v.empty())
	{
		cout << "Error in 'DataType Heap<DataType>::pop()'" << endl
			 << "The heap is empty, nothing to pop!" << endl;
		exit(-1);
	}

	if(v.size() == 1)
	{
		return v.pop_back();
	}

	DataType x = v[0];
	DataType v0 = v.pop_back();
	v[0] = v0;
	down_percolate(v, 0, v.size(), 0);

	return x;
}

template<class DataType>
void Heap<DataType>::insert(Vector<DataType>& v, int lower, int& upper, const DataType& x)
{
	v.check_limit(lower, upper, "void Heap<DataType>::insert(Vector<DataType>& v, int lower, int& upper, const DataType& x)");

	v.insert(upper, x);
	upper++;
	up_percolate(v, lower, upper);
}

template<class DataType>
void Heap<DataType>::insert(Vector<DataType>& v, int lower, int& upper)
{
	v.check_limit(lower, upper, "void Heap<DataType>::insert(Vector<DataType>& v, int lower, int& upper)");

	upper++;
	up_percolate(v, lower, upper);
}

template<class DataType>
void Heap<DataType>::insert(Vector<DataType>& v, const DataType& x)
{
	v.push_back(x);
	up_percolate(v, 0, v.size());
}

#endif