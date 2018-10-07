#ifdef CIRCLIST_H

template<typename DataType>
void CircList<DataType>::memory_error(CircList<DataType>::Node* p)const
{
	if(!p)
	{
		cerr << "Error when creating list node." << endl
			 << "Failed to allocate memory!" << endl;
		exit(-1);
	}
}

template<typename DataType>
typename CircList<DataType>::Node* CircList<DataType>::new_Node()const
{
	CircList<DataType>::Node* p = new CircList<DataType>::Node;
	memory_error(p);

	return p;
}

template<typename DataType>
typename CircList<DataType>::Node* CircList<DataType>::new_Node(DataType element)const
{
	CircList<DataType>::Node* p = new CircList<DataType>::Node(element);
	memory_error(p);

	return p;
}

template<typename DataType>
typename CircList<DataType>::Node* CircList<DataType>::new_Node(DataType element, CircList<DataType>::Node* ptr)const
{
	CircList<DataType>::Node* p = new CircList<DataType>::Node(element, ptr);
	memory_error(p);

	return p;
}

template<typename DataType>
typename CircList<DataType>::Node* CircList<DataType>::new_Node(CircList<DataType>::Node *node)const
{
	CircList<DataType>::Node* p = new CircList<DataType>::Node(node->data);
	memory_error(p);

	return p;
}

template<typename DataType>
CircList<DataType>::CircList(int n)
{
	if(n < 0)
	{
		cout << "Error in \'CircList<DataType>::CircList(int n)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}
	if(n == 0)
	{
		return;
	}

	first = new_Node();
	CircList<DataType>::Node* p = first;
	for(int i = 1; i < n; i++)
	{
		p->link = new_Node();
		p = p->link;
	}
	p->link = first;
	rear = p;
	length = n;
}

template<typename DataType>
CircList<DataType>::CircList(int n, DataType element)
{
	if(n < 0)
	{
		cout << "Error in \'CircList<DataType>::CircList(int n, DataType element)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}
	if(n == 0)
	{
		return;
	}

	first = new_Node(element);
	CircList<DataType>::Node* p = first;
	for(int i = 1; i < n; i++)
	{
		p->link = new_Node(element);
		p = p->link;
	}
	p->link = first;
	rear = p;
	length = n;
}

template<typename DataType>
CircList<DataType>::CircList(const CircList<DataType>& list)
{
	if(list.length == 0)
	{
		return;
	}
	
	first = new_Node(list.first);
	CircList<DataType>::Node *p = first;
	CircList<DataType>::Node *q = list.first;
	for(int i = 1; i < list.length; i++)
	{
		p->link = new_Node(q->link);
		p = p->link;
		q = q->link;
	}
	p->link = first;
	rear = p;
	length = list.length;
}

template<typename DataType>
CircList<DataType>::~CircList()
{
	if(length != 0)
	{
		while(first->link != first)
		{
			CircList<DataType>::Node *p = first->link;
			first->link = p->link;
			delete p;
		}
		delete first;
		length = 0;
	}
}

template<typename DataType>
void CircList<DataType>::clear()
{
	if(length != 0)
	{
		while(first->link != first)
		{
			CircList<DataType>::Node *p = first->link;
			first->link = p->link;
			delete p;
		}
		delete first;

		first = NULL;
		rear = NULL;
		length = 0;
	}
}

template<typename DataType>
CircList<DataType>& CircList<DataType>::operator =(const CircList<DataType>& list)
{
	clear();
	if(list.length == 0)
	{
		return *this;
	}
	
	first = new_Node(list.first);
	CircList<DataType>::Node *p = first;
	CircList<DataType>::Node *q = list.first;
	for(int i = 1; i < list.length; i++)
	{
		p->link = new_Node(q->link);
		p = p->link;
		q = q->link;
	}
	p->link = first;
	rear = p;
	length = list.length;

	return *this;
}

template<typename DataType>
int CircList<DataType>::size()const
{
	return length;
}

template<typename DataType>
bool CircList<DataType>::empty()const
{
	return (length == 0);
}

template<typename DataType>
DataType& CircList<DataType>::operator [](int n)
{
	if(length == 0)
	{
		cout << "Error in \'DataType& CircList<DataType>::operator [](int n)\':" << endl
			 << "Empty list." << endl;
		exit(-1);
	}
	n = n % length;
	if(n < 0)
	{
		n += length;
	}
	
	CircList<DataType>::Node *p = first;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<typename DataType>
DataType CircList<DataType>::operator [](int n)const
{
	if(length == 0)
	{
		cout << "Error in \'DataType CircList<DataType>::operator [](int n)const\':" << endl
			 << "Empty list." << endl;
		exit(-1);
	}
	n = n % length;
	if(n < 0)
	{
		n += length;
	}
	CircList<DataType> *p = first;
	for(int i = 0; i < n; i++, p = p->link){}
	return p->data;
}

template<typename DataType>
int CircList<DataType>::locate(DataType element)const
{
	if(length == 0)
	{
		return -1;
	}

	CircList<DataType>::Node *p = first;
	for(int i = 0; i < length; i++, p = p->link)
	{
		if(p->data == element)
		{
			return i;
		}
	}
	return -1;
}

template<typename DataType>
void CircList<DataType>::insert(int n, DataType element)
{
	if(length == 0)
	{
		first = new_Node(element);
		first->link = first;
		rear = first;
		length = 1;
		return;
	}

	int ni = n % length;
	if(ni < 0)
	{
		ni += length;
	}

	if(n == 0)
	{
		rear->link = new_Node(element, first);
		first = rear->link;
	}
	else if(ni == 0)
	{
		rear->link = new_Node(element, first);
		rear = rear->link;
	}
	else
	{
		CircList<DataType>::Node *p = first;
		for(int i = 0; i < ni-1; i++, p = p->link){}
		p->link = new_Node(element, p->link);
	}
	length++;
}

template<typename DataType>
bool CircList<DataType>::erase(int n)
{
	if(length == 0)
	{
		cout << "Warning in bool List<DataType>::erase(int):" << endl
			 << "Empty list. Nothing has been done." << endl;
		return false;
	}
	else if(length == 1)
	{
		delete first;
		first = NULL;
		rear = NULL;
		length = 0;
		return true;
	}

	n = n % length;
	if(n < 0)
	{
		n += length;
	}

	CircList<DataType>::Node *p = first;
	for(int i = 0; i < n-1; i++, p = p->link){}
	CircList<DataType>::Node *q = p->link;
	p->link = q->link;
	if(q == first)
	{
		first = q->link;
	}
	else if(q == rear)
	{
		rear = p;
	}
	delete q;
	length--;
	return true;
}

template<typename DataType>
void CircList<DataType>::push_back(DataType element)
{
	if(length == 0)
	{
		first = new_Node(element);
		first->link = first;
		rear = first;
		length = 1;
		return;
	}

	rear->link = new_Node(element, first);
	rear = rear->link;
	length++;
}

template<typename DataType>
void CircList<DataType>::push_front(DataType element)
{
	if(length == 0)
	{
		first = new_Node(element);
		first->link = first;
		rear = first;
		length = 1;
		return;
	}

	rear->link = new_Node(element, first);
	first = rear->link;
	length++;
}

template<typename DataType>
DataType CircList<DataType>::pop_back()
{
	if(length == 0)
	{
		cout << "Error in \'DataType CircList<DataType>::pop_back()\'." << endl
			 << "Empty list." << endl;
		exit(-1);
	}
	if(length == 1)
	{
		DataType element = rear->data;
		delete first;
		first = NULL;
		rear = NULL;
		length = 0;
		return element;
	}

	CircList<DataType>::Node *p = first;
	for(int i = 0; i < length-2; i++, p = p->link){}

	DataType element = rear->data;
	p->link = first;
	delete rear;
	rear = p;
	length--;
	return element;
}

template<typename DataType>
DataType CircList<DataType>::pop_front()
{
	if(length == 0)
	{
		cout << "Error in \'DataType CircList<DataType>::pop_front()\'" << endl
			 << "Empty list." << endl;
		exit(-1);
	}
	if(length == 1)
	{
		DataType element = first->data;
		delete first;
		first = NULL;
		rear = NULL;
		length = 0;
		return element;
	}

	DataType element = first->data;
	rear->link = first->link;
	delete first;
	first = rear->link;
	length--;
	return element;
}

template<typename DataType>
bool CircList<DataType>::swap(int i, int j)
{
	if(length == 0)
	{
		cout << "Warning in bool List<DataType>::swap(int i, int j)" << endl
			 << "Empty list. Nothing has been done." << endl;
		return false;
	}

	i = i % length;
	j = j % length;
	if(i < 0)
	{
		i += length;
	}
	if(j < 0)
	{
		j += length;
	}

	if(i == j)
	{
		cout << "Warning in bool List<DataType>::swap(int i, int j)" << endl
			 << "Try to swap the same position. Nothing has been done." << endl;
		return false;
	}

	if(i > j)
	{
		std::swap(i, j);
	}

	CircList<DataType>::Node *pi_last;
	if(i == 0)
	{
		pi_last = rear;
	}
	else
	{
		pi_last = first;
		for(int it = 0; it < i-1; it++, pi_last = pi_last->link){}
	}
	CircList<DataType>::Node *pj_last = first;
	for(int it = 0; it < j-1; it++, pj_last = pj_last->link){}

	CircList<DataType>::Node *pi = pi_last->link;
	CircList<DataType>::Node *pj = pj_last->link;
	CircList<DataType>::Node *pi_next = pi->link;
	CircList<DataType>::Node *pj_next = pj->link;

	int situation = 0;
	if(first == pi)
	{
		first = pj;
		situation++;
	}

	if(rear == pj)
	{
		rear = pi;
		situation++;
	}

	if(situation == 2)
	{
		pj_last->link = pi;
		pi->link = pj;
		pj->link = pi_next;
		return true;
	}

	if(j-i > 1)
	{
		pi_last->link = pj;
		pj->link = pi->link;
		pj_last->link = pi;
		pi->link = pj_next;
		return true;
	}
	else
	{
		pi_last->link = pj;
		pj->link = pi;
		pi->link = pj_next;
		return true;
	}
}

template<typename DataType>
CircList<DataType> CircList<DataType>::cat(const CircList<DataType>& list)
{
	if(length == 0)
	{
		*this = list;
		return *this;
	}

	CircList<DataType>::Node *p = list.first;
	for(int i = 0; i < list.length; i++)
	{
		rear->link = new_Node(p);
		rear = rear->link;
		p = p->link;
	}
	rear->link = first;
	length += list.length;
	return *this;
}

template<class DataType>
ostream & operator <<(ostream& out, const CircList<DataType>& list)
{
	if(list.empty())
	{
		return out;
	}

	int n = list.size();
	typename CircList<DataType>::iterator it = list.begin();
	out << (*it);
	it++;
	for(int i = 1; i < n; i++, it++)
	{
		out << ", " << (*it);
	}

	return out;
}

#endif