#include <iostream>
#include <ctime>
using namespace std;

#define DEFAULT_CAPACITY 4
template<class DataType>
class Vector
{
public:
	int _capacity;
	int _size;
	DataType* _data;

private:
	DataType* new_DataType(int n);
	void copy_from(const DataType* array, int lower, int upper);
	void expand();
	void shrink();
	void check_limit(int lower, int upper, const char* function_name)const;
	void merge(int lower, int middle, int upper);

public:
	Vector<DataType>(); // tested
	Vector<DataType>(int size); // tested
	Vector<DataType>(int size, const DataType& value); // tested
	Vector<DataType>(const DataType* array, int size); // tested
	Vector<DataType>(const DataType* array, int lower, int upper); // tested
	Vector<DataType>(const Vector<DataType>& v); // tested
	Vector<DataType>(const Vector<DataType>& v, int lower, int upper); // tested
	Vector<DataType>(initializer_list<DataType> list); // tested
	~Vector<DataType>(); // tested

	void clear(); // tested
	int size()const; // tested
	int capacity()const; // tested
	bool empty()const; // tested

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

	bool sorted()const; // tested
	Vector<DataType>& sort(); // tested
	Vector<DataType>& sort(int lower, int upper); // tested
	Vector<DataType>& unsort(); // tested
	Vector<DataType>& unsort(int lower, int upper); // tested

	int uniquify();

	friend ostream& operator <<(ostream& out, const Vector<DataType>& v)
	{
		int i;
		for(i = 0; i < v.size()-1; i++)
		{
			out << v[i] << ", ";
		}
		if(i)
		{
			out << v[i];
		}

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
void Vector<DataType>::check_limit(int lower, int upper, const char* function_name)const
{
	if(lower < 0 || lower >= upper || upper > _size)
	{
		cout << "Error in '"<< function_name << "'" << endl
			 << "lower or upper limit exceeds vector dimension" << endl;
		exit(-1);
	}
}

template<class DataType>
Vector<DataType>::Vector()
{
	_capacity = DEFAULT_CAPACITY;
	_size = 0;
	_data = new_DataType(_capacity);
}

template<class DataType>
Vector<DataType>::Vector(int size)
{
	_size = size;
	_capacity = _size << 1;
	_data = new_DataType(_capacity);
}

template<class DataType>
Vector<DataType>::Vector(int size, const DataType& value)
{
	_size = size;
	_capacity = size << 1;
	_data = new_DataType(_capacity);

	DataType* ptr = _data;
	while(size--)
	{
		*ptr++ = value;
	}
}

template<class DataType>
void Vector<DataType>::copy_from(const DataType* array, int lower, int upper)
{
	if(lower >= upper)
	{
		cout << "Error in 'void Vector<DataType>::copy_from(const DataType* array, int lower, int upper)'" << endl
			 << "lower limit exceeds upper limit!" << endl;
		exit(-1);
	}

	_size = upper - lower;
	_capacity = _size << 1;
	_data = new_DataType(_capacity);

	DataType* ptr_dest = _data;
	const DataType* ptr_src = array + lower;

	while(lower++ != upper)
	{
		*ptr_dest++ = *ptr_src++;
	}
}

template<class DataType>
Vector<DataType>::Vector(const DataType* array, int size)
{
	copy_from(array, 0, size);
}

template<class DataType>
Vector<DataType>::Vector(const DataType* array, int lower, int upper)
{
	copy_from(array, lower, upper);
}

template<class DataType>
Vector<DataType>::Vector(const Vector<DataType>& v)
{
	copy_from(v._data, 0, v._size);
}

template<class DataType>
Vector<DataType>::Vector(const Vector<DataType>& v, int lower, int upper)
{
	v.check_limit(lower, upper, "Vector<DataType>::Vector(const Vector<DataType>& v, int lower, int upper)");
	copy_from(v._data, lower, upper);
}

template<class DataType>
Vector<DataType>::Vector(initializer_list<DataType> list)
{
	_size = list.size();
	_capacity = _size << 1;
	_data = new_DataType(_capacity);

	DataType* ptr_dest = _data;
	for(typename initializer_list<DataType>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		*ptr_dest++ = *it;
	}
}

template<class DataType>
Vector<DataType>::~Vector()
{
	delete [] _data;
}

template<class DataType>
void Vector<DataType>::clear()
{
	_size = 0;
	_capacity = DEFAULT_CAPACITY;
	delete [] _data;
	_data = new_DataType(DEFAULT_CAPACITY);
}

template<class DataType>
int Vector<DataType>::size()const
{
	return _size;
}

template<class DataType>
int Vector<DataType>::capacity()const
{
	return _capacity;
}

template<class DataType>
bool Vector<DataType>::empty()const
{
	return (_size == 0);
}

template<class DataType>
void Vector<DataType>::expand()
{
	if(_size < _capacity)
	{
		return;
	}

	_capacity <<= 1;
	DataType* old_data = _data;
	_data = new_DataType(_capacity);
	
	DataType* ptr_src = old_data;
	DataType* ptr_dest = _data;
	for(int i = 0; i < _size; i++)
	{
		*ptr_dest++ = *ptr_src++;
	}

	delete [] old_data;
}

template<class DataType>
void Vector<DataType>::shrink()
{
	if(_capacity < _size << 2 || _capacity < DEFAULT_CAPACITY << 1)
	{
		return;
	}
	
	_capacity >> 1;
	DataType *old_data = _data;
	_data = new_DataType(_capacity);

	DataType *ptr_dest = _data;
	DataType *ptr_src = old_data;

	for(int i = 0; i < _size; i++)
	{
		*ptr_dest++ = *ptr_src++;
	}
}

template<class DataType>
Vector<DataType>& Vector<DataType>::operator =(const Vector<DataType>& v)
{
	delete [] _data;

	_capacity = v._capacity;
	_size = v._size;
	_data = new_DataType(_capacity);

	DataType *ptr_dest = _data;
	DataType *ptr_src = v._data;

	for(int i = 0; i < _size; i++)
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
	if(i >= _size)
	{
		cout << "Error in 'DataType& operator [](int i)const'" << endl
			 << "Index exceeds vector size!" << endl;
		exit(-1);
	}

	return _data[i];
}

template<class DataType>
void Vector<DataType>::push_back(const DataType& x)
{
	expand();
	_data[_size++] = x;
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
	DataType *ptr_i = _data + i;
	DataType *ptr_dest = _data + _size;
	DataType *ptr_src = _data + _size - 1;
	while(ptr_dest != ptr_i)
	{
		*ptr_dest-- = *ptr_src--;
	}
	*ptr_dest = x;
	_size++;
}

template<class DataType>
DataType Vector<DataType>::erase(int i)
{
	DataType x = _data[i];
	erase(i, i+1);
	return x;
}

template<class DataType>
void Vector<DataType>::erase(int lower, int upper)
{
	check_limit(lower, upper, "void Vector<DataType>::erase(int lower, int upper)");

	DataType *ptr_dest = _data + lower;
	DataType *ptr_src = _data + upper;

	int n = _size - upper;
	for(int i = 0; i < n; i++)
	{
		*ptr_dest++ = *ptr_src++;
	}

	_size -= upper - lower;
	shrink();
}

template<class DataType>
DataType Vector<DataType>::pop_back()
{
	return erase(_size - 1);
}

template<class DataType>
DataType Vector<DataType>::pop_front()
{
	return erase(0);
}

template<class DataType>
int Vector<DataType>::find(const DataType& x)
{
	return find(x, 0, _size);
}

template<class DataType>
int Vector<DataType>::find(const DataType& x, int lower, int upper)
{
	check_limit(lower, upper, "int Vector<DataType>::find(const DataType& x, int lower, int upper)");

	if(sorted())
	{
		if(x < _data[lower] || x > _data[upper-1])
		{
			return -1;
		}
		int middle = (lower + upper) >> 1;
		while(_data[middle] != x)
		{
			x > _data[middle] ? lower = middle : upper = middle;
			middle = (lower + upper) >> 1;
		}
		return middle;
	}
	else
	{
		while(lower != upper)
		{
			if(_data[lower] == x)
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
	for(int i = 0; i < _size - 1; i++)
	{
		if(_data[i] > _data[i + 1])
		{
			return false;
		}
	}
	return true;
}

template<class DataType>
void Vector<DataType>::merge(int lower, int middle, int upper)
{
	int n_pre = middle - lower;

	DataType* ptr_src = _data + lower;
	DataType* ptr_pre = new_DataType(n_pre);
	DataType* ptr_post = _data + middle;

	for(int i = 0; i < n_pre; i++)
	{
		*ptr_pre++ = *ptr_src++;
	}
	DataType* end_pre = ptr_pre;
	ptr_pre -= n_pre;

	DataType* ptr_dest = _data + lower;
	DataType* end = _data + upper;

	while(ptr_dest != end)
	{
		if(ptr_post == end || (ptr_pre != end_pre && *ptr_pre < *ptr_post) )
		{
			*ptr_dest++ = *ptr_pre++;
		}
		else if(ptr_pre == end_pre || (ptr_post != end && *ptr_pre >= *ptr_post) )
		{
			*ptr_dest++ = *ptr_post++;
		}
	}
	delete [] ptr_pre;
}

template<class DataType>
Vector<DataType>& Vector<DataType>::sort(int lower, int upper)
{
	if(upper - lower == 1)
	{
		return *this;
	}
	int middle = (lower + upper) >> 1;
	sort(lower, middle);
	sort(middle, upper);
	merge(lower, middle, upper);

	return *this;
}

template<class DataType>
Vector<DataType>& Vector<DataType>::sort()
{
	return sort(0, _size);
}

template<class DataType>
Vector<DataType>& Vector<DataType>::unsort()
{
	return unsort(0, _size);
}

template<class DataType>
Vector<DataType>& Vector<DataType>::unsort(int lower, int upper)
{
	check_limit(lower, upper, "Vector<DataType>& Vector<DataType>::unsort(int lower, int upper)");
	srand((unsigned)time(NULL));
	for(int i = upper-1; i >= lower+1; i--)
	{
		swap(_data[i], _data[rand() % i]);
	}

	return *this;
}

template<class DataType>
int Vector<DataType>::uniquify()
{
	if(sorted())
	{
		DataType *ptr_dest = _data;
		DataType *ptr_src = _data;
		for(int i = 0; i < _size; i++, ptr_src++)
		{
			if(*ptr_src != *ptr_dest)
			{
				*(++ptr_dest) = *ptr_src;
			}
		}
		_size = ptr_dest - _data + 1;
		shrink();
		return ptr_dest - ptr_src;
	}
	else
	{
		int i = 1;
		int old_size = _size;
		while(i < _size)
		{
			find(_data[i], 0, i) < 0 ? i++ : erase(i);
		}

		return old_size - _size;
	}
}