#ifndef CIRCLIST_H
#define CIRCLIST_H

#include <iostream>

using namespace std;

template<typename DataType>
class CircList
{
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
	Node* new_Node()const;
	Node* new_Node(DataType element)const;
	Node* new_Node(DataType element, Node* ptr)const;
	Node* new_Node(Node* node)const;
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
	CircList<DataType>(){};
	CircList<DataType>(int n);
	CircList<DataType>(int n, DataType element);
	CircList<DataType>(const CircList<DataType>& list);
	~CircList<DataType>();
	void clear();
	
	int size()const;
	bool empty()const;
	int locate(DataType element)const;
	void insert(int n, DataType element);
	bool erase(int n);
	void push_back(DataType element);
	void push_front(DataType element);
	DataType pop_back();
	DataType pop_front();
	bool swap(int i, int j);
	CircList<DataType> cat(const CircList<DataType>& list);
	iterator begin()const{return iterator(first);}
	iterator last()const{return iterator(rear);}

	DataType& operator [](int i);
	DataType operator [](int i)const;
	CircList<DataType>& operator =(const CircList<DataType>& list);

	template<class ElemType>
	friend ostream & operator <<(ostream& out, const CircList<ElemType>& list);
};

#include <circlist.cpp>
#endif