#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>

using namespace std;

template<typename DataType>
class Deque
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
	Node* new_Node(const DataType& element);

private:
	Node *head = NULL; // Point to head node(not the first node)
	Node *rear = NULL; // Point to last node
	int length = 0;

public:
	Deque<DataType>();
	Deque<DataType>(const Deque<DataType>& deque);
	Deque<DataType>(const initializer_list<DataType>& list);
	Deque<DataType>(int n, const DataType& element);
	~Deque<DataType>();
	Deque<DataType>& operator =(const Deque<DataType>& deque);
	void clear();
	bool empty()const;
	int size()const;
	DataType& front()const;
	DataType& back()const;
	void push_front(const DataType& element);
	void push_back(const DataType& element);
	DataType pop_back();
	DataType pop_front();

	template<class ElemType>
	friend ostream& operator <<(ostream& out, const Deque<ElemType>& deque);
};

#include <deque.cpp>
#endif