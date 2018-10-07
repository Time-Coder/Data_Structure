#ifdef DEQUE_H

template<typename DataType>
typename Deque<DataType>::Node* Deque<DataType>::new_Node()
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
typename Deque<DataType>::Node* Deque<DataType>::new_Node(const DataType& element)
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
	head = new_Node();
	rear = head;
}

template<typename DataType>
Deque<DataType>::Deque(const Deque<DataType>& deque)
{
	head = new_Node();

	Deque<DataType>::Node *p = head;
	Deque<DataType>::Node *q = deque.head;
	while(q->link)
	{
		p->link = new_Node(q->link->data);
		p = p->link;
		q = q->link;
	}
	rear = p;
	length = deque.length;
}

template<typename DataType>
Deque<DataType>::Deque(const initializer_list<DataType>& list)
{
	head = new_Node();

	Deque<DataType>::Node *p = head;
	for(typename initializer_list<DataType>::iterator it = list.begin(); it != list.end(); it++, p = p->link)
	{
		p->link = new_Node(*it);
		length++;
	}
	rear = p;
}


template<typename DataType>
Deque<DataType>::Deque(int n, const DataType& element)
{
	head = new_Node();

	Deque<DataType>::Node *p = head;
	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new_Node(element);
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
		p->link = new_Node(q->link->data);
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
DataType& Deque<DataType>::front()const
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
DataType& Deque<DataType>::back()const
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
void Deque<DataType>::push_back(const DataType& element)
{
	rear->link = new_Node(element);
	rear = rear->link;
	length++;
}

template<typename DataType>
void Deque<DataType>::push_front(const DataType& element)
{
	Deque<DataType>::Node *p = head->link;
	head->link = new_Node(element);
	head->link->link = p;
	length++;
	if(length == 1)
	{
		rear = head->link;
	}
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
	rear->link = NULL;
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

template<typename DataType>
ostream& operator <<(ostream& out, const Deque<DataType>& deque_origine)
{
	Deque<DataType> deque = deque_origine;

	if(deque.empty())
	{
		return out;
	}

	DataType x = deque.pop_front();
	out << x;
	while(!deque.empty())
	{
		x = deque.pop_front();
		out << ", " << x;
	}

	return out;
}

#endif