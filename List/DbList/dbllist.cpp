#ifdef DBLLIST_H

template<typename DataType>
typename DblList<DataType>::iterator& DblList<DataType>::iterator::operator ++()
{
	_ptr = _ptr->_next;
    return *this;
}

template<typename DataType>
typename DblList<DataType>::iterator DblList<DataType>::iterator::operator ++(int)
{
    iterator temp = *this;
    _ptr = _ptr->_next;
    return temp;
}

template<typename DataType>
typename DblList<DataType>::iterator& DblList<DataType>::iterator::operator --()
{
    _ptr = _ptr->_prev;
    return *this;
}

template<typename DataType>
typename DblList<DataType>::iterator DblList<DataType>::iterator::operator --(int)
{
    iterator temp = *this;
    _ptr = _ptr->_prev;
    return temp;
}

template<typename DataType>
DblList<DataType>::DblList()
{
	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	tail = new Node(head, NULL);
	if(!tail)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	head->_next = tail;
}

template<typename DataType>
DblList<DataType>::DblList(int n)
{
	if(n < 0)
	{
		cout << "Error in \'DblList<DataType>::DblList(int n)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}

	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	tail = new Node;
	if(!tail)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	Node* p = head;
	for(int i = 0; i < n; i++, p = p->_next)
	{
		p->_next = new Node(p, NULL);
		if(!(p->_next))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
	}
	p->_next = tail;
	tail->_prev = p;
	length = n;
}

template<typename DataType>
DblList<DataType>::DblList(int n, DataType element)
{
	if(n < 0)
	{
		cout << "Error in \'DblList<DataType>::DblList(int n, DataType)\'" << endl
			 << "\'n\' must be positive." << endl;
		exit(-1);
	}

	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	tail = new Node;
	if(!tail)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	Node* p = head;
	for(int i = 0; i < n; i++, p = p->_next)
	{
		p->_next = new Node(element, p, NULL);
		if(!(p->_next))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
	}
	p->_next = tail;
	tail->_prev = p;
	length = n;
}

template<typename DataType>
DblList<DataType>::DblList(const DblList<DataType>& list)
{
	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	tail = new Node;
	if(!tail)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	Node *p = head;
	Node *q = list.head;
	while(q->_next != list.tail)
	{
		p->_next = new Node(q->_next->data, p, NULL);
		if(!(p->_next))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		p = p->_next;
		q = q->_next;
	}
	p->_next = tail;
	tail->_prev = p;
	length = list.length;
}

template<typename DataType>
DblList<DataType>::~DblList()
{
	while(head->_next != tail)
	{
		Node* p = head->_next;
		head->_next = p->_next;
		delete p;
	}
	length = 0;
	delete head;
	delete tail;
}

template<typename DataType>
DblList<DataType>& DblList<DataType>::operator =(const DblList<DataType>& list)
{
	clear();
	Node *p = head;
	Node *q = list.head;
	while(q->_next != list.tail)
	{
		p->_next = new Node(q->_next->data, p, NULL);
		if(!(p->_next))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		p = p->_next;
		q = q->_next;
	}
	p->_next = tail;
	tail->_prev = p;
	length = list.length;

	return *this;
}

template<typename DataType>
void DblList<DataType>::clear()
{
	while(head->_next != tail)
	{
		Node* p = head->_next;
		head->_next = p->_next;
		delete p;
	}
	length = 0;
}

template<typename DataType>
int DblList<DataType>::size()const
{
	return length;
}

template<typename DataType>
bool DblList<DataType>::empty()const
{
	return (length == 0);
}

template<typename DataType>
DataType& DblList<DataType>::operator [](int n)
{
	if(n < 0 || n >= length)
	{
		cout << "Error in \'DataType& DblList<DataType>::operator [](int n)\':" << endl
			 << "\'n\' is out of list range." << endl;
		exit(-1);
	}

	Node *p = head->_next;
	for(int i = 0; i < n; i++, p = p->_next){}
	return p->data;
}

template<typename DataType>
DataType DblList<DataType>::operator [](int n)const
{
	if(n < 0 || n >= length)
	{
		cout << "Error in \'DataType DblList<DataType>::operator [](int n)const\':" << endl
			 << "\'n\' is out of list range." << endl;
		exit(-1);
	}

	Node *p = head->_next;
	for(int i = 0; i < n; i++, p = p->_next){}
	return p->data;
}

template<typename DataType>
int DblList<DataType>::locate(DataType element)const
{
	int i = 0;
	Node *p = head->_next;
	while(p != tail)
	{
		if(p->data == element)
		{
			return i;
		}
		i++;
		p = p->_next;
	}
	return -1;
}

template<typename DataType>
bool DblList<DataType>::insert(int n, DataType element)
{
	if(n > length || n < 0)
	{
		cout << "Warning in bool DblList<DataType>::insert(int n, DataType)" << endl
			 << "\'n\' is not in [0, length]. Nothing has been done." << endl;
		return false;
	}
	Node *p = head;
	for(int i = 0; i < n; i++, p = p->_next){}
	Node *q = p->_next;
	p->_next = new Node(element, p, q);
	if(!(p->_next))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	q->_prev = p->_next;
	length++;
	return true;
}

template<typename DataType>
bool DblList<DataType>::erase(int n)
{
	if(n >= length || n < 0)
	{
		cout << "Warning in bool DblList<DataType>::erase(int n)" << endl
			 << "\'n\' is not in [0, length-1]. Nothing has been done." << endl;
		return false;
	}
	Node *p = head;
	for(int i = 0; i < n; i++, p = p->_next){}
	Node *q = p->_next;
	p->_next = q->_next;
	q->_next->_prev = p;
	delete q;
	length--;
	return true;
}

template<typename DataType>
void DblList<DataType>::push_back(DataType element)
{
	Node *p = tail->_prev;
	tail->_prev = new Node(element, p, tail);
	if(!(tail->_prev))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	p->_next = tail->_prev;
	length++;
}

template<typename DataType>
void DblList<DataType>::push_front(DataType element)
{
	Node *p = head->_next;
	head->_next = new Node(element, head, p);
	if(!(head->_next))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	p->_prev = head->_next;
	length++;
}

template<typename DataType>
DataType DblList<DataType>::pop_back()
{
	if(length == 0)
	{
		cout << "Error in \'DataType DblList<DataType>::pop_back()\'" << endl
			 << "The list is empty." << endl;
		exit(-1);
	}

	Node *p = tail->_prev;
	DataType element = p->data;
	p->_prev->_next = tail;
	tail->_prev = p->_prev;
	delete p;
	length--;
	return element;
}

template<typename DataType>
DataType DblList<DataType>::pop_front()
{
	if(length == 0)
	{
		cout << "Error in \'DataType DblList<DataType>::pop_front()\'" << endl
			 << "The list is empty." << endl;
		exit(-1);
	}

	Node *p = head->_next;
	DataType element = p->data;
	p->_next->_prev = head;
	head->_next = p->_next;
	delete p;
	length--;
	return element;
}

template<typename DataType>
DblList<DataType> DblList<DataType>::cat(const DblList<DataType>& list)
{
	Node *p = list.head->_next;
	while(p != list.tail)
	{
		Node *q = tail->_prev;
		tail->_prev = new Node(p->data, q, tail);
		if(!(tail->_prev))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		q->_next = tail->_prev;
		p = p->_next;
	}
	
	length += list.length;
	return *this;
}

template<typename DataType>
bool DblList<DataType>::swap(int i, int j)
{
	if(i < 0 || i >= length || j < 0 || j >= length || i == j)
	{
		cout << "Warning in bool DblList<DataType>::swap(int i, int j)" << endl
			 << "i or j is(are) out of range, or i == j now. Nothing has been done." << endl;
		return false;
	}
	if(i > j)
	{
		std::swap(i, j);
	}

	Node *pi_last = head;
	for(int it = 0; it < i; it++, pi_last = pi_last->_next){}
	Node *pj_last = head;
	for(int it = 0; it < j; it++, pj_last = pj_last->_next){}

	Node *pi = pi_last->_next;
	Node *pj = pj_last->_next;
	Node *pj__next = pj->_next;

	if(j-i > 1)
	{
		pi_last->_next = pj;
		pj->_prev = pi_last;
		pj->_next = pi->_next;
		pi->_next->_prev = pj;
		pj_last->_next = pi;
		pi->_prev = pj_last;
		pi->_next = pj__next;
		pj__next->_prev = pi;
	}
	else
	{
		pi_last->_next = pj;
		pj->_prev = pi_last;
		pj->_next = pi;
		pi->_prev = pj;
		pi->_next = pj__next;
		pj__next->_prev = pi;
	}

	return true;
}

template<class DataType>
ostream & operator <<(ostream& out, const DblList<DataType>& list)
{
	if(list.empty())
	{
		return out;
	}

	typename DblList<DataType>::iterator it = list.begin();
	out << (*it);
	it++;
	for(; it != list.end(); it++)
	{
		out << ", " << (*it);
	}

	return out;
}

#endif