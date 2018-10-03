// Completed at 2018/7/29 15:29 by Bing-Hui WANG

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <sstream>

using namespace std;

template<typename DataType>
class Queue
{
	friend ostream & operator <<(ostream &o, const Queue<DataType>& queue)
	{
		Queue<DataType> queue1;
		Queue<DataType> queue2;
		queue1 = queue;
		queue2 = queue;

		o << endl << endl;

		if( queue1.empty() )
		{
			o << "| (void) |" << endl;
			return o;
		}

		DataType longest_element = queue1.pop();
		string longest_string = Queue::cout2string(longest_element);
		while( !queue1.empty() )
		{
			DataType temp_element = queue1.pop();
			string temp_string = Queue::cout2string(temp_element);
			if( temp_string.size() > longest_string.size() )
			{
				longest_string = temp_string;
			}
		}

		while( !queue2.empty() )
		{
			DataType temp_element = queue2.pop();
			o << "| " << temp_element << " ";
			unsigned i = 0;
			string temp_string = Queue::cout2string(temp_element);

			while(i != longest_string.size()-temp_string.size())
			{
				o << " ";
				i++;
			}

			o << "|" << endl;
		}

		return o;
	}

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

	Node* creat_node();
	Node* creat_node(DataType element);
	
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
};

template<typename DataType>
typename Queue<DataType>::Node* Queue<DataType>::creat_node()
{
	Queue<DataType>::Node* ptr_node = new Queue<DataType>::Node;
	if(!ptr_node)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	return ptr_node;
}

template<typename DataType>
typename Queue<DataType>::Node* Queue<DataType>::creat_node(DataType element)
{
	Queue<DataType>::Node* ptr_node = new Queue<DataType>::Node(element);
	if(!ptr_node)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	return ptr_node;
}

template<typename DataType>
Queue<DataType>::Queue()
{
	head = creat_node();
	rear = head;
}

template<typename DataType>
Queue<DataType>::Queue(const Queue<DataType>& queue)
{
	head = creat_node();

	Queue<DataType>::Node *p = head;
	Queue<DataType>::Node *q = queue.head;
	while(q->link)
	{
		p->link = creat_node(q->link->data);
		p = p->link;
		q = q->link;
	}
	rear = p;
	length = queue.length;
}

template<typename DataType>
Queue<DataType>::Queue(const initializer_list<DataType>& list)
{
	head = creat_node();

	Queue<DataType>::Node *p = head;
	for(typename initializer_list<DataType>::iterator it = list.begin(); it != list.end(); it++, p = p->link)
	{
		p->link = creat_node(*it);
		length++;
	}
	rear = p;
}

template<typename DataType>
Queue<DataType>::Queue(int n, const DataType& element)
{
	head = creat_node();

	Queue<DataType>::Node *p = head;
	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = creat_node(element);
	}
	rear = p;
	length = n;
}

template<typename DataType>
Queue<DataType>::~Queue()
{
	while(head->link)
	{
		Queue<DataType>::Node* p = head->link;
		head->link = p->link;
		delete p;
	}
	
	delete head;

	head = NULL;
	rear = NULL;
	length = 0;
}

template<typename DataType>
Queue<DataType>& Queue<DataType>::operator =(const Queue<DataType>& queue)
{
	if(length)
	{
		clear();
	}
	
	Queue<DataType>::Node *p = head;
	Queue<DataType>::Node *q = queue.head;
	while(q->link)
	{
		p->link = creat_node(q->link->data);
		p = p->link;
		q = q->link;
	}
	rear = p;
	length = queue.length;

	return *this;
}

template<typename DataType>
void Queue<DataType>::clear()
{
	while(head->link)
	{
		Queue<DataType>::Node* p = head->link;
		head->link = p->link;
		delete p;
	}
	rear = head;
	length = 0;
}

template<typename DataType>
bool Queue<DataType>::empty()const
{
	return (length == 0);
}

template<typename DataType>
int Queue<DataType>::size()const
{
	return length;
}

template<typename DataType>
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

template<typename DataType>
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

template<typename DataType>
void Queue<DataType>::push(DataType element)
{
	rear->link = creat_node(element);
	rear = rear->link;
	length++;
}

template<typename DataType>
DataType Queue<DataType>::pop()
{
	if(length == 0)
	{
		cout << "Error in \'DataType Queue<DataType>::pop()\'" << endl
			 << "Empty queue!" << endl;
		exit(-1);
	}

	Queue<DataType>::Node *p = head->link;
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