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

protected:
	Node *head = NULL; // point to head node (not the first node, before first node)
	Node *_rear = NULL; // point to last node
	int length = 0;

public:
	List<DataType>();
	List<DataType>(int n);
	List<DataType>(int n, DataType element);
	List<DataType>(const List<DataType>& list);
	~List<DataType>();
	List<DataType>& operator =(const List<DataType>& list);
	void clear();
	int size()const;
	bool empty()const;
	DataType& operator [](int i);
	DataType operator [](int i)const;
	List<DataType>::iterator find(const DataType& element)const;
	List<DataType>::iterator locate(int i)const;
	int locate(List<DataType>::iterator it)const;
	int locate(DataType* ptr)const;
	bool insert(int i, const DataType& element);
	iterator erase(int i);
	iterator erase(DataType* ptr);
	iterator erase(iterator it);
	void push_back(const DataType& element);
	void push_front(const DataType& element);
	DataType pop_back();
	DataType pop_front();
	bool swap(int i, int j);
	List<DataType> cat(const List<DataType>& list);
	iterator begin()const;
	iterator end()const;
	iterator rear()const;

	template<class ElemType>
	friend ostream & operator <<(ostream& out, const List<ElemType>& list);
};

#include <list.cpp>
#endif