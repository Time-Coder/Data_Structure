#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

template<typename DataType>
class Stack
{
public:
	class Node
	{
	public:
		DataType _data;
		Node *_next = NULL;

	public:
		Node(){};
		Node(const DataType& data) : _data(data) {}
		Node(const DataType& data, Node *next) : _data(data), _next(next) {}
	};	

public:
	static string cout2string(const DataType& element)
	{
	    ostringstream oss;
	    oss << element;
	    return oss.str();
	}

private:
	Node *head;
	int length = 0;

public:
	Stack<DataType>();
	Stack<DataType>(const Stack<DataType>& stack);
	~Stack<DataType>();
	Stack<DataType>& operator =(const Stack<DataType>& stack);
	void clear();
	void push(const DataType& element);
	DataType pop();
	DataType& top();
	bool empty()const;
	int size()const;
	Stack<DataType>& inverse();

	template<class ElemType>
	friend ostream& operator <<(ostream& out, const Stack<ElemType>& stack);
};

#include <stack.cpp>
#endif