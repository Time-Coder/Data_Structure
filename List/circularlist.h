#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include <iostream>
#include <iterator>

using namespace std;

template<typename DataType>
class CircularListNode
{
public:
	DataType data;
	CircularListNode<DataType> *link = NULL;

public:
	CircularListNode<DataType>()
	{
		link = NULL;
	}

	CircularListNode<DataType>(DataType element)
	{
		data = element;
		link = NULL;
	}
};

template<class Class, typename DataType>
class CircularListIterator : public iterator<input_iterator_tag, Class>
{
private:
	Class* _ptr = NULL;

public:
	CircularListIterator()
	{
		_ptr = NULL;
	}

	CircularListIterator(Class *p)
	{
		_ptr = p;
	}

	~CircularListIterator()
	{
		_ptr = NULL;
	}

    CircularListIterator& operator =(const CircularListIterator& it)
    {
        _ptr = it._ptr;
    }

    bool operator !=(const CircularListIterator& it)
    {
        return (_ptr != it._ptr);
    }

    bool operator ==(const CircularListIterator& it)
    {
        return (_ptr == it._ptr);
    }

    CircularListIterator& operator ++()
    {
        _ptr = _ptr->link;
        return *this;
    }

    CircularListIterator operator ++(int)
    {
        CircularListIterator temp = *this;
        _ptr = _ptr->link;
        return temp;
    }

    DataType& operator *()
    {
        return _ptr->data;
    }
};

template<typename DataType>
class CircularList
{
	friend ostream & operator <<(ostream& out, const CircularList<DataType>& list)
	{
		CircularList<DataType>::iterator it = list.begin();
		for(int i = 0; i < list.size(); i++, it++)
		{
			out << (*it) << endl;
		}

		return out;
	}

private:
	CircularListNode<DataType> *head = new CircularListNode<DataType>();
	int length = 0;

public:
	typedef CircularListIterator< CircularListNode<DataType>, DataType > iterator;

public:
	CircularList<DataType>(){};
	CircularList<DataType>(int n);
	CircularList<DataType>(int n, DataType element);
	CircularList<DataType>(const CircularList<DataType>& list);
	~CircularList<DataType>();
	CircularList<DataType>& operator =(const CircularList<DataType>& list);
	void clear();
	int size()const;
	bool empty()const;
	DataType& operator [](int i);
	DataType operator [](int i)const;
	int locate(DataType element)const;
	bool insert(int i, DataType element);
	bool erase(int i);
	void push_back(DataType element);
	void push_front(DataType element);
	DataType pop_back();
	DataType pop_front();
	bool swap(int i, int j);
	iterator begin()const;
	iterator tail()const;
};

template<typename DataType>
typename CircularList<DataType>::iterator CircularList<DataType>::begin()const
{
	return iterator(head->link);
}

template<typename DataType>
typename CircularList<DataType>::iterator CircularList<DataType>::tail()const
{
	CircularListNode<DataType> *p = head;
	for(int i = 0; i < length; i++, p = p->link){}
	return iterator(p);
}

template<typename DataType>
CircularList<DataType>::CircularList(int n)
{
	if(n < 0)
	{
		cout << "Error in \'CircularList<DataType>::CircularList(int n)\', \'n\' must be positive." << endl;
		exit(-1);
	}

	CircularListNode<DataType>* p = head;
	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new CircularListNode<DataType>;
	}
	p->link = head->link;
	length = n;
}

template<typename DataType>
CircularList<DataType>::CircularList(int n, DataType element)
{
	if(n < 0)
	{
		cout << "Error in \'CircularList<DataType>::CircularList(int n, DataType)\', \'n\' must be positive." << endl;
		exit(-1);
	}

	CircularListNode<DataType>* p = head;
 	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new CircularListNode<DataType>(element);
	}
	p->link = head->link;
	length = n;
}

template<typename DataType>
CircularList<DataType>::CircularList(const CircularList<DataType>& list)
{
	CircularListNode<DataType> *p = head;
	CircularListNode<DataType> *q = list.head;
	while(q->link != list.head->link)
	{
		p->link = new CircularListNode<DataType>(q->link->data);
		p = p->link;
		q = q->link;
	}
	p->link = head->link;
	length = list.length;
}

template<typename DataType>
CircularList<DataType>::~CircularList()
{
	CircularListNode<DataType> *p = head->link;
	for(int i = 0; i < length; i++)
	{
		head->link = p->link;
		delete p;
	}
	delete head;
}

template<typename DataType>
CircularList<DataType>& CircularList<DataType>::operator =(const CircularList<DataType>& list)
{
	CircularListNode<DataType> *p = head;
	CircularListNode<DataType> *q = list.head;
	while(q->link != list.head->link)
	{
		p->link = new CircularListNode<DataType>(q->link->data);
		p = p->link;
		q = q->link;
	}
	p->link = head->link;
	length = list.length;

	return *this;
}

template<typename DataType>
void CircularList<DataType>::clear()
{
	CircularListNode<DataType> *p = head->link;
	for(int i = 0; i < length; i++)
	{
		head->link = p->link;
		delete p;
	}
	length = 0;
}

template<typename DataType>
int CircularList<DataType>::size()const
{
	return length;
}

template<typename DataType>
bool CircularList<DataType>::empty()const
{
	return (length == 0);
}

template<typename DataType>
DataType& CircularList<DataType>::operator [](int n)
{
	if(length == 0)
	{
		cout << "Error in \'DataType& List<DataType>::operator [](int n)\':" << endl
			 << "Empty list." << endl;
		exit(-1);
	}
	if(n < 0)
	{
		cout << "Error in \'DataType& List<DataType>::operator [](int n)\':" << endl
			 << "Index \'n\' must be positive." << endl;
		exit(-1);
	}

	CircularListNode<DataType> *p = head->link;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<typename DataType>
DataType CircularList<DataType>::operator [](int n)const
{
	if(length == 0)
	{
		cout << "Error in \'DataType CircularList<DataType>::operator [](int n)const\':" << endl
			 << "Empty list." << endl;
		exit(-1);
	}
	if(n < 0)
	{
		cout << "Error in \'DataType List<DataType>::operator [](int n)const\':" << endl
			 << "Index \'n\' is out of list range." << endl;
		exit(-1);
	}

	CircularListNode<DataType> *p = head->link;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<typename DataType>
int CircularList<DataType>::locate(DataType element)const
{
	CircularListNode<DataType> *p = head->link;
	for(int i = 0; i < length; i++, p = p->link)
	{
		if(p->data == element)
		{
			return i;
		}
	}
	return -1;
}

template<typename DataType>
bool CircularList<DataType>::insert(int n, DataType element)
{
	if(n < 0)
	{
		cout << "Warning in bool List<DataType>::insert(int n, DataType)" << endl
			 << "\'n\' must be positive. Nothing has been done." << endl;
		return false;
	}

	CircularListNode<DataType> *p = head;
	if(length == 0)
	{
		p->link = new CircularListNode<DataType>(element);
		p = p->link;
		p->link = p;
		length++;
		return true;
	}

	for(int i = 0; i < n; i++, p = p->link){}
	CircularListNode<DataType> *q = p->link;
	p->link = new CircularListNode<DataType>(element);
	p = p->link;
	p->link = q;
	length++;
	return true;
}

template<typename DataType>
bool CircularList<DataType>::erase(int n)
{
	if(length == 0)
	{
		cout << "Warning in bool List<DataType>::erase(int)" << endl
			 << "Empty list. Nothing has been done." << endl;
		return false;
	}
	if(n < 0)
	{
		cout << "Warning in bool List<DataType>::erase(int n)" << endl
			 << "\'n\' must be positive. Nothing has been done." << endl;
		return false;
	}

	CircularListNode<DataType> *p = head;
	for(int i = 0; i < n; i++, p = p->link){}
	CircularListNode<DataType> *q = p->link;
	p->link = q->link;
	if(q == head->link)
	{
		head->link = q->link;
	}
	delete q;
	length--;
	return true;
}

template<typename DataType>
void CircularList<DataType>::push_back(DataType element)
{
	CircularListNode<DataType> *p = head;
	for(int i = 0; i < length; i++, p = p->link){}
	p->link = new CircularListNode<DataType>(element);
	p = p->link;
	p->link = head->link;
	length++;
}

template<typename DataType>
void CircularList<DataType>::push_front(DataType element)
{
	CircularListNode<DataType> *p = head;
	CircularListNode<DataType> *q = head->link;
	CircularListNode<DataType> *tail = head;
	for(int i = 0; i < length; i++, tail = tail->link){}
	p->link = new CircularListNode<DataType>(element);
	p = p->link;
	p->link = q;
	tail->link = p;
	length++;
}

template<typename DataType>
DataType CircularList<DataType>::pop_back()
{
	if(length == 0)
	{
		cout << "Error in \'DataType CircularList<DataType>::pop_back()\'." << endl
			 << "Empty list." << endl;
		exit(-1);
	}

	CircularListNode<DataType> *p = head;
	for(int i = 0; i < length-1; i++, p = p->link){}

	DataType element = p->link->data;
	delete p->link;
	p->link = head->link;
	length--;
	return element;
}

template<typename DataType>
DataType CircularList<DataType>::pop_front()
{
	if(length == 0)
	{
		cout << "Error in \'DataType CircularList<DataType>::pop_front()\'" << endl
			 << "Empty list." << endl;
		exit(-1);
	}

	CircularListNode<DataType> *p = head->link;
	DataType element = p->data;
	if(length != 1)
	{
		head->link = p->link;
	}
	else
	{
		head->link = NULL;
	}
	delete p;
	length--;
	return element;
}

template<typename DataType>
bool CircularList<DataType>::swap(int i, int j)
{
	if(length == 0)
	{
		cout << "Warning in bool List<DataType>::swap(int i, int j)" << endl
			 << "Empty list. Nothing has been done." << endl;
		return false;
	}

	i = i % length;
	j = j % length;

	if(i < 0 || j < 0 || i == j)
	{
		cout << "Warning in bool List<DataType>::swap(int i, int j)" << endl
			 << "i or j is(are) negtive, or try to swap the same position. Nothing has been done." << endl;
		return false;
	}

	if(i > j)
	{
		std::swap(i, j);
	}

	CircularListNode<DataType> *pi_last = head;
	for(int it = 0; it < i; it++, pi_last = pi_last->link){}
	CircularListNode<DataType> *pj_last = head;
	for(int it = 0; it < j; it++, pj_last = pj_last->link){}

	CircularListNode<DataType> *pi = pi_last->link;
	CircularListNode<DataType> *pj = pj_last->link;
	CircularListNode<DataType> *pj_next = pj->link;

	if(head->link == pi)
	{
		head->link = pj;
	}
	else if(head->link == pj)
	{
		head->link = pi;
	}

	if(j-i > 1)
	{
		pi_last->link = pj;
		pj->link = pi->link;
		pj_last->link = pi;
		pi->link = pj_next;
	}
	else
	{
		pi_last->link = pj;
		pj->link = pi;
		pi->link = pj_next;
	}

	return true;
}

#endif