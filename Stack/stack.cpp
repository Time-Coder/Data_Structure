#ifdef STACK_H

// Stack's constructor without initial value.
template<typename DataType>
Stack<DataType>::Stack()
{
	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
}

//-------------------------------------------------------------------------------

// Stack's copy constructor.
template<typename DataType>
Stack<DataType>::Stack(const Stack<DataType>& stack)
{
	head = new Node;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	Node *p = head;
	Node *q = stack.head;
	while(q->_next != NULL)
	{
		p->_next = new Node(q->_next->_data);
		if(!(p->_next))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}

		p = p->_next;
		q = q->_next;
	}

	length = stack.length;
}

//-------------------------------------------------------------------------------

// Stack's destructor.
template<typename DataType>
Stack<DataType>::~Stack<DataType>()
{
	while(!empty())
	{
		pop();
	}
	length = 0;
	delete head;
}

//-------------------------------------------------------------------------------

// Function: void Stack<DataType>::clear();
// Description: Clear Stack's memory.
// Calls: Stack<DataType>::~Stack<DataType>();
//		  // Declared and defined in current file.
// Input Parameter: Nothing
// Output Parameter: Nothing
// Return: void.
template<typename DataType>
void Stack<DataType>::clear()
{
	while(!empty())
	{
		pop();
	}
	length = 0;
}

//-------------------------------------------------------------------------------

// Function: Stack<DataType>& operator =(const Stack<DataType>&);
// Descripsion: Reload Stack's operator "=".
//				Make it possible to use "=" to clone a Stack to another.
// Input Parameter: const Stack<DataType>& X:	Stack on the right of "=".
// Output Parameter: Nothing.
// Return: A reference of Stack.
template<typename DataType>
Stack<DataType>& Stack<DataType>::operator =(const Stack<DataType>& stack)
{
	clear();

	Node *p = head;
	Node *q = stack.head;
	while(q->_next != NULL)
	{
		p->_next = new Node(q->_next->_data);
		if(!(p->_next))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		p = p->_next;
		q = q->_next;
	}

	length = stack.length;

	return *this;
}

//-------------------------------------------------------------------------------

// Function: void push(const DataType&);
// Description: Push a element into Stack.
// Input Parameter: const DataType& x:	The element waited to be pushed into stack.
// Output Parameter: Nothing
// Return: void.
template<typename DataType>
void Stack<DataType>::push(const DataType& element)
{
	head->_next = new Node(element, head->_next);
	if(!(head->_next))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	length++;
}

//-------------------------------------------------------------------------------

// Function: DataType pop();
// Description: Pop a element from the Stack.
// Input Parameter: Nothing
// Output Parameter: Nothing
// Return: Poped element.
// Others: This function will delete the top element of the initial Stack.
template<typename DataType>
DataType Stack<DataType>::pop()
{
	if(empty())
	{
		cout << "Error in DataType Stack<DataType>::pop()" << endl
			 << "The stack is empty" << endl;
		exit(-1);
	}
	DataType element = head->_next->_data;
	Node *p = head->_next;
	head->_next = p->_next;
	delete p;
	length--;
	return element;
}

//-------------------------------------------------------------------------------

// Function: DataType top()const;
// Description: Look the top element of the Stack.
// Input Parameter: Nothing
// Output Parameter: Nothing
// Return: Poped element.
template<typename DataType>
DataType& Stack<DataType>::top()
{
	if(empty())
	{
		cout << "Error in DataType Stack<DataType>::top()const" << endl
			 << "The stack is empty!" << endl;
		exit(-1);
	}
	return head->_next->_data;
}

//-------------------------------------------------------------------------------

// Function: bool Stack<DataType>::empty()const;
// Description: To judge if a Stack is empty or not.
// Input Parameter: Nothing
// Output Parameter: Nothing
// Return: "true" when Stack is empty.
template<typename DataType>
bool Stack<DataType>::empty()const
{
	return (length == 0);
}

//-------------------------------------------------------------------------------

// Function: int Stack<DataType>::length()const;
// Description: To count there are how many elements in the stack.
// Input Parameter: Nothing
// Output Parameter: Nothing
// Return: The number of elements in the Stack.
template<typename DataType>
int Stack<DataType>::size()const
{
	return length;
}

//-------------------------------------------------------------------------------

// Function: Stack<DataType>& Stack<DataType>::inverse();
// Description: To reverse a Stack.
// Input Parameter: Nothing
// Output Parameter: Nothing
// Return: A reference to current stack.
template<typename DataType>
Stack<DataType>& Stack<DataType>::inverse()
{
	Stack<DataType> stack_temp;
	while(!empty())
	{
		stack_temp.push( pop() );
	}
	*this = stack_temp;
	return *this;
}

template<typename DataType>
ostream& operator <<(ostream& out, const Stack<DataType>& stack_origine)
{
	Stack<DataType> stack = stack_origine;
	if(stack.empty())
	{
		return out;
	}
	stack.inverse();

	DataType x = stack.pop();
	out << x;
	while(!stack.empty())
	{
		x = stack.pop();
		out << ", " << x;
	}

	return out;
}

#endif