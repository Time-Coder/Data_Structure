#include <string.h>

String::Block& String::Block::operator =(const String::Block& block)
{
	char *destptr = data;
	const char *srcptr = block.data;
	for(int i = 0; i < BLOCK_SIZE; i++)
	{
		*destptr++ = *srcptr++;
	}

	return *this;
}

String::Block* String::creat_block()
{
	String::Block* ptr = new String::Block;
	if(!ptr)
	{
		cerr << "Error when allocate memory!" << endl;
		exit(-1);
	}

	return ptr;
}

String::String(const String& str)
{
	if(!str.length)
	{
		return;
	}

	length = str.length;
	first = creat_block();
	last = first;
	*first = *(str.first);

	Block *srcptr = str.first;
	while(srcptr->link)
	{
		last->link = creat_block();
		*(last->link) = *(srcptr->link);
		last = last->link;
		srcptr = srcptr->link;
	}
}

String::String(const char* str)
{
	if(*str == '\0')
	{
		return;
	}

	char* destptr;
	const char* srcptr = str;

	first = creat_block();
	destptr = first->data;
	last = first;

	int i = 1;
	while(*srcptr != '\0')
	{
		if(i > BLOCK_SIZE)
		{
			last->link = creat_block();
			last = last->link;
			destptr = last->data;
			i = 1;
		}
		*destptr++ = *srcptr++;
		i++;
		length++;
	}

	while(i++ <= BLOCK_SIZE)
	{
		*destptr++ = '\0';
	}
}

String::~String()
{
	String::Block* p = first;
	while(first)
	{
		p = first;
		delete [] first->data;
		first = first->link;
		delete p;
	}
	last = NULL;
	length = 0;
}

void String::clear()
{
	String::Block* p = first;
	while(first)
	{
		p = first;
		delete [] first->data;
		first = first->link;
		delete p;
	}
	last = NULL;
	length = 0;
}

int String::size()const
{
	return length;
}

String& String::operator =(const String& str)
{
	clear();

	if(!str.length)
	{
		return *this;
	}

	length = str.length;
	first = creat_block();
	last = first;
	*first = *(str.first);

	Block *srcptr = str.first;
	while(srcptr->link)
	{
		last->link = creat_block();
		*(last->link) = *(srcptr->link);
		last = last->link;
		srcptr = srcptr->link;
	}

	return *this;
}

String& String::operator =(const char* str)
{
	clear();

	if(*str == '\0')
	{
		return *this;
	}

	char* destptr;
	const char* srcptr = str;

	first = creat_block();
	destptr = first->data;
	last = first;

	int i = 1;
	while(*srcptr != '\0')
	{
		if(i > BLOCK_SIZE)
		{
			last->link = creat_block();
			last = last->link;
			destptr = last->data;
			i = 1;
		}
		*destptr++ = *srcptr++;
		i++;
		length++;
	}

	while(i++ <= BLOCK_SIZE)
	{
		*destptr++ = '\0';
	}

	return *this;
}

char& String::operator [](int i)
{
	if(i < 0 || i >= length)
	{
		cout << "Error in 'char& String::operator [](int i)'. Index i is out of range!" << endl;
		exit(-1);
	}

	int n_block = i / BLOCK_SIZE;
	int i_inner = i % BLOCK_SIZE;
	String::Block *ptr_block = first;
	while(n_block--)
	{
		ptr_block = ptr_block->link;
	}
	return ptr_block->data[i_inner];
}

char String::operator [](int i)const
{
	if(i < 0 || i >= length)
	{
		return '\0';
	}

	int n_block = i / BLOCK_SIZE;
	int i_inner = i % BLOCK_SIZE;
	String::Block *ptr_block = first;
	while(n_block--)
	{
		ptr_block = ptr_block->link;
	}
	return ptr_block->data[i_inner];
}

ostream& operator <<(ostream& out, String str)
{
	String::Block* blockptr = str.first;
	while(blockptr)
	{
		char* p = blockptr->data;
		for(int i = 0; i < BLOCK_SIZE; i++, p++)
		{
			out << *p;
		}
		
		blockptr = blockptr->link;
	}

	return out;
}

String::iterator& String::iterator::operator =(const String::iterator& it)
{
	current_block = it.current_block;
	i_inner = it.i_inner;
    ptr = it.ptr;

    return *this;
}

bool String::iterator::operator !=(const iterator& it)
{
    return (ptr != it.ptr);
}

bool String::iterator::operator ==(const iterator& it)
{
    return (ptr == it.ptr);
}

String::iterator& String::iterator::operator ++()
{
    if(i_inner == BLOCK_SIZE-1)
    {
    	if(current_block->link == NULL)
    	{
    		ptr = NULL;
    	}
    	else
    	{
    		current_block = current_block->link;
        	ptr = current_block->data;
        	i_inner = 0;
    	}
    }
    else
    {
    	ptr++;
    	i_inner++;
    }
    return *this;
}

String::iterator String::iterator::operator ++(int)
{
    iterator temp = *this;
    if(i_inner == BLOCK_SIZE-1)
    {
    	if(current_block->link == NULL)
    	{
    		ptr = NULL;
    	}
    	else
    	{
    		current_block = current_block->link;
        	ptr = current_block->data;
        	i_inner = 0;
    	}
    }
    else
    {
    	ptr++;
    	i_inner++;
    }
    return temp;
}

char& String::iterator::operator *()
{
    return *ptr;
}

String::iterator String::begin()
{
	String::iterator it;
	it.current_block = first;
	it.ptr = it.current_block->data;

	return it;
}

String::iterator String::end()
{
	String::iterator it;

	return it;
}

int* calculate_next(const String& pattern)
{
	int* next = new int[pattern.size()];
	next[0] = -1;

	for(int j = 1; j < pattern.size(); j++)
	{
		int k = next[j-1];
		while(k != -1 && pattern[j] != pattern[k])
		{
			k = next[k];
		}
		next[j] = k + 1;
	}

	return next;
}

int String::find(const String& pattern)const
{
	int* next = calculate_next(pattern);

	int i = 0, j = 0;
	while(length - i > pattern.length - j)
	{
		if(j == -1 || (*this)[i] == pattern[j])
		{
			j++;
			if(j == pattern.length)
			{
				return i - pattern.length + 1;
			}
			i++;
		}
		else
		{
			j = next[j];
		}
	}

	delete next;

	return -1;
}

int String::find(const char* pattern)const
{
	return find(String(pattern));
}