#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <sstream>

using namespace std;

template<typename DataType>
class Queue
{
private:
	class Node
	{
	public:
		DataType data;
		Node *link = NULL;

	public:
		Node(){}
		Node(DataType element) : data(element){}
	};

	Node* new_Node();
	Node* new_Node(DataType element);

public:
	static string cout2string(const DataType& element)
	{
	    ostringstream oss;
	    oss << element;
	    return oss.str();
	}

private:
	Node *head = NULL; // Point to head node(not the first node)
	Node *rear = NULL; // Point to last node
	int length = 0;

public:
	Queue<DataType>();
	Queue<DataType>(const Queue<DataType>& queue);
	Queue<DataType>(const initializer_list<DataType>& list);
	Queue<DataType>(int n, const DataType& element);
	~Queue<DataType>();
	Queue<DataType>& operator =(const Queue<DataType>& queue);
	void clear();
	bool empty()const;
	int size()const;
	DataType front()const;
	DataType back()const;
	void push(DataType element);
	DataType pop();

	template<class ElemType>
	friend ostream& operator <<(ostream& out, const Queue<ElemType>& queue);
};

#include <queue.cpp>
#endif