#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iterator>

using namespace std;

template<typename DataType>
class ListNode
{
public:
	DataType data;
	ListNode<DataType> *link = NULL;

public:
	ListNode<DataType>()
	{
		link = NULL;
	}

	ListNode<DataType>(DataType element)
	{
		data = element;
		link = NULL;
	}
};

template<class Class, typename DataType>
class ListIterator : public iterator<input_iterator_tag, Class>
{
private:
	Class* _ptr = NULL;

public:
	ListIterator()
	{
		_ptr = NULL;
	}

	ListIterator(Class *p)
	{
		_ptr = p;
	}

	~ListIterator()
	{
		_ptr = NULL;
	}

    ListIterator& operator =(const ListIterator& it)
    {
        _ptr = it._ptr;
    }

    bool operator !=(const ListIterator& it)
    {
        return (_ptr != it._ptr);
    }

    bool operator ==(const ListIterator& it)
    {
        return (_ptr == it._ptr);
    }

    ListIterator& operator ++()
    {
        _ptr = _ptr->link;
        return *this;
    }

    ListIterator operator ++(int)
    {
        ListIterator temp = *this;
        _ptr = _ptr->link;
        return temp;
    }

    DataType& operator *()
    {
        return _ptr->data;
    }
};

template<typename DataType>
class List
{
	friend ostream & operator <<(ostream& out, const List<DataType>& list)
	{
		for(List<DataType>::iterator it = list.begin(); it != list.end(); it++)
		{
			out << (*it) << endl;
		}

		return out;
	}

public:
	ListNode<DataType> *head = new ListNode<DataType>();
	typedef ListIterator< ListNode<DataType>, DataType > iterator;

public:
	List<DataType>(){head->link = NULL;};
	List<DataType>(int n);
	List<DataType>(int n, DataType element);
	List<DataType>(const List<DataType>& list);
	~List<DataType>(){};
	List<DataType>& operator =(const List<DataType>& list);
	void clear();
	int length();
	bool empty();
	DataType& operator [](int i);
	// DataType operator [](int i);
	int locate(DataType element);
	bool insert(int i);
	bool erase(int i);
	iterator begin()const;
	iterator end()const;
};

template<typename DataType>
typename List<DataType>::iterator List<DataType>::begin()const
{
	return iterator(head->link);
}

template<typename DataType>
typename List<DataType>::iterator List<DataType>::end()const
{
	return iterator(NULL);
}

template<typename DataType>
List<DataType>::List(int n)
{
	ListNode<DataType>* p = head;
	for(int i = 0; i < n; i++,p = p->link)
	{
		p->link = new ListNode<DataType>;
	}
}

template<typename DataType>
List<DataType>::List(int n, DataType element)
{
	ListNode<DataType>* p = head;
 	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new ListNode<DataType>(element);
	}
}

#endif