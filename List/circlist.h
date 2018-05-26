#ifndef CIRCLIST_H
#define CIRCLIST_H

#include <iostream>
#include <iterator>

using namespace std;

template<typename DataType>
class CircNode
{
public:
	DataType data;
	CircNode<DataType> *link = NULL;

public:
	CircNode<DataType>(){};
	CircNode<DataType>(DataType element)
	{
		data = element;
	}
};

template<class Class, typename DataType>
class CircListIterator : public iterator<input_iterator_tag, Class>
{
private:
	Class* _ptr = NULL;

public:
	CircListIterator()
	{
		_ptr = NULL;
	}

	CircListIterator(Class *p)
	{
		_ptr = p;
	}

	~CircListIterator()
	{
		_ptr = NULL;
	}

    CircListIterator& operator =(const CircListIterator& it)
    {
        _ptr = it._ptr;
    }

    bool operator !=(const CircListIterator& it)
    {
        return (_ptr != it._ptr);
    }

    bool operator ==(const CircListIterator& it)
    {
        return (_ptr == it._ptr);
    }

    CircListIterator& operator ++()
    {
        _ptr = _ptr->link;
        return *this;
    }

    CircListIterator operator ++(int)
    {
        CircListIterator temp = *this;
        _ptr = _ptr->link;
        return temp;
    }

    DataType& operator *()
    {
        return _ptr->data;
    }
};

template<typename DataType>
class CircList
{
	friend ostream & operator <<(ostream& out, const CircList<DataType>& list)
	{
		CircList<DataType>::iterator it = list.begin();
		for(int i = 0; i < list.size(); i++, it++)
		{
			out << (*it) << endl;
		}

		return out;
	}

private:
	CircNode<DataType> *head = new CircNode<DataType>();
	int length = 0;

public:
	typedef CircListIterator< CircNode<DataType>, DataType > iterator;

public:
	CircList<DataType>(){};
	CircList<DataType>(int n);
	CircList<DataType>(int n, DataType element);
	CircList<DataType>(const CircList<DataType>& list);
	~CircList<DataType>();
	CircList<DataType>& operator =(const CircList<DataType>& list);
	void clear();
	int size()const;
	bool empty()const;
	DataType& operator [](int i);
	DataType operator [](int i)const;
	int locate(DataType element)const;
	void insert(int n, DataType element);
	bool erase(int n);
	void push_back(DataType element);
	void push_front(DataType element);
	DataType pop_back();
	DataType pop_front();
	bool swap(int i, int j);
	CircList<DataType> cat(const CircList<DataType>& list);
	iterator begin()const;
	iterator tail()const;
};

template<typename DataType>
typename CircList<DataType>::iterator CircList<DataType>::begin()const
{
	return iterator(head->link);
}

template<typename DataType>
typename CircList<DataType>::iterator CircList<DataType>::tail()const
{
	CircNode<DataType> *p = head;
	for(int i = 0; i < length; i++, p = p->link){}
	return iterator(p);
}

template<typename DataType>
CircList<DataType>::CircList(int n)
{
	if(n < 0)
	{
		cout << "Error in \'CircList<DataType>::CircList(int n)\', \'n\' must be positive." << endl;
		exit(-1);
	}

	CircNode<DataType>* p = head;
	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new CircNode<DataType>;
	}
	p->link = head->link;
	length = n;
}

template<typename DataType>
CircList<DataType>::CircList(int n, DataType element)
{
	if(n < 0)
	{
		cout << "Error in \'CircList<DataType>::CircList(int n, DataType)\', \'n\' must be positive." << endl;
		exit(-1);
	}

	CircNode<DataType>* p = head;
 	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new CircNode<DataType>(element);
	}
	p->link = head->link;
	length = n;
}

template<typename DataType>
CircList<DataType>::CircList(const CircList<DataType>& list)
{
	CircNode<DataType> *p = head;
	CircNode<DataType> *q = list.head;
	for(int i = 0; i < list.length; i++)
	{
		p->link = new CircNode<DataType>(q->link->data);
		p = p->link;
		q = q->link;
	}
	p->link = head->link;
	length = list.length;
}

template<typename DataType>
CircList<DataType>::~CircList()
{
	for(int i = 0; i < length; i++)
	{
		CircNode<DataType> *p = head->link;
		head->link = p->link;
		delete p;
	}
	delete head;
}

template<typename DataType>
CircList<DataType>& CircList<DataType>::operator =(const CircList<DataType>& list)
{
	CircNode<DataType> *p = head;
	CircNode<DataType> *q = list.head;
	for(int i = 0; i < list.length; i++)
	{
		p->link = new CircNode<DataType>(q->link->data);
		p = p->link;
		q = q->link;
	}
	p->link = head->link;
	length = list.length;

	return *this;
}

template<typename DataType>
void CircList<DataType>::clear()
{
	for(int i = 0; i < length; i++)
	{
		CircNode<DataType> *p = head->link;
		head->link = p->link;
		delete p;
	}
	head->link = NULL;
	length = 0;
}

template<typename DataType>
int CircList<DataType>::size()const
{
	return length;
}

template<typename DataType>
bool CircList<DataType>::empty()const
{
	return (length == 0);
}

template<typename DataType>
DataType& CircList<DataType>::operator [](int n)
{
	if(length == 0)
	{
		cout << "Error in \'DataType& List<DataType>::operator [](int n)\':" << endl
			 << "Empty list." << endl;
		exit(-1);
	}
	n = n % length;
	if(n < 0)
	{
		n += length;
	}

	CircNode<DataType> *p = head->link;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<typename DataType>
DataType CircList<DataType>::operator [](int n)const
{
	if(length == 0)
	{
		cout << "Error in \'DataType CircList<DataType>::operator [](int n)const\':" << endl
			 << "Empty list." << endl;
		exit(-1);
	}
	n = n % length;
	if(n < 0)
	{
		n += length;
	}

	CircNode<DataType> *p = head->link;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<typename DataType>
int CircList<DataType>::locate(DataType element)const
{
	CircNode<DataType> *p = head->link;
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
void CircList<DataType>::insert(int n, DataType element)
{
	bool flag = false;
	int N = n % length;
	if(n != 0 && N == 0)
	{
		flag = true;
	}
	n = N;
	if(n < 0)
	{
		n += length;
	}

	CircNode<DataType> *p = head;
	if(length == 0)
	{
		p->link = new CircNode<DataType>(element);
		p = p->link;
		p->link = p;
		length++;
		return;
	}

	CircNode<DataType> *rear = head;
	for(int i = 0; i < n; i++, p = p->link){}
	for(int i = 0; i < length; i++, rear = rear->link){}

	if(flag)
	{
		rear->link = new CircNode<DataType>(element);
		rear = rear->link;
		rear->link = head->link;
		length++;
		return;
	}

	CircNode<DataType> *q = p->link;
	p->link = new CircNode<DataType>(element);
	p = p->link;
	p->link = q;
	rear->link = head->link;
	length++;
}

template<typename DataType>
bool CircList<DataType>::erase(int n)
{
	if(length == 0)
	{
		cout << "Warning in bool List<DataType>::erase(int)" << endl
			 << "Empty list. Nothing has been done." << endl;
		return false;
	}
	n = n % length;
	if(n < 0)
	{
		n += length;
	}

	CircNode<DataType> *p = head;
	for(int i = 0; i < n; i++, p = p->link){}
	CircNode<DataType> *q = p->link;
	p->link = q->link;
	if(q == head->link)
	{
		head->link = q->link;
	}
	delete q;
	length--;
	if(length == 0)
	{
		head->link = NULL;
	}
	return true;
}

template<typename DataType>
void CircList<DataType>::push_back(DataType element)
{
	CircNode<DataType> *p = head;
	for(int i = 0; i < length; i++, p = p->link){}
	p->link = new CircNode<DataType>(element);
	p = p->link;
	p->link = head->link;
	length++;
}

template<typename DataType>
void CircList<DataType>::push_front(DataType element)
{
	CircNode<DataType> *p = head;
	CircNode<DataType> *q = head->link;
	CircNode<DataType> *tail = head;
	for(int i = 0; i < length; i++, tail = tail->link){}
	p->link = new CircNode<DataType>(element);
	p = p->link;
	p->link = q;
	tail->link = p;
	length++;
}

template<typename DataType>
DataType CircList<DataType>::pop_back()
{
	if(length == 0)
	{
		cout << "Error in \'DataType CircList<DataType>::pop_back()\'." << endl
			 << "Empty list." << endl;
		exit(-1);
	}

	CircNode<DataType> *p = head;
	for(int i = 0; i < length-1; i++, p = p->link){}

	DataType element = p->link->data;
	delete p->link;
	if(length != 1)
	{
		p->link = head->link;
	}
	else
	{
		head->link = NULL;
	}
	length--;
	return element;
}

template<typename DataType>
DataType CircList<DataType>::pop_front()
{
	if(length == 0)
	{
		cout << "Error in \'DataType CircList<DataType>::pop_front()\'" << endl
			 << "Empty list." << endl;
		exit(-1);
	}

	CircNode<DataType> *p = head->link;
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
bool CircList<DataType>::swap(int i, int j)
{
	if(length == 0)
	{
		cout << "Warning in bool List<DataType>::swap(int i, int j)" << endl
			 << "Empty list. Nothing has been done." << endl;
		return false;
	}

	i = i % length;
	j = j % length;
	if(i < 0)
	{
		i += length;
	}
	if(j < 0)
	{
		j += length;
	}

	if(i == j)
	{
		cout << "Warning in bool List<DataType>::swap(int i, int j)" << endl
			 << "i or j is(are) negtive, or try to swap the same position. Nothing has been done." << endl;
		return false;
	}

	if(i > j)
	{
		std::swap(i, j);
	}

	CircNode<DataType> *pi_last = head;
	for(int it = 0; it < i; it++, pi_last = pi_last->link){}
	CircNode<DataType> *pj_last = head;
	for(int it = 0; it < j; it++, pj_last = pj_last->link){}

	CircNode<DataType> *pi = pi_last->link;
	CircNode<DataType> *pj = pj_last->link;
	CircNode<DataType> *pj_next = pj->link;

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

template<typename DataType>
CircList<DataType> CircList<DataType>::cat(const CircList<DataType>& list)
{
	CircNode<DataType> *p = head;
	for(int i = 0; i < length; i++, p = p->link){}

	CircNode<DataType> *q = list.head->link;
	for(int i = 0; i < list.length; i++, p = p->link, q = q->link)
	{
		p->link = new CircNode<DataType>(q->data);
	}

	p->link = head->link;
	length += list.length;

	return *this;
}

#endif