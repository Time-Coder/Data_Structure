#ifdef QUEUE_H

template<typename DataType>
typename Queue<DataType>::Node* Queue<DataType>::new_Node()
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
typename Queue<DataType>::Node* Queue<DataType>::new_Node(DataType element)
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
	head = new_Node();
	rear = head;
}

template<typename DataType>
Queue<DataType>::Queue(const Queue<DataType>& queue)
{
	head = new_Node();

	Queue<DataType>::Node *p = head;
	Queue<DataType>::Node *q = queue.head;
	while(q->link)
	{
		p->link = new_Node(q->link->data);
		p = p->link;
		q = q->link;
	}
	rear = p;
	length = queue.length;
}

template<typename DataType>
Queue<DataType>::Queue(const initializer_list<DataType>& list)
{
	head = new_Node();

	Queue<DataType>::Node *p = head;
	for(typename initializer_list<DataType>::iterator it = list.begin(); it != list.end(); it++, p = p->link)
	{
		p->link = new_Node(*it);
		length++;
	}
	rear = p;
}

template<typename DataType>
Queue<DataType>::Queue(int n, const DataType& element)
{
	head = new_Node();

	Queue<DataType>::Node *p = head;
	for(int i = 0; i < n; i++, p = p->link)
	{
		p->link = new_Node(element);
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
		p->link = new_Node(q->link->data);
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
	rear->link = new_Node(element);
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

template<typename DataType>
ostream& operator <<(ostream& out, const Queue<DataType>& queue_origine)
{
	Queue<DataType> queue = queue_origine;

	if(queue.empty())
	{
		return out;
	}

	DataType x = queue.pop();
	out << x;
	while(!queue.empty())
	{
		x = queue.pop();
		out << ", " << x;
	}
	return out;
}

#endif