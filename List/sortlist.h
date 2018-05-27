// Copyright(c): 2017 Bing-Hui WANG
//
// Author: Bing-Hui WANG
//
// Date: 2017-10-3
//
// Description: This code has build a sorted link list class named "SortList"
//
// See usage in "./README.md"
// See examples in "./example/"

#ifndef SORTLIST_H
#define SORTLIST_H

#include <iostream>
#include <stdlib.h>
#include <iterator>
#include <stdio.h>

using namespace std;

// Define SortList's node "ListNode".
template<typename DataType>
class ListNode
{
public:
	DataType  data;
	ListNode<DataType>* link = NULL;

public:
	ListNode<DataType>(){};
};

// Define SortList's iterator(read only).
template<typename DataType>
class SortListIterator : public iterator< input_iterator_tag, ListNode<DataType> >
{
public:
    ListNode<DataType>* _ptr = NULL;

public:
	SortListIterator();
    SortListIterator(ListNode<DataType>* p);
    SortListIterator& operator =(const SortListIterator& iter);
    bool operator !=(const SortListIterator& iter)const;
    bool operator ==(const SortListIterator& iter)const;
    SortListIterator& operator ++();
    SortListIterator operator ++(int);
    DataType operator *()const;
    bool empty()const;
};

// Define Sorted Link List class "SortList"
template<typename DataType>
class SortList
{
	friend ostream & operator <<(ostream &o, const SortList<DataType>& X)
	{
		o << endl << endl;

		for(const_iterator it = X.begin(); it != X.end(); it++)
		{
			o << *it << endl;
		}

		return o;
	}

private:
	ListNode<DataType>* head;
	
public:
	// Define it's read only iterator.
	typedef SortListIterator<DataType> const_iterator;

	// SortList's constructor without initial value.
	SortList<DataType>();

	// SortList's copy constructor
	SortList<DataType>(const SortList<DataType>& X);

	// SortList's destructor
	~SortList<DataType>();

	// Reload SortLiks's operator "=".
	// Make it possible to clone a SortList to anther by just use "=".
	SortList<DataType>& operator =(const SortList<DataType>& X);

	// To judge if 2 SortList is equal or not.
	bool operator ==(const SortList<DataType>& X)const;
	bool operator !=(const SortList<DataType>& X)const;

	// Clear the memory of SortList
	void clear();

	// Return the const_iterator that points to SortLiks begin element.
	const_iterator begin()const;

	// Return the const_iterator that points to SortLists end element's next position(NULL).
	// Be aware the difference between the begin() and end().
	const_iterator end()const;

	// Insert an element to correct position of SortList
	// This movement didn't destroy the order structrue of SortList.
	void insert(const DataType& x);

	// Erase the element in SortList at position that const_iterator point to.
	void erase(const const_iterator& it);

	// Erase the i-position(count from 0) element in SortList.
	void erase(const int& i);

	// Return the number of elements in current SortList.
	int  length()const;

	// To judge if current SortList is empty or not.
	bool empty()const;

	// To find out if the passed in element is in the SortList.
	// If yes, return it's location in type "const_iterator".
	const_iterator find(const DataType& x)const;

	// Return position i's iterator.
	const_iterator locate(const int& i)const;

	// Return iterator's position index in type "int".
	int locate(const const_iterator& it)const;

	// Merge 2 SortList into one.
	SortList<DataType> merge(const SortList<DataType>& X);
};

//--------------------------------- Implementation ------------------------------------------

template<typename DataType>
ListNode<DataType>::ListNode()
{
	link = NULL;
}

template<typename DataType>
SortList<DataType>::SortList()
{
	head = new ListNode<DataType>;
}

template<typename DataType>
SortList<DataType>::SortList(const SortList<DataType>& X)
{
	head = new ListNode<DataType>;
	
	ListNode<DataType>* p = X.head;
	while(p->link != NULL)
	{
		DataType value = (p->link)->data;
		insert(value);
		p = p->link;
	}
}

template<typename DataType>
SortList<DataType>::~SortList<DataType>()
{
	ListNode<DataType>* p;
	while( head->link != NULL )
	{
		p = head->link;
		head->link = p->link;
		delete p;
	}
}

template<typename DataType>
SortList<DataType>& SortList<DataType>::operator =(const SortList<DataType>& X)
{
	clear();
	ListNode<DataType>* p = X.head;
	while(p->link != NULL)
	{
		DataType value = (p->link)->data;
		insert(value);
		p = p->link;
	}
	return (*this);
}

template<typename DataType>
bool SortList<DataType>::operator ==(const SortList<DataType>& X)const
{
	if(length() != X.length())
	{
		return false;
	}

	const_iterator it2 = X.begin();
	for(const_iterator it1 = begin(); it1 != end(); it1++)
	{
		if(*it1 != *it2)
		{
			return false;
		}
		it2++;
	}

	return true;
}

template<typename DataType>
bool SortList<DataType>::operator !=(const SortList<DataType>& X)const
{
	return !(*this == X);
}

template<typename DataType>
void SortList<DataType>::clear()
{
	ListNode<DataType>* p;
	while( head->link != NULL )
	{
		p = head->link;
		head->link = p->link;
		delete p;
	}
}

template<typename DataType>
typename SortList<DataType>::const_iterator SortList<DataType>::begin()const
{
	return const_iterator(head->link);
}

template<typename DataType>
typename SortList<DataType>::const_iterator SortList<DataType>::end()const
{
	return const_iterator();
}

template<typename DataType>
void SortList<DataType>::insert(const DataType& x)
{
	ListNode<DataType>* newNode = new ListNode<DataType>;
	newNode->data = x;
	ListNode<DataType>* p;
	p = head;
	while( p->link != NULL && (p->link)->data > x )
	{
		p = p->link;
	}
	newNode->link = p->link;
	p->link = newNode;
}

template<typename DataType>
void SortList<DataType>::erase(const int& i)
{
	int n = length();
	if( i < 0 || i >= n )
	{
		return;
	}
	ListNode<DataType>* p = head;
	for(int index = 0; index < i; index++)
	{
		p = p->link;
	}
	ListNode<DataType>* q = p->link;
	p->link = (p->link)->link;
	delete q;
}

template<typename DataType>
void SortList<DataType>::erase(const const_iterator& it)
{
	ListNode<DataType>* p = head;
	ListNode<DataType>* q = it._ptr;

	while( p->link != NULL && p->link != q )
	{
		p = p->link;
	}

	if(p->link == q)
	{
		p->link = q->link;
		delete q;
	}
}

template<typename DataType>
int SortList<DataType>::length()const
{
	int n = 0;
	ListNode<DataType>* p = head;
	while(p->link != NULL)
	{
		p = p->link;
		n++;
	}
	return n;
}

template<typename DataType>
bool SortList<DataType>::empty()const
{
	return ( head->link == NULL );
}

template<typename DataType>
typename SortList<DataType>::const_iterator SortList<DataType>::find(const DataType& x)const
{
	ListNode<DataType>* index = NULL;
	const_iterator it = begin();
	ListNode<DataType>* p = it._ptr;
	
	while(p != NULL)
	{
		if(p->data == x)
		{
			index = p;
			break;
		}
		p = p->link;
	}
	return const_iterator(index);
}

template<typename DataType>
typename SortList<DataType>::const_iterator SortList<DataType>::locate(const int& i)const
{
	int n = length();
	if( i < 0 || i > n )
	{
		return NULL;
	}
	ListNode<DataType>* p = head;
	for(int index = 1; index <= i; index++)
	{
		p = p->link;
	}
	return const_iterator(p);
}

template<typename DataType>
int SortList<DataType>::locate(const const_iterator& it)const
{
	int i = 0;
	ListNode<DataType>* p = head;
	ListNode<DataType>* q = it._ptr;
	while( p->link != NULL && p != q )
	{
		p = p->link;
		i++;
	}

	if(p != q)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

template<typename DataType>
SortList<DataType> SortList<DataType>::merge(const SortList<DataType>& X)
{
	for(const_iterator it = X.begin(); it != X.end(); it++)
	{
		insert(*it);
	}
	return (*this);
}

template<typename DataType>
SortListIterator<DataType>::SortListIterator()
{
	_ptr = NULL;
}

template<typename DataType>
SortListIterator<DataType>::SortListIterator(ListNode<DataType>* p)
{
    _ptr = p;
}

template<typename DataType>
SortListIterator<DataType>& SortListIterator<DataType>::operator =(const SortListIterator& iter)
{
    _ptr = iter._ptr;
}

template<typename DataType>
bool SortListIterator<DataType>::operator !=(const SortListIterator& iter)const
{
    return _ptr != iter._ptr;
}

template<typename DataType>
bool SortListIterator<DataType>::operator ==(const SortListIterator& iter)const
{
    return _ptr == iter._ptr;
}

template<typename DataType>
SortListIterator<DataType>& SortListIterator<DataType>::operator ++()
{
    if(_ptr)
    {
    	_ptr = _ptr->link;
    }
    return *this;
}

template<typename DataType>
SortListIterator<DataType> SortListIterator<DataType>::operator ++(int)
{
    SortListIterator<DataType> tmp = *this;
    if(_ptr)
    {
    	_ptr = _ptr->link;
    }

    return tmp;
}

template<typename DataType>
DataType SortListIterator<DataType>::operator *()const
{
	if(_ptr)
	{
    	return _ptr->data;
	}
	else
	{
		cout << "Error in *it!" << endl;
		exit(-1);
	}
}

template<typename DataType>
bool SortListIterator<DataType>::empty()const
{
	return !_ptr;
}

#endif