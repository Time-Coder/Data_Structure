#ifdef SORT_H

template<class DataType>
void insert_sort(Vector<DataType>& v, int lower, int upper)
{
	for(int i = lower + 1; i < upper; i++)
	{
		if(v[i] < v[i-1])
		{
			int j;
			for(j = i - 1; v[j] > v[i]; j--)
			{
				v[j + 1] = v[j];
			}
			v[j + 1] = v[i];
		}
	}
}

template<class DataType>
void half_insert_sort(Vector<DataType>& v, int lower, int upper)
{
	for(int i = lower + 1; i < upper; i++)
	{
		if(v[i] < v[i-1])
		{
			int lo = lower, hi = i;
			DataType x = v[i];
			while(lo < hi)
			{
				int mi = (lo + hi) >> 1;
				x < v[mi] ? hi = mi : lo = mi + 1;
			}

			for(int j = i - 1; j >= lo; j--)
			{
				v[j+1] = v[j];
			}
			v[lo] = x;
		}
	}
}

template<class DataType>
void sort_column(Vector<DataType>& v, int lower, int upper, int w, int j)
{
	int n = (upper - lower) / w;
	int rear = (upper - lower) % w;
	if(rear != 0 && j < rear)
	{
		n++;
	}

	for(int i = 1; i < n; i++)
	{
		if(v[i*w+j + lower] < v[(i-1)*w+j + lower])
		{
			DataType x = v[i*w+j + lower];
			int lo = 0, hi = i;
			while(lo < hi)
			{
				int mi = (lo + hi) >> 1;
				x < v[mi*w+j + lower] ? hi = mi : lo = mi + 1;
			}
			
			for(int sub_i = i - 1; sub_i >= lo; sub_i--)
			{
				v[(sub_i+1)*w+j + lower] = v[sub_i*w+j + lower];
			}
			v[lo*w+j + lower] = x;
		}
	}
}

template<class DataType>
void shell_sort(Vector<DataType>& v, int lower, int upper, const Vector<int>& steps)
{
	for(int i = steps.size()-1; i >= 0; i--)
	{
		int w = steps[i];
		for(int j = 0; j < w; j++)
		{
			sort_column(v, lower, upper, w, j);
		}
	}
}

Vector<int> shell(int n)
{
	Vector<int> steps;
	int value = 1;
	while(value < n)
	{
		steps.push_back(value);
		value *= 2;
	}

	return steps;
}

Vector<int> papernov(int n)
{
	Vector<int> steps;
	int value = 1;
	while(value < n)
	{
		steps.push_back(value);
		value = 2 * value + 1;
	}

	return steps;
}

Vector<int> pratt(int n)
{
	Vector<int> steps;

	int i2 = 0, i3 = 0, value = 1;
	while(value < n)
	{
		steps.push_back(value);
		int n2 = 2 * steps[i2];
		int n3 = 3 * steps[i3];
		value = min(n2, n3);
		if(n2 <= n3) i2++;
		if(n2 >= n3) i3++;
	}

	return steps;
}

Vector<int> sedgewick(int n)
{
	Vector<int> steps;

	int e1 = 4, e2 = 4, value = 1;
	while(value < n)
	{
		steps.push_back(value);
		int n1 = 9*e1*(e1 - 1) + 1;
		int n2 = e2*(e2 - 3) + 1;
		value = min(n1, n2);
		if(n1 <= n2) e1 <<= 1;
		if(n1 >= n2) e2 <<= 1;
	}

	return steps;
}

template<class DataType>
int partition(Vector<DataType>& v, int lower, int upper)
{
	static bool first = true;
	if(first)
	{
		srand((unsigned)time(NULL));
	}

	swap(v[lower], v[lower + rand() % (upper - lower)]);

	int mi = lower;
	for(int k = lower + 1; k < upper; k++)
	{
		if(v[k] < v[lower])
		{
			swap(v[++mi], v[k]);
		}
	}
	swap(v[lower], v[mi]);
	first = false;
	return mi;
}

template<class DataType>
void quick_sort(Vector<DataType>& v, int lower, int upper)
{
	if(upper - lower <= 1)
	{
		return;
	}
	
	int i = partition(v, lower, upper);
	quick_sort(v, lower, i);
	quick_sort(v, i+1, upper);
}

template<class DataType>
void merge(Vector<DataType>& v, int lower, int upper, int middle)
{
	int n1 = middle - lower, n2 = upper - middle;
	DataType* A = new DataType[n1];
	DataType* B = v._data + middle;
	DataType* C = v._data + lower;
	for(int i = 0; i < n1; A[i] = C[i++]);

	for(int i = 0, j = 0, k = 0; (i < n1 || j < n2);)
	{
		if(i < n1 && ( j >= n2 || A[i] <= B[j] )) C[k++] = A[i++];
		if(j < n2 && ( i >= n1 || B[j] <  A[i] )) C[k++] = B[j++];
	}
}

template<class DataType>
void merge_sort(Vector<DataType>& v, int lower, int upper)
{
	if(upper - lower <= 1)
	{
		return;
	}

	int middle = (lower + upper) >> 1;
	merge_sort(v, lower, middle);
	merge_sort(v, middle, upper);
	merge(v, lower, upper, middle);
}

template<class DataType>
void select_sort(Vector<DataType>& v, int lower, int upper)
{
	for(int j = upper - 1; j > lower; j--)
	{
		int it_max = 0;
		for(int i = 1; i <= j; i++)
		{
			if(v[i] > v[it_max])
			{
				it_max = i;
			}
		}
		swap(v[it_max], v[j]);
	}
}

template<class DataType>
void heap_sort(Vector<DataType>& v, int lower, int upper)
{
	Heap<DataType>::heapify(v);
	while(upper - lower >= 2)
	{
		DataType max = Heap<DataType>::pop(v, lower, upper);
		v[upper] = max;
	}
}

void count_sort(Vector<int>& v, int lower, int upper)
{
	int min = v[lower];
	int max = min;
	for(int i = lower+1; i < upper; i++)
	{
		if(v[i] > max)
		{
			max = v[i];
		}
		else if(v[i] < min)
		{
			min = v[i];
		}
	}

	int n = max - min + 1;
	int* a = new int[n];
	for(int i = 0; i < n; i++)
	{
		a[i] = 0;
	}

	for(int i = lower; i < upper; i++)
	{
		a[v[i]-min]++;
	}

	int j = 0;
	for(int i = 0; i < n; i++)
	{
		while(a[i] > 0)
		{
			v[j++] = i + min;
			a[i]--;
		}
	}
}

#endif