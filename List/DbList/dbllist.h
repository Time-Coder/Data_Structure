#ifndef DBLLIST_H
#define DBLLIST_H

#include <iostream>
#include <iterator>

using namespace std;

template<typename DataType>
class DblList
{
private:
	class Node
	{
	public:
		DataType _data;
		Node *_prev = NULL;
		Node *_next = NULL;

	public:
		Node() {}
		Node(DataType element) : _data(element) {}
		Node(Node *prev, Node *next) : _prev(prev), _next(next) {}
		Node(const DataType& data, Node *prev, Node *next) :
		_data(data), _prev(prev), _next(next) {}
	};

	class iterator
	{
	private:
		Node* _ptr = NULL;

	public:
		iterator() {}
		iterator(Node *ptr) : _ptr(ptr) {}
		~iterator() {_ptr = NULL;}

	    iterator& operator =(const iterator& it) {_ptr = it._ptr;}
	    bool operator !=(const iterator& it) {return (_ptr != it._ptr);}
	    bool operator ==(const iterator& it) {return (_ptr == it._ptr);}
	    iterator& operator ++();
	    iterator operator ++(int);
	    iterator& operator --();
	    iterator operator --(int);
	    DataType& operator *() {return _ptr->_data;}
	    DataType* operator ->() {return &(_ptr->_data);}
	    DataType* ptr() {return &(_ptr->_data);} 
	};

private:
	Node *head = NULL;
	Node *tail = NULL;
	int length = 0;

public:
	DblList<DataType>();
	DblList<DataType>(int n);
	DblList<DataType>(int n, DataType element);
	DblList<DataType>(const DblList<DataType>& list);
	~DblList<DataType>();
	
	void clear();
	int size()const;
	bool empty()const;
	int locate(DataType element)const;
	bool insert(int i, DataType element);
	bool erase(int i);
	void push_back(DataType element);
	void push_front(DataType element);
	DataType pop_back();
	DataType pop_front();
	bool swap(int i, int j);
	DblList<DataType> cat(const DblList<DataType>& list);
	iterator begin()const{return iterator(head->_next);};
	iterator end()const{return iterator(tail);};

	DblList<DataType>& operator =(const DblList<DataType>& list);
	DataType& operator [](int i);
	DataType operator [](int i)const;

	template<class ElemType>
	friend ostream & operator <<(ostream& out, const DblList<ElemType>& list);
};

#include <dbllist.cpp>
#endif