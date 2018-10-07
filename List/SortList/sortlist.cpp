#ifdef SORTLIST_H

template<typename DataType>
typename SortList<DataType>::Node* SortList<DataType>::new_Node()
{
	SortList<DataType>::Node* node = new SortList<DataType>::Node();
	if(!node)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	return node;
}

template<typename DataType>
typename SortList<DataType>::Node* SortList<DataType>::new_Node(const DataType& data, Node* next)
{
	SortList<DataType>::Node* node = new SortList<DataType>::Node(data, next);
	if(!node)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	return node;
}

template<typename DataType>
SortList<DataType>::SortList()
{
	head = new_Node();
}

template<typename DataType>
SortList<DataType>::SortList(const SortList<DataType>& X)
{
	head = new_Node();
	
	Node* p = X.head;
	while(p->_next != NULL)
	{
		DataType value = (p->_next)->_data;
		insert(value);
		p = p->_next;
	}
}

template<typename DataType>
SortList<DataType>::~SortList<DataType>()
{
	Node* p;
	while( head->_next != NULL )
	{
		p = head->_next;
		head->_next = p->_next;
		delete p;
	}
}

template<typename DataType>
SortList<DataType>& SortList<DataType>::operator =(const SortList<DataType>& X)
{
	clear();
	Node* p = X.head;
	while(p->_next != NULL)
	{
		DataType value = (p->_next)->_data;
		insert(value);
		p = p->_next;
	}
	return (*this);
}

template<typename DataType>
bool SortList<DataType>::operator ==(const SortList<DataType>& X)const
{
	if(length() != X.length())
	{
		return false;
	}

	const_iterator it2 = X.begin();
	for(const_iterator it1 = begin(); it1 != end(); it1++)
	{
		if(*it1 != *it2)
		{
			return false;
		}
		it2++;
	}

	return true;
}

template<typename DataType>
bool SortList<DataType>::operator !=(const SortList<DataType>& X)const
{
	return !(*this == X);
}

template<typename DataType>
void SortList<DataType>::clear()
{
	Node* p;
	while( head->_next != NULL )
	{
		p = head->_next;
		head->_next = p->_next;
		delete p;
	}
}

template<typename DataType>
typename SortList<DataType>::const_iterator SortList<DataType>::begin()const
{
	return const_iterator(head->_next);
}

template<typename DataType>
typename SortList<DataType>::const_iterator SortList<DataType>::end()const
{
	return const_iterator();
}

template<typename DataType>
void SortList<DataType>::insert(const DataType& x)
{
	Node* newNode = new_Node();
	newNode->_data = x;
	Node* p;
	p = head;
	while( p->_next != NULL && (p->_next)->_data > x )
	{
		p = p->_next;
	}
	newNode->_next = p->_next;
	p->_next = newNode;
}

template<typename DataType>
void SortList<DataType>::erase(const int& i)
{
	int n = length();
	if( i < 0 || i >= n )
	{
		return;
	}
	Node* p = head;
	for(int index = 0; index < i; index++)
	{
		p = p->_next;
	}
	Node* q = p->_next;
	p->_next = (p->_next)->_next;
	delete q;
}

template<typename DataType>
void SortList<DataType>::erase(const const_iterator& it)
{
	Node* p = head;
	Node* q = it._ptr;

	while( p->_next != NULL && p->_next != q )
	{
		p = p->_next;
	}

	if(p->_next == q)
	{
		p->_next = q->_next;
		delete q;
	}
}

template<typename DataType>
int SortList<DataType>::length()const
{
	int n = 0;
	Node* p = head;
	while(p->_next != NULL)
	{
		p = p->_next;
		n++;
	}
	return n;
}

template<typename DataType>
bool SortList<DataType>::empty()const
{
	return ( head->_next == NULL );
}

template<typename DataType>
typename SortList<DataType>::const_iterator SortList<DataType>::find(const DataType& x)const
{
	Node* index = NULL;
	const_iterator it = begin();
	Node* p = it._ptr;
	
	while(p != NULL)
	{
		if(p->_data == x)
		{
			index = p;
			break;
		}
		p = p->_next;
	}
	return const_iterator(index);
}

template<typename DataType>
typename SortList<DataType>::const_iterator SortList<DataType>::locate(const int& i)const
{
	int n = length();
	if( i < 0 || i > n )
	{
		return NULL;
	}
	Node* p = head;
	for(int index = 1; index <= i; index++)
	{
		p = p->_next;
	}
	return const_iterator(p);
}

template<typename DataType>
int SortList<DataType>::locate(const const_iterator& it)const
{
	int i = 0;
	Node* p = head;
	Node* q = it._ptr;
	while( p->_next != NULL && p != q )
	{
		p = p->_next;
		i++;
	}

	if(p != q)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

template<typename DataType>
SortList<DataType> SortList<DataType>::merge(const SortList<DataType>& X)
{
	for(const_iterator it = X.begin(); it != X.end(); it++)
	{
		insert(*it);
	}
	return (*this);
}



template<typename DataType>
typename SortList<DataType>::const_iterator& SortList<DataType>::const_iterator::operator ++()
{
    if(_ptr)
    {
    	_ptr = _ptr->_next;
    }
    return *this;
}

template<typename DataType>
typename SortList<DataType>::const_iterator SortList<DataType>::const_iterator::operator ++(int)
{
    const_iterator tmp = *this;
    if(_ptr)
    {
    	_ptr = _ptr->_next;
    }

    return tmp;
}

template<typename DataType>
DataType SortList<DataType>::const_iterator::operator *()const
{
	if(_ptr)
	{
    	return _ptr->_data;
	}
	else
	{
		cout << "Error in *it! it is empty." << endl;
		exit(-1);
	}
}

template<typename DataType>
bool SortList<DataType>::const_iterator::empty()const
{
	return !_ptr;
}

template<typename DataType>
ostream& operator <<(ostream& out, const SortList<DataType>& list)
{
	if(list.empty())
	{
		return out;
	}

	typename SortList<DataType>::const_iterator it = list.begin();
	out << *it;
	it++;
	for(; it != list.end(); it++)
	{
		out << ", " << *it;
	}

	return out;
}

#endif