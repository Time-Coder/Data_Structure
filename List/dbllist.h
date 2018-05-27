#ifndef DBLLIST_H
#define DBLLIST_H

#include <iostream>
#include <iterator>

using namespace std;

template<typename DataType>
class DblNode
{
public:
	DataType data;
	DblNode<DataType> *left_link = NULL;
	DblNode<DataType> *right_link = NULL;

public:
	DblNode<DataType>(){};
	DblNode<DataType>(DataType element)
	{
		data = element;
	}
	DblNode<DataType>(DblNode<DataType> *lptr, DblNode<DataType> *rptr)
	{
		left_link = lprt;
		right_link = rptr;
	}
	DblNode<DataType>(DataType element, DblNode<DataType> *lptr, DblNode<DataType> *rptr)
	{
		data = element;
		left_link = lprt;
		right_link = rptr;
	}
	~DblNode<DataType>()
	{
		left_link = NULL;
		right_link = NULL;
	}
};

template<class Class, typename DataType>
class DblIterator : public iterator<input_iterator_tag, Class>
{
private:
	Class* _ptr = NULL;

public:
	DblIterator(){}

	DblIterator(Class *p)
	{
		_ptr = p;
	}

	~DblIterator()
	{
		_ptr = NULL;
	}

    DblIterator& operator =(const DblIterator& it)
    {
        _ptr = it._ptr;
    }

    bool operator !=(const DblIterator& it)
    {
        return (_ptr != it._ptr);
    }

    bool operator ==(const DblIterator& it)
    {
        return (_ptr == it._ptr);
    }

    DblIterator& operator ++()
    {
        _ptr = _ptr->right_link;
        return *this;
    }

    DblIterator operator ++(int)
    {
        DblIterator temp = *this;
        _ptr = _ptr->right_link;
        return temp;
    }

    DblIterator& operator --()
    {
        _ptr = _ptr->left_link;
        return *this;
    }

    DblIterator operator --(int)
    {
        DblIterator temp = *this;
        _ptr = _ptr->left_link;
        return temp;
    }

    DataType& operator *()
    {
        return _ptr->data;
    }
};

template<typename DataType>
class DblList
{
	friend ostream & operator <<(ostream& out, const DblList<DataType>& list)
	{
		for(DblList<DataType>::iterator it = list.begin(); it != list.end(); it++)
		{
			out << (*it) << endl;
		}

		return out;
	}

private:
	DblNode<DataType> *head = NULL;
	DblNode<DataType> *tail = NULL;
	int length = 0;

public:
	typedef DblIterator< DblNode<DataType>, DataType > iterator;

public:
	DblList<DataType>();
	DblList<DataType>(int n);
	DblList<DataType>(int n, DataType element);
	DblList<DataType>(const DblList<DataType>& list);
	~DblList<DataType>();
	DblList<DataType>& operator =(const DblList<DataType>& list);
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
	DblList<DataType> cat(const DblList<DataType>& list);
	iterator begin()const;
	iterator end()const;
};

template<typename DataType>
typename DblList<DataType>::iterator DblList<DataType>::begin()const
{
	return iterator(head->right_link);
}

template<typename DataType>
typename DblList<DataType>::iterator DblList<DataType>::end()const
{
	return iterator(tail);
}

template<typename DataType>
DblList<DataType>::DblList()
{
	head = new DblNode<DataType>;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	tail = new DblNode<DataType>(head, NULL);
	if(!tail)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	head->right_link = tail;
}

template<typename DataType>
DblList<DataType>::DblList(int n)
{
	if(n < 0)
	{
		cout << "Error in \'DblList<DataType>::DblList(int n)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}

	head = new DblNode<DataType>;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	tail = new DblNode<DataType>;
	if(!tail)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	DblNode<DataType>* p = head;
	for(int i = 0; i < n; i++, p = p->right_link)
	{
		p->right_link = new DblNode<DataType>(p, NULL);
		if(!(p->right_link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
	}
	p->right_link = tail;
	tail->left_link = p;
	length = n;
}

template<typename DataType>
DblList<DataType>::DblList(int n, DataType element)
{
	if(n < 0)
	{
		cout << "Error in \'DblList<DataType>::DblList(int n, DataType)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}

	head = new DblNode<DataType>;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	tail = new DblNode<DataType>;
	if(!tail)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	DblNode<DataType>* p = head;
	for(int i = 0; i < n; i++, p = p->right_link)
	{
		p->right_link = new DblNode<DataType>(element, p, NULL);
		if(!(p->right_link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
	}
	p->right_link = tail;
	tail->left_link = p;
	length = n;
}

template<typename DataType>
DblList<DataType>::DblList(const DblList<DataType>& list)
{
	head = new DblNode<DataType>;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	tail = new DblNode<DataType>;
	if(!tail)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	DblNode<DataType> *p = head;
	DblNode<DataType> *q = list.head;
	while(q->right_link != list.tail)
	{
		p->right_link = new DblNode<DataType>(q->right_link->data, p, NULL);
		if(!(p->right_link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		p = p->right_link;
		q = q->right_link;
	}
	p->right_link = tail;
	tail->left_link = p;
	length = list.length;
}

template<typename DataType>
DblList<DataType>::~DblList()
{
	while(head->right_link != tail)
	{
		DblNode<DataType>* p = head->right_link;
		head->right_link = p->right_link;
		delete p;
	}
	length = 0;
	delete head;
	delete tail;
}

template<typename DataType>
DblList<DataType>& DblList<DataType>::operator =(const DblList<DataType>& list)
{
	clear();
	DblNode<DataType> *p = head;
	DblNode<DataType> *q = list.head;
	while(q->right_link != list.tail)
	{
		p->right_link = new DblNode<DataType>(q->right_link->data, p, NULL);
		if(!(p->right_link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		p = p->right_link;
		q = q->right_link;
	}
	p->right_link = tail;
	tail->left_link = p;
	length = list.length;

	return *this;
}

template<typename DataType>
void DblList<DataType>::clear()
{
	while(head->right_link != tail)
	{
		DblNode<DataType>* p = head->right_link;
		head->right_link = p->right_link;
		delete p;
	}
	length = 0;
}

template<typename DataType>
int DblList<DataType>::size()const
{
	return length;
}

template<typename DataType>
bool DblList<DataType>::empty()const
{
	return (length == 0);
}

template<typename DataType>
DataType& DblList<DataType>::operator [](int n)
{
	if(n < 0 || n >= length)
	{
		cout << "Error in \'DataType& DblList<DataType>::operator [](int n)\':" << endl
			 << "\'n\' is out of list range." << endl;
		exit(-1);
	}

	DblNode<DataType> *p = head->right_link;
	for(int i = 0; i < n; i++, p = p->right_link){}
	return p->data;
}

template<typename DataType>
DataType DblList<DataType>::operator [](int n)const
{
	if(n < 0 || n >= length)
	{
		cout << "Error in \'DataType DblList<DataType>::operator [](int n)const\':" << endl
			 << "\'n\' is out of list range." << endl;
		exit(-1);
	}

	DblNode<DataType> *p = head->right_link;
	for(int i = 0; i < n; i++, p = p->right_link){}
	return p->data;
}

template<typename DataType>
int DblList<DataType>::locate(DataType element)const
{
	int i = 0;
	DblNode<DataType> *p = head->right_link;
	while(p != tail)
	{
		if(p->data == element)
		{
			return i;
		}
		i++;
		p = p->right_link;
	}
	return -1;
}

template<typename DataType>
bool DblList<DataType>::insert(int n, DataType element)
{
	if(n > length || n < 0)
	{
		cout << "Warning in bool DblList<DataType>::insert(int n, DataType)" << endl
			 << "\'n\' is not in [0, length]. Nothing has been done." << endl;
		return false;
	}
	DblNode<DataType> *p = head;
	for(int i = 0; i < n; i++, p = p->right_link){}
	DblNode<DataType> *q = p->right_link;
	p->right_link = new DblNode<DataType>(element, p, q);
	if(!(p->right_link))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	q->left_link = p->right_link;
	length++;
	return true;
}

template<typename DataType>
bool DblList<DataType>::erase(int n)
{
	if(n >= length || n < 0)
	{
		cout << "Warning in bool DblList<DataType>::erase(int n)" << endl
			 << "\'n\' is not in [0, length-1]. Nothing has been done." << endl;
		return false;
	}
	DblNode<DataType> *p = head;
	for(int i = 0; i < n; i++, p = p->right_link){}
	DblNode<DataType> *q = p->right_link;
	p->right_link = q->right_link;
	q->right_link->left_link = p;
	delete q;
	length--;
	return true;
}

template<typename DataType>
void DblList<DataType>::push_back(DataType element)
{
	DblNode<DataType> *p = tail->left_link;
	tail->left_link = new DblNode<DataType>(element, p, tail);
	if(!(tail->left_link))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	p->right_link = tail->left_link;
	length++;
}

template<typename DataType>
void DblList<DataType>::push_front(DataType element)
{
	DblNode<DataType> *p = head->right_link;
	head->right_link = new DblNode<DataType>(element, head, p);
	if(!(head->right_link))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	p->left_link = head->right_link;
	length++;
}

template<typename DataType>
DataType DblList<DataType>::pop_back()
{
	if(length == 0)
	{
		cout << "Error in \'DataType DblList<DataType>::pop_back()\'" << endl
			 << "The list is empty." << endl;
		exit(-1);
	}

	DblNode<DataType> *p = tail->left_link;
	DataType element = p->data;
	p->left_link->right_link = tail;
	tail->left_link = p->left_link;
	delete p;
	length--;
	return element;
}

template<typename DataType>
DataType DblList<DataType>::pop_front()
{
	if(length == 0)
	{
		cout << "Error in \'DataType DblList<DataType>::pop_front()\'" << endl
			 << "The list is empty." << endl;
		exit(-1);
	}

	DblNode<DataType> *p = head->right_link;
	DataType element = p->data;
	p->right_link->left_link = head;
	head->right_link = p->right_link;
	delete p;
	length--;
	return element;
}

template<typename DataType>
DblList<DataType> DblList<DataType>::cat(const DblList<DataType>& list)
{
	DblNode<DataType> *p = list.head->right_link;
	while(p != list.tail)
	{
		DblNode<DataType> *q = tail->left_link;
		tail->left_link = new DblNode<DataType>(p->data, q, tail);
		if(!(tail->left_link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		q->right_link = tail->left_link;
		p = p->right_link;
	}
	
	length += list.length;
	return *this;
}

template<typename DataType>
bool DblList<DataType>::swap(int i, int j)
{
	if(i < 0 || i >= length || j < 0 || j >= length || i == j)
	{
		cout << "Warning in bool DblList<DataType>::swap(int i, int j)" << endl
			 << "i or j is(are) out of range, or i == j now. Nothing has been done." << endl;
		return false;
	}
	if(i > j)
	{
		std::swap(i, j);
	}

	DblNode<DataType> *pi_last = head;
	for(int it = 0; it < i; it++, pi_last = pi_last->right_link){}
	DblNode<DataType> *pj_last = head;
	for(int it = 0; it < j; it++, pj_last = pj_last->right_link){}

	DblNode<DataType> *pi = pi_last->right_link;
	DblNode<DataType> *pj = pj_last->right_link;
	DblNode<DataType> *pj_next = pj->right_link;

	if(j-i > 1)
	{
		pi_last->right_link = pj;
		pj->left_link = pi_last;
		pj->right_link = pi->right_link;
		pi->right_link->left_link = pj;
		pj_last->right_link = pi;
		pi->left_link = pj_last;
		pi->right_link = pj_next;
		pj_next->left_link = pi;
	}
	else
	{
		pi_last->right_link = pj;
		pj->left_link = pi_last;
		pj->right_link = pi;
		pi->left_link = pj;
		pi->right_link = pj_next;
		pj_next->left_link = pi;
	}

	return true;
}

#endif