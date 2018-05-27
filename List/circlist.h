#ifndef CIRCLIST_H
#define CIRCLIST_H

#include <iostream>

using namespace std;

template<typename DataType>
class CircList
{
	friend ostream & operator <<(ostream& out, const CircList<DataType>& list) // tested
	{
		out << endl;
		CircList<DataType>::iterator it = list.begin();
		for(int i = 0; i < list.size(); i++, it++)
		{
			out << (*it) << endl;
		}

		return out;
	}

private:
	class Node
	{
	public:
		DataType data;
		Node *link = NULL;

		Node(){}
		Node(DataType element): data(element){}
		Node(Node *ptr): link(ptr){}
		Node(DataType element, Node *ptr): data(element), link(ptr){}
		~Node(){link = NULL;}
	}*first = NULL, *rear = NULL;
	int length = 0;

private:
	Node* creat_node()const;
	Node* creat_node(DataType element)const;
	Node* creat_node(DataType element, Node* ptr)const;
	Node* creat_node(Node* node)const;
	void memory_error(Node* p)const;
	
public:
	class iterator
	{
	public:
		Node* ptr = NULL;

	public:
		iterator(){}
		iterator(Node* p): ptr(p){}
		iterator(const iterator& it): ptr(it.ptr){}
		~iterator(){ptr = NULL;}
		iterator& operator =(const iterator& it){ptr = it.ptr; return *this;}
		bool operator ==(const iterator& it){return (ptr == it.ptr);}
		bool operator !=(const iterator& it){return (ptr != it.ptr);}
		DataType& operator *(){return ptr->data;}
		iterator& operator ++(){ptr = ptr->link; return *this;}
	    iterator operator ++(int){iterator it_temp = *this; ptr = ptr->link; return it_temp;}
	};

	class const_iterator
	{
	public:
		Node* ptr = NULL;

	public:
		const_iterator(){}
		const_iterator(Node* p): ptr(p){}
		const_iterator(const iterator& it): ptr(it.ptr){}
		const_iterator(const const_iterator& it): ptr(it.ptr){}
		~const_iterator(){ptr = NULL;}
		const_iterator& operator =(const iterator& it){ptr = it.ptr;return *this;}
		const_iterator& operator =(const const_iterator& it){ptr = it.ptr;return *this;}
		bool operator ==(const iterator& it){return (ptr == it.ptr);}
		bool operator ==(const const_iterator& it){return (ptr == it.ptr);}
		bool operator !=(const iterator& it){return (ptr != it.ptr);}
		bool operator !=(const const_iterator& it){return (ptr != it.ptr);}
		DataType operator *(){return ptr->data;}
		const_iterator& operator ++(){ptr = ptr->link; return *this;}
	    const_iterator operator ++(int){const_iterator it_temp = *this; ptr = ptr->link; return it_temp;}
	};

public:
	CircList<DataType>(){}; // tested
	CircList<DataType>(int n); // tested
	CircList<DataType>(int n, DataType element); // tested
	CircList<DataType>(const CircList<DataType>& list); // tested
	~CircList<DataType>(); // tested
	void clear(); // tested
	CircList<DataType>& operator =(const CircList<DataType>& list); // tested
	int size()const; // tested
	bool empty()const; // tested
	DataType& operator [](int i); // tested
	DataType operator [](int i)const; // tested
	int locate(DataType element)const;
	void insert(int n, DataType element); // tested
	bool erase(int n); // tested
	void push_back(DataType element); // tested
	void push_front(DataType element); // tested
	DataType pop_back(); // tested
	DataType pop_front(); // tested
	bool swap(int i, int j); // tested
	CircList<DataType> cat(const CircList<DataType>& list); // tested
	iterator begin()const{return iterator(first);}
	iterator last()const{return iterator(rear);}
};

template<typename DataType>
void CircList<DataType>::memory_error(CircList<DataType>::Node* p)const
{
	if(!p)
	{
		cerr << "Error when creating list node." << endl
			 << "Failed to allocate memory!" << endl;
		exit(-1);
	}
}

template<typename DataType>
typename CircList<DataType>::Node* CircList<DataType>::creat_node()const
{
	CircList<DataType>::Node* p = new CircList<DataType>::Node;
	memory_error(p);

	return p;
}

template<typename DataType>
typename CircList<DataType>::Node* CircList<DataType>::creat_node(DataType element)const
{
	CircList<DataType>::Node* p = new CircList<DataType>::Node(element);
	memory_error(p);

	return p;
}

template<typename DataType>
typename CircList<DataType>::Node* CircList<DataType>::creat_node(DataType element, CircList<DataType>::Node* ptr)const
{
	CircList<DataType>::Node* p = new CircList<DataType>::Node(element, ptr);
	memory_error(p);

	return p;
}

template<typename DataType>
typename CircList<DataType>::Node* CircList<DataType>::creat_node(CircList<DataType>::Node *node)const
{
	CircList<DataType>::Node* p = new CircList<DataType>::Node(node->data);
	memory_error(p);

	return p;
}

template<typename DataType>
CircList<DataType>::CircList(int n)
{
	if(n < 0)
	{
		cout << "Error in \'CircList<DataType>::CircList(int n)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}
	if(n == 0)
	{
		return;
	}

	first = creat_node();
	CircList<DataType>::Node* p = first;
	for(int i = 1; i < n; i++)
	{
		p->link = creat_node();
		p = p->link;
	}
	p->link = first;
	rear = p;
	length = n;
}

template<typename DataType>
CircList<DataType>::CircList(int n, DataType element)
{
	if(n < 0)
	{
		cout << "Error in \'CircList<DataType>::CircList(int n, DataType element)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}
	if(n == 0)
	{
		return;
	}

	first = creat_node(element);
	CircList<DataType>::Node* p = first;
	for(int i = 1; i < n; i++)
	{
		p->link = creat_node(element);
		p = p->link;
	}
	p->link = first;
	rear = p;
	length = n;
}

template<typename DataType>
CircList<DataType>::CircList(const CircList<DataType>& list)
{
	if(list.length == 0)
	{
		return;
	}
	
	first = creat_node(list.first);
	CircList<DataType>::Node *p = first;
	CircList<DataType>::Node *q = list.first;
	for(int i = 1; i < list.length; i++)
	{
		p->link = creat_node(q->link);
		p = p->link;
		q = q->link;
	}
	p->link = first;
	rear = p;
	length = list.length;
}

template<typename DataType>
CircList<DataType>::~CircList()
{
	if(length != 0)
	{
		while(first->link != first)
		{
			CircList<DataType>::Node *p = first->link;
			first->link = p->link;
			delete p;
		}
		delete first;
		length = 0;
	}
}

template<typename DataType>
void CircList<DataType>::clear()
{
	if(length != 0)
	{
		while(first->link != first)
		{
			CircList<DataType>::Node *p = first->link;
			first->link = p->link;
			delete p;
		}
		delete first;

		first = NULL;
		rear = NULL;
		length = 0;
	}
}

template<typename DataType>
CircList<DataType>& CircList<DataType>::operator =(const CircList<DataType>& list)
{
	clear();
	if(list.length == 0)
	{
		return *this;
	}
	
	first = creat_node(list.first);
	CircList<DataType>::Node *p = first;
	CircList<DataType>::Node *q = list.first;
	for(int i = 1; i < list.length; i++)
	{
		p->link = creat_node(q->link);
		p = p->link;
		q = q->link;
	}
	p->link = first;
	rear = p;
	length = list.length;

	return *this;
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
		cout << "Error in \'DataType& CircList<DataType>::operator [](int n)\':" << endl
			 << "Empty list." << endl;
		exit(-1);
	}
	n = n % length;
	if(n < 0)
	{
		n += length;
	}
	
	CircList<DataType>::Node *p = first;
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
	CircList<DataType> *p = first;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<typename DataType>
int CircList<DataType>::locate(DataType element)const
{
	if(length == 0)
	{
		return -1;
	}

	CircList<DataType>::Node *p = first;
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
	if(length == 0)
	{
		first = creat_node(element);
		first->link = first;
		rear = first;
		length = 1;
		return;
	}

	int ni = n % length;
	if(ni < 0)
	{
		ni += length;
	}

	if(n == 0)
	{
		rear->link = creat_node(element, first);
		first = rear->link;
	}
	else if(ni == 0)
	{
		rear->link = creat_node(element, first);
		rear = rear->link;
	}
	else
	{
		CircList<DataType>::Node *p = first;
		for(int i = 0; i < ni-1; i++, p = p->link){}
		p->link = creat_node(element, p->link);
	}
	length++;
}

template<typename DataType>
bool CircList<DataType>::erase(int n)
{
	if(length == 0)
	{
		cout << "Warning in bool List<DataType>::erase(int):" << endl
			 << "Empty list. Nothing has been done." << endl;
		return false;
	}
	else if(length == 1)
	{
		delete first;
		first = NULL;
		rear = NULL;
		length = 0;
		return true;
	}

	n = n % length;
	if(n < 0)
	{
		n += length;
	}

	CircList<DataType>::Node *p = first;
	for(int i = 0; i < n-1; i++, p = p->link){}
	CircList<DataType>::Node *q = p->link;
	p->link = q->link;
	if(q == first)
	{
		first = q->link;
	}
	else if(q == rear)
	{
		rear = p;
	}
	delete q;
	length--;
	return true;
}

template<typename DataType>
void CircList<DataType>::push_back(DataType element)
{
	if(length == 0)
	{
		first = creat_node(element);
		first->link = first;
		rear = first;
		length = 1;
		return;
	}

	rear->link = creat_node(element, first);
	rear = rear->link;
	length++;
}

template<typename DataType>
void CircList<DataType>::push_front(DataType element)
{
	if(length == 0)
	{
		first = creat_node(element);
		first->link = first;
		rear = first;
		length = 1;
		return;
	}

	rear->link = creat_node(element, first);
	first = rear->link;
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
	if(length == 1)
	{
		DataType element = rear->data;
		delete first;
		first = NULL;
		rear = NULL;
		length = 0;
		return element;
	}

	CircList<DataType>::Node *p = first;
	for(int i = 0; i < length-2; i++, p = p->link){}

	DataType element = rear->data;
	p->link = first;
	delete rear;
	rear = p;
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
	if(length == 1)
	{
		DataType element = first->data;
		delete first;
		first = NULL;
		rear = NULL;
		length = 0;
		return element;
	}

	DataType element = first->data;
	rear->link = first->link;
	delete first;
	first = rear->link;
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
			 << "Try to swap the same position. Nothing has been done." << endl;
		return false;
	}

	if(i > j)
	{
		std::swap(i, j);
	}

	CircList<DataType>::Node *pi_last;
	if(i == 0)
	{
		pi_last = rear;
	}
	else
	{
		pi_last = first;
		for(int it = 0; it < i-1; it++, pi_last = pi_last->link){}
	}
	CircList<DataType>::Node *pj_last = first;
	for(int it = 0; it < j-1; it++, pj_last = pj_last->link){}

	CircList<DataType>::Node *pi = pi_last->link;
	CircList<DataType>::Node *pj = pj_last->link;
	CircList<DataType>::Node *pi_next = pi->link;
	CircList<DataType>::Node *pj_next = pj->link;

	int situation = 0;
	if(first == pi)
	{
		first = pj;
		situation++;
	}

	if(rear == pj)
	{
		rear = pi;
		situation++;
	}

	if(situation == 2)
	{
		pj_last->link = pi;
		pi->link = pj;
		pj->link = pi_next;
		return true;
	}

	if(j-i > 1)
	{
		pi_last->link = pj;
		pj->link = pi->link;
		pj_last->link = pi;
		pi->link = pj_next;
		return true;
	}
	else
	{
		pi_last->link = pj;
		pj->link = pi;
		pi->link = pj_next;
		return true;
	}
}

template<typename DataType>
CircList<DataType> CircList<DataType>::cat(const CircList<DataType>& list)
{
	if(length == 0)
	{
		*this = list;
		return *this;
	}

	CircList<DataType>::Node *p = list.first;
	for(int i = 0; i < list.length; i++)
	{
		rear->link = creat_node(p);
		rear = rear->link;
		p = p->link;
	}
	rear->link = first;
	length += list.length;
	return *this;
}

#endif