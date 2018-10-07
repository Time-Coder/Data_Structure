#ifndef SORTLIST_H
#define SORTLIST_H

#include <iostream>

using namespace std;

template<typename DataType>
class SortList
{
private:
	class Node
	{
	public:
		DataType  _data;
		Node* _next = NULL;

	public:
		Node(){};
		Node(const DataType& data, Node* next) : _data(data), _next(next) {}
	};

	static Node* new_Node();
	static Node* new_Node(const DataType& data, Node* next = NULL);

public:
	class const_iterator
	{
	public:
	    Node* _ptr = NULL;

	public:
		const_iterator() {}
		const_iterator(Node* ptr) : _ptr(ptr) {}
		const_iterator& operator =(const const_iterator& iter) {_ptr = iter._ptr; return *this;}
		bool operator !=(const const_iterator& iter)const {return _ptr != iter._ptr;}
		bool operator ==(const const_iterator& iter)const {return _ptr == iter._ptr;}
	    const_iterator& operator ++();
	    const_iterator operator ++(int);
	    DataType operator *()const;
	    bool empty()const;
	};

private:
	Node* head;
	
public:
	SortList<DataType>();
	SortList<DataType>(const SortList<DataType>& X);
	~SortList<DataType>();
	SortList<DataType>& operator =(const SortList<DataType>& X);
	bool operator ==(const SortList<DataType>& X)const;
	bool operator !=(const SortList<DataType>& X)const;
	void clear();
	const_iterator begin()const;
	const_iterator end()const;
	void insert(const DataType& x);
	void erase(const const_iterator& it);
	void erase(const int& i);
	int  length()const;
	bool empty()const;
	const_iterator find(const DataType& x)const;
	const_iterator locate(const int& i)const;
	int locate(const const_iterator& it)const;
	SortList<DataType> merge(const SortList<DataType>& X);

	template<class ElemType>
	friend ostream & operator <<(ostream &o, const SortList<ElemType>& X);
};

#include <sortlist.cpp>
#endif