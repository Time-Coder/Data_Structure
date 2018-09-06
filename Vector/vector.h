#include <iostream>

using namespace std;

#define DEFAULT_CAPACITY 4
template<class DataType>
class Vector
{
public:
	int capacity;
	int length;
	DataType* data;

private:
	DataType* new_DataType(int n);
	void copy_from(const DataType* array, int lower, int upper);
	void expand();
	void shrink();

public:
	Vector<DataType>();
	Vector<DataType>(int length);
	Vector<DataType>(int length, const DataType& value);
	Vector<DataType>(const DataType* array, int length);
	Vector<DataType>(const DataType* array, int lower, int upper);
	Vector<DataType>(const Vector<DataType>& v);
	Vector<DataType>(const Vector<DataType>& v, int lower, int upper);
	Vector<DataType>(initializer_list<DataType> list);
	~Vector<DataType>();

	int size()const;
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
	void sort();
	void sort(int lower, int upper);
	void unsort();
	void unsort(int lower, int upper);

	int uniquify();

	friend ostream& operator <<(ostream& out, const Vector<DataType>& v)
	{
		int i;
		for(i = 0; i < v.size()-1; i++)
		{
			out << v[i] << ", ";
		}
		out << v[i] << endl;

		return out;
	}
};

template<class DataType>
DataType* Vector<DataType>::new_DataType(int n)
{
	DataType* p = new DataType[n];
	if(!p)
	{
		cerr << "Error to allocate memory!" << endl;
		exit(-1);
	}

	return p;
}

template<class DataType>
Vector<DataType>::Vector()
{
	capacity = DEFAULT_CAPACITY;
	length = 0;
	data = new_DataType(capacity);
}

template<class DataType>
Vector<DataType>::Vector(int length)
{
	capacity = length << 1;
	this->length = length;
	data = new_DataType(capacity);
}

template<class DataType>
Vector<DataType>::Vector(int length, const DataType& value)
{
	capacity = length << 1;
	this->length = length;
	data = new_DataType(capacity);

	DataType* ptr = data;
	while(length--)
	{
		*ptr++ = value;
	}
}

template<class DataType>
void Vector<DataType>::copy_from(const DataType* array, int lower, int upper)
{
	length = upper - lower;
	capacity = length << 1;
	data = new_DataType(capacity);

	DataType* ptr_dest = data;
	DataType* ptr_src = array + lower;

	while(lower++ != upper)
	{
		*ptr_dest++ = *ptr_src++;
	}
}

template<class DataType>
Vector<DataType>::Vector(const DataType* array, int length)
{
	copy_from(array, 0, length);
}

template<class DataType>
Vector<DataType>::Vector(const DataType* array, int lower, int upper)
{
	copy_from(array, lower, upper);
}

template<class DataType>
Vector<DataType>::Vector(const Vector<DataType>& v)
{
	copy_from(v.data, 0, v.length);
}

template<class DataType>
Vector<DataType>::Vector(const Vector<DataType>& v, int lower, int upper)
{
	copy_from(v.data, lower, upper);
}

template<class DataType>
Vector<DataType>::Vector(initializer_list<DataType> list)
{
	length = list.size();
	capacity = length << 1;
	data = new_DataType(capacity);

	DataType* ptr_dest = data;
	for(typename initializer_list<DataType>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		*ptr_dest++ = *it;
	}
}

template<class DataType>
Vector<DataType>::~Vector()
{
	delete [] data;
}

template<class DataType>
int Vector<DataType>::size()const
{
	return length;
}

template<class DataType>
bool Vector<DataType>::empty()const
{
	return (length == 0);
}

template<class DataType>
void Vector<DataType>::expand()
{
	if(length < capacity)
	{
		return;
	}

	capacity <<= 1;
	DataType* old_data = data;
	data = new_DataType(capacity);
	
	DataType* ptr_old = old_data;
	DataType* ptr = data;
	for(int i = 0; i < length; i++)
	{
		*ptr++ = *ptr_old++;
	}

	delete [] old_data;
}

template<class DataType>
void Vector<DataType>::shrink()
{
	if(capacity < length << 2 || capacity < DEFAULT_CAPACITY << 1)
	{
		return;
	}
	
	capacity >> 1;
	DataType *old_data = data;
	data = new_DataType(capacity);

	DataType *ptr = data;
	DataType *ptr_old = old_data;

	for(int i = 0; i < length; i++)
	{
		*ptr++ = *ptr_old++;
	}
}

template<class DataType>
Vector<DataType>& Vector<DataType>::operator =(const Vector<DataType>& v)
{
	if(data)
	{
		delete [] data;
	}

	capacity = v.capacity;
	length = v.length;
	data = new_DataType(capacity);

	DataType *ptr_dest = data;
	DataType *ptr_src = v.data;

	for(int i = 0; i < length; i++)
	{
		*ptr_dest++ = *ptr_src++;
	}

	return *this;
}

template<class DataType>
DataType& Vector<DataType>::operator [](int i)const
{
	if(i < 0)
	{
		cout << "Error in 'DataType& operator [](int i)const'" << endl
			 << "Index must be positive!" << endl;
		exit(-1);
	}
	if(i >= length)
	{
		cout << "Error in 'DataType& operator [](int i)const'" << endl
			 << "Index exceeds vector size!" << endl;
		exit(-1);
	}

	return data[i];
}

template<class DataType>
void Vector<DataType>::push_back(const DataType& x)
{
	expand();
	data[length++] = x;
}

template<class DataType>
void Vector<DataType>::push_front(const DataType& x)
{
	insert(0, x);
}

template<class DataType>
void Vector<DataType>::insert(int i, const DataType& x)
{
	expand();
	DataType *ptr_i = data + i;
	DataType *ptr_dest = data + length;
	DataType *ptr_src = data + length - 1;
	while(ptr_dest != ptr_i)
	{
		*ptr_dest-- = *ptr_src--;
	}
	*ptr_dest = x;
	length++;
}

template<class DataType>
DataType Vector<DataType>::erase(int i)
{
	DataType x = data[i];
	erase(i, i+1);
	return x;
}

template<class DataType>
void Vector<DataType>::erase(int lower, int upper)
{
	DataType *ptr_dest = data + lower;
	DataType *ptr_src = data + upper;

	int n = length - upper;
	for(int i = 0; i < n; i++)
	{
		*ptr_dest++ = *ptr_src++;
	}

	length -= upper - lower;
	shrink();
}

template<class DataType>
DataType Vector<DataType>::pop_back()
{
	return erase(length - 1);
}

template<class DataType>
DataType Vector<DataType>::pop_front()
{
	return erase(0);
}

template<class DataType>
int Vector<DataType>::find(const DataType& x)
{
	return find(x, 0, length);
}

template<class DataType>
int Vector<DataType>::find(const DataType& x, int lower, int upper)
{
	if(sorted())
	{
		if(x < data[lower] || x > data[upper-1])
		{
			return -1;
		}
		int middle = (lower + upper) >> 1;
		while(data[middle] != x)
		{
			x > data[middle] ? lower = middle : upper = middle;
			middle = (lower + upper) >> 1;
		}
		return middle;
	}
	else
	{
		while(lower != upper)
		{
			if(data[lower] == x)
			{
				return lower;
			}
			lower++;
		}
		return -1;
	}
}

template<class DataType>
bool Vector<DataType>::sorted()const
{
	for(int i = 0; i < length - 1; i++)
	{
		if(data[i] > data[i + 1])
		{
			return false;
		}
	}
	return true;
}

// void sort();
// void sort(int lower, int upper);
// void unsort();
// void unsort(int lower, int upper);

template<class DataType>
int Vector<DataType>::uniquify()
{
	if(sorted())
	{
		DataType *ptr_dest = data;
		DataType *ptr_src = data;
		for(int i = 0; i < length; i++, ptr_src++)
		{
			if(*ptr_src != *ptr_dest)
			{
				*(++ptr_dest) = *ptr_src;
			}
		}
		length = ptr_dest - data + 1;
		shrink();
		return ptr_dest - ptr_src;
	}
	else
	{
		int i = 1;
		int old_length = length;
		while(i < length)
		{
			find(data[i], 0, i) < 0 ? i++ : erase(i);
		}

		return old_length - length;
	}
}