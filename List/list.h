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

private:
	ListNode<DataType> *head = new ListNode<DataType>();
	int length = 0;

public:
	typedef ListIterator< ListNode<DataType>, DataType > iterator;

public:
	List<DataType>(){}; // finished, tested
	List<DataType>(int n); // finished, tested
	List<DataType>(int n, DataType element); // finished, tested
	List<DataType>(const List<DataType>& list); // finished, tested
	~List<DataType>(); // finished, tested
	List<DataType>& operator =(const List<DataType>& list); // finished, tested
	void clear(); // finished, tested
	int size()const; // finished, tested
	bool empty()const; // finished, tested
	DataType& operator [](int i); // finished, tested
	DataType operator [](int i)const; // finished, tested
	int locate(DataType element)const; // finished, tested
	bool insert(int i, DataType element); // finished, tested
	bool erase(int i); // finished, tested
	void push_back(DataType element); // finished, tested
	void push_front(DataType element); // finished, tested
	DataType pop_back(); // finished, tested
	DataType pop_front(); // finished, tested
	bool swap(int i, int j); // finished, tested
	List<DataType> cat(const List<DataType>& list); // finished, tested
	iterator begin()const; // finished, tested
	iterator end()const; // finished, tested
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
	if(n < 0)
	{
		cout << "Error in \'List<DataType>::List(int n)\', \'n\' must be positive." << endl;
		exit(-1);
	}

	ListNode<DataType>* p = head;
	for(int i = 0; i < n; i++,p = p->link)
	{
		p->link = new ListNode<DataType>;
	}
	length = n;
}

template<typename DataType>
List<DataType>::List(int n, DataType element)
{
	if(n < 0)
	{
		cout << "Error in \'List<DataType>::List(int n, DataType)\', \'n\' must be positive." << endl;
		exit(-1);
	}

	ListNode<DataType>* p = head;
 	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new ListNode<DataType>(element);
	}
	length = n;
}

template<typename DataType>
List<DataType>::List(const List<DataType>& list)
{
	ListNode<DataType> *p = head;
	ListNode<DataType> *q = list.head;
	while(q->link)
	{
		p->link = new ListNode<DataType>(q->link->data);
		p = p->link;
		q = q->link;
	}
	length = list.length;
}

template<typename DataType>
List<DataType>::~List()
{
	while(head->link != NULL)
	{
		ListNode<DataType>* p = head->link;
		head->link = p->link;
		delete p;
	}
	length = 0;
}

template<typename DataType>
List<DataType>& List<DataType>::operator =(const List<DataType>& list)
{
	ListNode<DataType> *p = head;
	ListNode<DataType> *q = list.head;
	while(q->link)
	{
		p->link = new ListNode<DataType>(q->link->data);
		p = p->link;
		q = q->link;
	}
	length = list.length;

	return *this;
}

template<typename DataType>
void List<DataType>::clear()
{
	while(head->link != NULL)
	{
		ListNode<DataType>* p = head->link;
		head->link = p->link;
		delete p;
	}
	length = 0;
}

template<typename DataType>
int List<DataType>::size()const
{
	return length;
}

template<typename DataType>
bool List<DataType>::empty()const
{
	return (length == 0);
}

template<typename DataType>
DataType& List<DataType>::operator [](int n)
{
	if(n < 0 || n >= length)
	{
		cout << "Error in \'DataType& List<DataType>::operator [](int n)\':" << endl
			 << "Index \'n\' is out of list range." << endl;
		exit(-1);
	}
	ListNode<DataType> *p = head->link;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<typename DataType>
DataType List<DataType>::operator [](int n)const
{
	if(n < 0 || n >= length)
	{
		cout << "Error in \'DataType List<DataType>::operator [](int n)const\':" << endl
			 << "Index \'n\' is out of list range." << endl;
		exit(-1);
	}
	ListNode<DataType> *p = head->link;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<typename DataType>
int List<DataType>::locate(DataType element)const
{
	int i = 0;
	ListNode<DataType> *p = head->link;
	while(p)
	{
		if(p->data == element)
		{
			return i;
		}
		i++;
		p = p->link;
	}
	return -1;
}

template<typename DataType>
bool List<DataType>::insert(int n, DataType element)
{
	if(n > length || n < 0)
	{
		cout << "Warning in bool List<DataType>::insert(int n, DataType)" << endl
			 << "\'n\' is not in [0, length]. Nothing has been done." << endl;
		return false;
	}
	ListNode<DataType> *p = head;
	for(int i = 0; i < n; i++, p = p->link){}
	ListNode<DataType> *q = p->link;
	p->link = new ListNode<DataType>(element);
	p = p->link;
	p->link = q;
	length++;
	return true;
}

template<typename DataType>
bool List<DataType>::erase(int n)
{
	if(n >= length || n < 0)
	{
		cout << "Warning in bool List<DataType>::erase(int n)" << endl
			 << "\'n\' is not in [0, length-1]. Nothing has been done." << endl;
		return false;
	}
	ListNode<DataType> *p = head;
	for(int i = 0; i < n; i++, p = p->link){}
	ListNode<DataType> *q = p->link;
	p->link = q->link;
	delete q;
	length--;
	return true;
}

template<typename DataType>
void List<DataType>::push_back(DataType element)
{
	ListNode<DataType> *p = head;
	while(p->link)
	{
		p = p->link;
	}
	p->link = new ListNode<DataType>(element);
	length++;
}

template<typename DataType>
void List<DataType>::push_front(DataType element)
{
	ListNode<DataType> *p = head;
	ListNode<DataType> *q = head->link;
	p->link = new ListNode<DataType>(element);
	p = p->link;
	p->link = q;
	length++;
}

template<typename DataType>
DataType List<DataType>::pop_back()
{
	if(empty())
	{
		cout << "Error: In \'DataType List<DataType>::pop_back()\' the list is empty." << endl;
		exit(-1);
	}

	ListNode<DataType> *p = head;
	while(p->link->link)
	{
		p = p->link;
	}

	DataType element = p->link->data;
	delete p->link;
	p->link = NULL;
	length--;
	return element;
}

template<typename DataType>
DataType List<DataType>::pop_front()
{
	if(empty())
	{
		cout << "Error: In \'DataType List<DataType>::pop_front()\' the list is empty." << endl;
		exit(-1);
	}

	ListNode<DataType> *p = head->link;
	DataType element = p->data;
	head->link = p->link;
	delete p;
	length--;
	return element;
}

template<typename DataType>
List<DataType> List<DataType>::cat(const List<DataType>& list)
{
	ListNode<DataType> *p = head;
	while(p->link)
	{
		p = p->link;
	}

	ListNode<DataType> *q = list.head->link;
	while(q)
	{
		p->link = new ListNode<DataType>(q->data);
		p = p->link;
		q = q->link;
	}
	length += list.length;
	return *this;
}

template<typename DataType>
bool List<DataType>::swap(int i, int j)
{
	if(i < 0 || i >= length || j < 0 || j >= length || i == j)
	{
		cout << "Warning in bool List<DataType>::swap(int i, int j)" << endl
			 << "i or j is(are) out of range, or i == j now. Nothing has been done." << endl;
		return false;
	}
	if(i > j)
	{
		std::swap(i, j);
	}

	ListNode<DataType> *pi_last = head;
	for(int it = 0; it < i; it++, pi_last = pi_last->link){}
	ListNode<DataType> *pj_last = head;
	for(int it = 0; it < j; it++, pj_last = pj_last->link){}

	ListNode<DataType> *pi = pi_last->link;
	ListNode<DataType> *pj = pj_last->link;
	ListNode<DataType> *pj_next = pj->link;

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