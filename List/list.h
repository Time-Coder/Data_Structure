#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iterator>

using namespace std;

template<class DataType>
class List
{
private:
	class Node
	{
	public:
		DataType data;
		Node *link = NULL;

	public:
		Node(){}
		Node(const DataType& element) : data(element){}
		Node(const DataType& element, Node *ptr) : data(element), link(ptr) {}
		~Node(){link = NULL;}
	};

public:
	class iterator
	{
	private:
		Node* _ptr = NULL;

	public:
		iterator() : _ptr(NULL){}
		iterator(Node *p) : _ptr(p){}
	    iterator& operator =(const iterator& it){_ptr = it._ptr;}
	    bool operator !=(const iterator& it){return (_ptr != it._ptr);}
	    bool operator ==(const iterator& it){return (_ptr == it._ptr);}
	    bool operator ==(Node* ptr){return _ptr == ptr;}
	    bool operator !=(Node* ptr){return _ptr != ptr;}
	    DataType& operator *(){return _ptr->data;}
	    DataType* operator ->(){return &(_ptr->data);}
	    DataType* ptr(){return &(_ptr->data);}

	    iterator& operator ++()
	    {
	        _ptr = _ptr->link;
	        return *this;
	    }

	    iterator operator ++(int)
	    {
	        iterator temp = *this;
	        _ptr = _ptr->link;
	        return temp;
	    }
	};

private:
	Node *head = NULL; // point to head node (not the first node, before first node)
	Node *_rear = NULL; // point to last node
	int length = 0;

public:
	List<DataType>(); // finished, tested
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
	List<DataType>::iterator find(const DataType& element)const; // finished, tested
	List<DataType>::iterator locate(int i)const;
	int locate(List<DataType>::iterator it)const;
	int locate(DataType* ptr)const;
	bool insert(int i, const DataType& element); // finished, tested
	iterator erase(int i); // finished, tested
	iterator erase(DataType* ptr);
	iterator erase(iterator it);
	void push_back(const DataType& element); // finished, tested
	void push_front(const DataType& element); // finished, tested
	DataType pop_back(); // finished, tested
	DataType pop_front(); // finished, tested
	bool swap(int i, int j); // finished, tested
	List<DataType> cat(const List<DataType>& list); // finished, tested
	iterator begin()const; // finished, tested
	iterator end()const; // finished, tested
	iterator rear()const;

	template<class ElemType>
	friend ostream & operator <<(ostream& out, const List<ElemType>& list);
};

template<class DataType>
typename List<DataType>::iterator List<DataType>::begin()const
{
	return iterator(head->link);
}

template<class DataType>
typename List<DataType>::iterator List<DataType>::end()const
{
	return iterator(NULL);
}

template<class DataType>
typename List<DataType>::iterator List<DataType>::rear()const
{
	return iterator(_rear);
}

template<class DataType>
List<DataType>::List()
{
	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
}

template<class DataType>
List<DataType>::List(int n)
{
	if(n < 0)
	{
		cout << "Error in \'List<DataType>::List(int n)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}

	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	Node* p = head;
	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new Node;
		if(!(p->link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
	}
	_rear = p;
	length = n;
}

template<class DataType>
List<DataType>::List(int n, DataType element)
{
	if(n < 0)
	{
		cout << "Error in \'List<DataType>::List(int n, DataType)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}

	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	Node* p = head;
 	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new Node(element);
		if(!(p->link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
	}
	_rear = p;
	length = n;
}

template<class DataType>
List<DataType>::List(const List<DataType>& list)
{
	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	Node *p = head;
	Node *q = list.head;
	while(q->link)
	{
		p->link = new Node(q->link->data);
		if(!(p->link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		p = p->link;
		q = q->link;
	}
	_rear = p;
	length = list.length;
}

template<class DataType>
List<DataType>::~List()
{
	if(!head)
	{
		return;
	}
	
	while(head->link)
	{
		Node* p = head->link;
		head->link = p->link;
		delete p;
	}
	delete head;
	head = NULL;
}

template<class DataType>
List<DataType>& List<DataType>::operator =(const List<DataType>& list)
{
	clear();

	Node *p = head;
	Node *q = list.head;
	while(q->link)
	{
		p->link = new Node(q->link->data);
		if(!(p->link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		p = p->link;
		q = q->link;
	}
	length = list.length;
	_rear = p;

	return *this;
}

template<class DataType>
void List<DataType>::clear()
{
	while(head->link != NULL)
	{
		Node* p = head->link;
		head->link = p->link;
		delete p;
	}
	length = 0;
	_rear = NULL;
}

template<class DataType>
int List<DataType>::size()const
{
	return length;
}

template<class DataType>
bool List<DataType>::empty()const
{
	return (length == 0);
}

template<class DataType>
DataType& List<DataType>::operator [](int n)
{
	if(n < 0 || n >= length)
	{
		cout << "Error in \'DataType& List<DataType>::operator [](int n)\':" << endl
			 << "Index \'n\' is out of list range." << endl;
		exit(-1);
	}
	Node *p = head->link;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<class DataType>
DataType List<DataType>::operator [](int n)const
{
	if(n < 0 || n >= length)
	{
		cout << "Error in \'DataType List<DataType>::operator [](int n)const\':" << endl
			 << "Index \'n\' is out of list range." << endl;
		exit(-1);
	}
	Node *p = head->link;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<class DataType>
typename List<DataType>::iterator List<DataType>::find(const DataType& element)const
{
	List<DataType>::iterator it;
	for(it = begin(); it != end(); it++)
	{
		if(it->data == element)
		{
			break;
		}
	}
	return it;
}

template<class DataType>
typename List<DataType>::iterator List<DataType>::locate(int i)const
{
	List<DataType>::iterator it;
	for(it = begin(); it != end(); it++, i--)
	{
		if(i == 0)
		{
			break;
		}
	}
	return it;
}

template<class DataType>
int List<DataType>::locate(List<DataType>::iterator it)const
{
	int i = 0;
	for(List<DataType>::iterator subit = begin(); subit != end(); subit++, i++)
	{
		if(subit == it)
		{
			return i;
		}
	}
	return -1;
}

template<class DataType>
int List<DataType>::locate(DataType* ptr)const
{
	int i = 0;
	for(List<DataType>::iterator it = begin(); it != end(); it++, i++)
	{
		if(&(*it) == ptr)
		{
			return i;
		}
	}
	return -1;
}

template<class DataType>
bool List<DataType>::insert(int n, const DataType& element)
{
	if(n > length || n < 0)
	{
		cout << "Warning in bool List<DataType>::insert(int n, DataType)" << endl
			 << "\'n\' is not in [0, length]. Nothing has been done." << endl;
		return false;
	}
	Node *p = head;
	for(int i = 0; i < n; i++, p = p->link){}
	Node *q = p->link;
	p->link = new Node(element, q);
	if(!(p->link))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	if(n == length)
	{
		_rear = p->link;
	}
	length++;
	return true;
}

template<class DataType>
typename List<DataType>::iterator List<DataType>::erase(DataType* ptr)
{
	return erase(locate(ptr));
}

template<class DataType>
typename List<DataType>::iterator List<DataType>::erase(iterator it)
{
	for(Node* p = head; p != NULL; p = p->link)
	{
		if(it == p->link)
		{
			Node* q = p->link;
			p->link = q->link;
			delete q;
			return iterator(p->link);
		}
	}
	return end();
}

template<class DataType>
typename List<DataType>::iterator List<DataType>::erase(int n)
{
	if(n >= length || n < 0)
	{
		cout << "Error in bool List<DataType>::erase(int n)" << endl
			 << "\'n\' is not in [0, length-1]. Nothing has been done." << endl;
		exit(-1);
	}
	Node *p = head;
	for(int i = 0; i < n; i++){p = p->link;}
	Node *q = p->link;
	p->link = q->link;
	delete q;
	if(n == length-1)
	{
		_rear = p;
		if(_rear == head)
		{
			_rear = NULL;
		}
	}
	length--;
	return iterator(p->link);
}

template<class DataType>
void List<DataType>::push_back(const DataType& element)
{
	Node *p = head;
	while(p->link)
	{
		p = p->link;
	}
	p->link = new Node(element);
	if(!(p->link))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	_rear = p->link;
	length++;
}

template<class DataType>
void List<DataType>::push_front(const DataType& element)
{
	Node *p = head->link;
	head->link = new Node(element, p);
	if(!(head->link))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	if(length == 0)
	{
		_rear = head->link;
	}
	length++;
}

template<class DataType>
DataType List<DataType>::pop_back()
{
	if(length == 0)
	{
		cout << "Error in \'DataType List<DataType>::pop_back()\'" << endl
			 << "The list is empty." << endl;
		exit(-1);
	}

	Node *p = head;
	while(p->link->link)
	{
		p = p->link;
	}

	DataType element = p->link->data;
	delete p->link;
	p->link = NULL;
	_rear = p;
	if(_rear == head)
	{
		_rear = NULL;
	}
	length--;
	return element;
}

template<class DataType>
DataType List<DataType>::pop_front()
{
	if(length == 0)
	{
		cout << "Error: In \'DataType List<DataType>::pop_front()\' the list is empty." << endl;
		exit(-1);
	}

	Node *p = head->link;
	DataType element = p->data;
	head->link = p->link;
	delete p;
	if(head->link == NULL)
	{
		_rear = NULL;
	}
	length--;
	return element;
}

template<class DataType>
List<DataType> List<DataType>::cat(const List<DataType>& list)
{
	Node *p = head;
	while(p->link)
	{
		p = p->link;
	}

	Node *q = list.head->link;
	while(q)
	{
		p->link = new Node(q->data);
		if(!(p->link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		p = p->link;
		q = q->link;
	}
	_rear = p;
	length += list.length;
	return *this;
}

template<class DataType>
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

	Node *pi_last = head;
	for(int it = 0; it < i; it++){pi_last = pi_last->link;}

	Node *pj_last = head;
	for(int it = 0; it < j; it++){pj_last = pj_last->link;}

	Node *pi = pi_last->link;
	Node *pj = pj_last->link;
	if(!(pj->link))
	{
		_rear = pi;
	}

	Node *pj_next = pj->link;

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

template<class DataType>
ostream & operator <<(ostream& out, const List<DataType>& list)
{
	for(typename List<DataType>::iterator it = list.begin(); it != list.end(); it++)
	{
		out << (*it) << endl;
	}

	return out;
}

#endif