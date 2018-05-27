#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

template<typename DataType>
class QueueNode
{
public:
	DataType data;
	QueueNode *link = NULL;

public:
	QueueNode<DataType>(){}
	QueueNode<DataType>(DataType element)
	{
		data = element;
	}
	QueueNode<DataType>(DataType element, QueueNode *ptr)
	{
		data = element;
		link = ptr;
	}
};

template<typename DataType>
class Queue
{
private:
	Queue<DataType> *head = NULL;
	Queue<DataType> *rear = NULL;
	int length = 0;

public:
	Queue<DataType>();
	Queue<DataType>(const Queue<DataType>& queue);
	~Queue<DataType>();
	Queue<DataType>& operator =(const Queue<DataType>& queue);
	void clear();
	bool empty()const;
	int size()const;
	DataType front()const;
	DataType back()const;
	void push(DataType element);
	DataType pop();
}

Queue<DataType>::Queue()
{
	head = new QueueNode<DataType>;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	rear = head;
}

Queue<DataType>::Queue(const Queue<DataType>& queue)
{
	head = new QueueNode<DataType>;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	QueueNode<DataType> *p = head;
	QueueNode<DataType> *q = queue.head;
	while(q->link)
	{
		p->link = new QueueNode<DataType>(q->link->data);
		if(!(p->link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}

		p = p->link;
		q = q->link;
	}
	rear = p;
	length = queue.length;
}

Queue<DataType>::~Queue()
{
	while(head->link)
	{
		QueueNode<DataType> p = head->link;
		head->link = p->link;
		delete p;
	}
	length = 0;
	rear = head;
	delete head;
}

Queue<DataType>& Queue<DataType>::operator =(const Queue<DataType>& queue)
{
	if(head)
	{
		clear();
	}
	else
	{
		head = new QueueNode<DataType>;
		if(!head)
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
	}

	QueueNode<DataType> *p = head;
	QueueNode<DataType> *q = queue.head;
	while(q->link)
	{
		p->link = new QueueNode<DataType>(q->link->data);
		if(!(p->link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}

		p = p->link;
		q = q->link;
	}
	rear = p;
	length = queue.length;
}

void Queue<DataType>::clear()
{
	while(head->link)
	{
		QueueNode<DataType> p = head->link;
		head->link = p->link;
		delete p;
	}
	rear = head;
	length = 0;
}

bool Queue<DataType>::empty()const
{
	return (length == 0);
}

int Queue<DataType>::size()const
{
	return length;
}

DataType Queue<DataType>::front()const
{
	if(length == 0)
	{
		cout << "Error in \'DataType Queue<DataType>::front()const\'" << endl
			 << "Empty queue!" << endl;
		exit(-1);
	}
	return head->link->data;
}

DataType Queue<DataType>::back()const
{
	if(length == 0)
	{
		cout << "Error in \'DataType Queue<DataType>::back()const\'" << endl
			 << "Empty queue!" << endl;
		exit(-1);
	}
	return rear->data;
}

void Queue<DataType>::push(DataType element)
{
	rear->link = new QueueNode<DataType>(element);
	if(!(rear->link))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	rear = rear->link;
	length++;
}

DataType Queue<DataType>::pop()
{
	if(length == 0)
	{
		cout << "Error in \'DataType pop()\'" << endl
			 << "Empty queue!" << endl;
		exit(-1);
	}
	QueueNode<DataType> *p = head->link;
	DataType element = p->data;
	head->link = p->link;
	delete p;
	length--;
	if(length == 0)
	{
		rear = head;
	}
	return element;
}

#endif