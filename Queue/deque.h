// Completed at 2018/7/29 16:08

#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <sstream>

using namespace std;

template<typename DataType>
string cout2string(const DataType& element)
{
    ostringstream oss;
    oss << element;
    return oss.str();
}

template<typename DataType>
class Deque
{
	friend ostream & operator <<(ostream &o, const Deque<DataType>& deque)
	{
		Deque<DataType> deque1 = deque;
		Deque<DataType> deque2 = deque;

		o << endl << endl;

		if( deque1.empty() )
		{
			o << "| (void) |" << endl;
			return o;
		}

		DataType longest_element = deque1.pop_front();
		string longest_string = cout2string(longest_element);
		while( !deque1.empty() )
		{
			DataType temp_element = deque1.pop_front();
			string temp_string = cout2string(temp_element);
			if( temp_string.size() > longest_string.size() )
			{
				longest_string = temp_string;
			}
		}

		while( !deque2.empty() )
		{
			DataType temp_element = deque2.pop_front();
			o << "| " << temp_element << " ";
			unsigned i = 0;
			string temp_string = cout2string(temp_element);

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
	DataType front()const;
	DataType back()const;
	void push_front(DataType element);
	void push_back(DataType element);
	DataType pop_back();
	DataType pop_front();
};

template<typename DataType>
typename Deque<DataType>::Node* Deque<DataType>::creat_node()
{
	Deque<DataType>::Node* ptr_node = new Deque<DataType>::Node;
	if(!ptr_node)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	return ptr_node;
}

template<typename DataType>
typename Deque<DataType>::Node* Deque<DataType>::creat_node(DataType element)
{
	Deque<DataType>::Node* ptr_node = new Deque<DataType>::Node(element);
	if(!ptr_node)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	return ptr_node;
}

template<typename DataType>
Deque<DataType>::Deque()
{
	head = creat_node();
	rear = head;
}

template<typename DataType>
Deque<DataType>::Deque(const Deque<DataType>& deque)
{
	head = creat_node();

	Deque<DataType>::Node *p = head;
	Deque<DataType>::Node *q = deque.head;
	while(q->link)
	{
		p->link = creat_node(q->link->data);
		p = p->link;
		q = q->link;
	}
	rear = p;
	length = deque.length;
}

template<typename DataType>
Deque<DataType>::Deque(const initializer_list<DataType>& list)
{
	head = creat_node();

	Deque<DataType>::Node *p = head;
	for(typename initializer_list<DataType>::iterator it = list.begin(); it != list.end(); it++, p = p->link)
	{
		p->link = creat_node(*it);
		length++;
	}
	rear = p;
}


template<typename DataType>
Deque<DataType>::Deque(int n, const DataType& element)
{
	head = creat_node();

	Deque<DataType>::Node *p = head;
	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = creat_node(element);
	}
	rear = p;
	length = n;
}

template<typename DataType>
Deque<DataType>::~Deque()
{
	while(head->link)
	{
		Deque<DataType>::Node* p = head->link;
		head->link = p->link;
		delete p;
	}
	
	delete head;

	head = NULL;
	rear = NULL;
	length = 0;
}

template<typename DataType>
Deque<DataType>& Deque<DataType>::operator =(const Deque<DataType>& deque)
{
	if(length)
	{
		clear();
	}
	
	Deque<DataType>::Node *p = head;
	Deque<DataType>::Node *q = deque.head;
	while(q->link)
	{
		p->link = creat_node(q->link->data);
		p = p->link;
		q = q->link;
	}
	rear = p;
	length = deque.length;

	return *this;
}

template<typename DataType>
void Deque<DataType>::clear()
{
	while(head->link)
	{
		Deque<DataType>::Node* p = head->link;
		head->link = p->link;
		delete p;
	}
	rear = head;
	length = 0;
}

template<typename DataType>
bool Deque<DataType>::empty()const
{
	return (length == 0);
}

template<typename DataType>
int Deque<DataType>::size()const
{
	return length;
}

template<typename DataType>
DataType Deque<DataType>::front()const
{
	if(empty())
	{
		cout << "Error in \'DataType Deque<DataType>::front()const\'" << endl
			 << "Empty deque!" << endl;
		exit(-1);
	}
	return head->link->data;
}

template<typename DataType>
DataType Deque<DataType>::back()const
{
	if(empty())
	{
		cout << "Error in \'DataType Deque<DataType>::back()const\'" << endl
			 << "Empty deque!" << endl;
		exit(-1);
	}
	return rear->data;
}

template<typename DataType>
void Deque<DataType>::push_back(DataType element)
{
	rear->link = creat_node(element);
	rear = rear->link;
	length++;
}

template<typename DataType>
void Deque<DataType>::push_front(DataType element)
{
	Deque<DataType>::Node *p = head->link;
	head->link = creat_node(element);
	head->link->link = p;
	if(length == 1)
	{
		rear = head->link;
	}
	length++;
}

template<typename DataType>
DataType Deque<DataType>::pop_back()
{
	if(length == 0)
	{
		cout << "Error in \'DataType Deque<DataType>::pop_back()\'" << endl
			 << "Empty deque!" << endl;
		exit(-1);
	}

	Deque<DataType>::Node *rear_left = head;
	while(rear_left->link->link)
	{
		rear_left = rear_left->link;
	}
	DataType element = rear->data;
	delete rear;
	rear = rear_left;
	length--;
	return element;
}

template<typename DataType>
DataType Deque<DataType>::pop_front()
{
	if(length == 0)
	{
		cout << "Error in \'DataType Deque<DataType>::pop_front()\'" << endl
			 << "Empty deque!" << endl;
		exit(-1);
	}

	Deque<DataType>::Node *p = head->link;
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