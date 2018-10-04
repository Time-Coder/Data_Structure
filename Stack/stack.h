// Copyright: 2017 Bing-Hui WANG
//
// Author: Bing-Hui WANG
//
// Date: 2017-10-3
//
// Description: This code has build a Stack's template class.
//
// Edit in 2018-5-26: Do some simplification.
//
// See usage in "./README.md"
// See examples in "./examples/"

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

// Define struct "StackNode" to store a stack element.
template<typename DataType>
class StackNode
{
public:
	DataType data;			// Store the real value of a StackNode.
	StackNode *link = NULL; // Store the pointer that point to next StackNode.

public:
	StackNode<DataType>(){};
	StackNode<DataType>(DataType element)
	{
		data = element;
	}
	StackNode<DataType>(DataType element, StackNode *ptr)
	{
		data = element;
		link = ptr;
	}
};

template<typename DataType>
class Stack
{
	// Define the cout format of Stack.
	friend ostream & operator <<(ostream &o, const Stack<DataType>& X)
	{
		Stack<DataType> S1;
		Stack<DataType> S2;
		S1 = X;
		S2 = X;

		o << endl << endl;

		if( S1.empty() )
		{
			o << "| (void) |" << endl;
			o << "----------" << endl;
		}
		else
		{
			DataType longest_element = S1.pop();
			string longest_string = Stack::cout2string(longest_element);
			while( !S1.empty() )
			{
				DataType temp_element = S1.pop();
				string temp_string = Stack::cout2string(temp_element);
				if( temp_string.size() > longest_string.size() )
				{
					longest_string = temp_string;
				}
			}

			while( !S2.empty() )
			{
				DataType temp_element = S2.pop();
				o << "| " << temp_element << " ";
				int i = 0;
				string temp_string = Stack::cout2string(temp_element);

				while(i != longest_string.size()-temp_string.size())
				{
					o << " ";
					i++;
				}

				o << "|" << endl;
			}
			o << "--";
			for(int i = 0; i < longest_string.size(); i++)
			{
				o << "-";
			}
			o << "--" << endl;
		}	

		return o;
	}

public:
	static string cout2string(const DataType& element)
	{
	    ostringstream oss;
	    oss << element;
	    return oss.str();
	}

private:
	StackNode<DataType> *head;
	// To store a Stack, just need to store it's head node's adress.
	int length = 0;

public:
	// Stack's constructor without initial value.
	Stack<DataType>();

	// Stack's copy constructor.
	Stack<DataType>(const Stack<DataType>& stack);

	// Stack's destructor.
	~Stack<DataType>();

	//-------------------------------------------------------------------------------

	// Function: Stack<DataType>& operator =(const Stack<DataType>&);
	// Descripsion: Reload Stack's operator "=".
	//				Make it possible to use "=" to clone a Stack to another.
	// Input Parameter: const Stack<DataType>& X:	Stack on the right of "=".
	// Output Parameter: Nothing.
	// Return: A reference of Stack.
	Stack<DataType>& operator =(const Stack<DataType>& stack);

	//-------------------------------------------------------------------------------

	// Function: void Stack<DataType>::clear();
    // Description: Clear Stack's memory.
    // Input Parameter: Nothing
    // Output Parameter: Nothing
    // Return: void.
	void clear();

	//-------------------------------------------------------------------------------

	// Function: void push(const DataType&);
    // Description: Push a element into Stack.
    // Input Parameter: const DataType& x:	The element waited to be pushed into stack.
    // Output Parameter: Nothing
    // Return: void.
	void push(const DataType& element);

	//-------------------------------------------------------------------------------

	// Function: DataType pop();
    // Description: Pop a element from the Stack.
    // Input Parameter: Nothing
    // Output Parameter: Nothing
    // Return: Poped element.
    // Others: This function will delete the top element of the initial Stack.
	DataType pop();

	//-------------------------------------------------------------------------------

	// Function: DataType top()const;
    // Description: Look the top element of the Stack.
    // Input Parameter: Nothing
    // Output Parameter: Nothing
    // Return: Poped element.
	DataType top()const;

	//-------------------------------------------------------------------------------

	// Function: bool Stack<DataType>::empty()const;
    // Description: To judge if a Stack is empty or not.
    // Input Parameter: Nothing
    // Output Parameter: Nothing
    // Return: "true" when Stack is empty.
	bool empty()const;

	//-------------------------------------------------------------------------------

	// Function: int Stack<DataType>::length()const;
    // Description: To count there are how many elements in the stack.
    // Input Parameter: Nothing
    // Output Parameter: Nothing
    // Return: The number of elements in the Stack.
	int size()const;

	//-------------------------------------------------------------------------------

	// Function: Stack<DataType>& Stack<DataType>::inverse();
    // Description: To reverse a Stack.
    // Input Parameter: Nothing
    // Output Parameter: Nothing
    // Return: A reference to current stack.
	Stack<DataType>& inverse();
};

//-------------------------------------------------------------------------------

// Stack's constructor without initial value.
template<typename DataType>
Stack<DataType>::Stack()
{
	head = new StackNode<DataType>;
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
	head = new StackNode<DataType>;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	StackNode<DataType> *p = head;
	StackNode<DataType> *q = stack.head;
	while(q->link != NULL)
	{
		p->link = new StackNode<DataType>(q->link->data);
		if(!(p->link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}

		p = p->link;
		q = q->link;
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

	StackNode<DataType> *p = head;
	StackNode<DataType> *q = stack.head;
	while(q->link != NULL)
	{
		p->link = new StackNode<DataType>(q->link->data);
		if(!(p->link))
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		p = p->link;
		q = q->link;
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
	head->link = new StackNode<DataType>(element, head->link);
	if(!(head->link))
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
	DataType element = head->link->data;
	StackNode<DataType> *p = head->link;
	head->link = p->link;
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
DataType Stack<DataType>::top()const
{
	if(empty())
	{
		cout << "Error in DataType Stack<DataType>::top()const" << endl
			 << "The stack is empty!" << endl;
		exit(-1);
	}
	return head->link->data;
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
	Stack<DataType> stackTemp;
	while(!empty())
	{
		stackTemp.push( pop() );
	}
	*this = stackTemp;
	return *this;
}

#endif