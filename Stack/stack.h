// Copyright: 2017 Bing-Hui WANG
//
// Author: Bing-Hui WANG
//
// Date: 2017-10-3
//
// Description: This code has build a Stack's template class.
//
// See usage in "./README.md"
// See examples in "./examples/"

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

// Convert a variable X of type "DataType" into string in cout format.
template<typename DataType>
string cout2string(const DataType& X);

// Define class "StackNode" to store a stack element.
template<typename DataType>
class StackNode
{
public:
	DataType data;			// Store the real value of a StackNode.
	StackNode *link = NULL; // Store the pointer that point to next StackNode.

public:
	// StackNode's constructor without initial value.
	StackNode<DataType>()
	{
		link = NULL;
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
			string longest_string = cout2string(longest_element);
			while( !S1.empty() )
			{
				DataType temp_element = S1.pop();
				string temp_string = cout2string(temp_element);
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
				string temp_string = cout2string(temp_element);

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

private:
	StackNode<DataType> *head;
	// To store a Stack, just need to store it's head node's adress.

public:
	// Stack's constructor without initial value.
	Stack<DataType>();

	// Stack's copy constructor.
	Stack<DataType>(const Stack<DataType>& X);

	// Stack's destructor.
	~Stack<DataType>();

	//-------------------------------------------------------------------------------

	// Function: Stack<DataType>& operator =(const Stack<DataType>&);
	//
	// Descripsion: Reload Stack's operator "=".
	//				Make it possible to use "=" to clone a Stack to another.
	//
	// Input Parameter: const Stack<DataType>& X:	Stack on the right of "=".
	//
	// Output Parameter: Nothing.
	//
	// Return: A reference of Stack.
	Stack<DataType>& operator =(const Stack<DataType>& X);

	//-------------------------------------------------------------------------------

	// Function: void Stack<DataType>::clear();
	//
    // Description: Clear Stack's memory.
    //
    // Input Parameter: Nothing
    //
    // Output Parameter: Nothing
    //
    // Return: void.
	void clear();

	//-------------------------------------------------------------------------------

	// Function: void push(const DataType&);
	//
    // Description: Push a element into Stack.
    //
    // Input Parameter: const DataType& x:	The element waited to be pushed into stack.
    //
    // Output Parameter: Nothing
    //
    // Return: void.
	void push(const DataType& x);

	//-------------------------------------------------------------------------------

	// Function: DataType pop();
	//
    // Description: Pop a element from the Stack.
    //
    // Input Parameter: Nothing
    //
    // Output Parameter: Nothing
    //
    // Return: Poped element.
    //
    // Others: This function will delete the top element of the initial Stack.
	DataType pop();

	//-------------------------------------------------------------------------------

	// Function: DataType top()const;
	//
    // Description: Look the top element of the Stack.
    //
    // Input Parameter: Nothing
    //
    // Output Parameter: Nothing
    //
    // Return: Poped element.
	DataType top()const;

	//-------------------------------------------------------------------------------

	// Function: bool Stack<DataType>::empty()const;
	//
    // Description: To judge if a Stack is empty or not.
    //
    // Input Parameter: Nothing
    //
    // Output Parameter: Nothing
    //
    // Return: "true" when Stack is empty.
	bool empty()const;

	//-------------------------------------------------------------------------------

	// Function: int Stack<DataType>::length()const;
	//
    // Description: To count there are how many elements in the stack.
    //
    // Input Parameter: Nothing
    //
    // Output Parameter: Nothing
    //
    // Return: The number of elements in the Stack.
	int length()const;

	//-------------------------------------------------------------------------------

	// Function: Stack<DataType>& Stack<DataType>::inverse();
	//
    // Description: To reverse a Stack.
    //
    // Input Parameter: Nothing
    //
    // Output Parameter: Nothing
    //
    // Return: A reference to current stack.
	Stack<DataType>& inverse();
};

//-------------------------------------------------------------------------------

// Convert a variable X of type "DataType" into string in cout format.
template<typename DataType>
string cout2string(const DataType& X)
{
    ostringstream strs;
    strs << X;
    return strs.str();
}

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
	head->link = NULL;
}

//-------------------------------------------------------------------------------

// Stack's copy constructor.
template<typename DataType>
Stack<DataType>::Stack(const Stack<DataType>& X)
{
	head = new StackNode<DataType>;
	if(!head)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	StackNode<DataType> *p = head;
	StackNode<DataType> *q = X.head;
	while(q->link != NULL)
	{
		StackNode<DataType> *newNode = new StackNode<DataType>;
		if(!newNode)
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}

		newNode->data = (q->link)->data;
		newNode->link = NULL;
		p->link = newNode;

		p = p->link;
		q = q->link;
	}
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
}

//-------------------------------------------------------------------------------

// Function: void Stack<DataType>::clear();
//
// Description: Clear Stack's memory.
//
// Calls: Stack<DataType>::~Stack<DataType>();
//		  // Declared and defined in current file.
//
// Input Parameter: Nothing
//
// Output Parameter: Nothing
//
// Return: void.
template<typename DataType>
void Stack<DataType>::clear()
{
	this->~Stack<DataType>();
}

//-------------------------------------------------------------------------------

// Function: Stack<DataType>& operator =(const Stack<DataType>&);
//
// Descripsion: Reload Stack's operator "=".
//				Make it possible to use "=" to clone a Stack to another.
//
// Input Parameter: const Stack<DataType>& X:	Stack on the right of "=".
//
// Output Parameter: Nothing.
//
// Return: A reference of Stack.
template<typename DataType>
Stack<DataType>& Stack<DataType>::operator =(const Stack<DataType>& X)
{
	clear();

	StackNode<DataType> *p = head;
	StackNode<DataType> *q = X.head;
	while(q->link != NULL)
	{
		StackNode<DataType> *newNode = new StackNode<DataType>;
		if(!newNode)
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}
		newNode->data = (q->link)->data;
		newNode->link = NULL;
		p->link = newNode;

		p = p->link;
		q = q->link;
	}

	return *this;
}

//-------------------------------------------------------------------------------

// Function: void push(const DataType&);
//
// Description: Push a element into Stack.
//
// Input Parameter: const DataType& x:	The element waited to be pushed into stack.
//
// Output Parameter: Nothing
//
// Return: void.
template<typename DataType>
void Stack<DataType>::push(const DataType& x)
{
	StackNode<DataType> *newNode = new StackNode<DataType>;
	if(!newNode)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	newNode->data = x;
	newNode->link = (head)->link;
	(head)->link = newNode;
}

//-------------------------------------------------------------------------------

// Function: DataType pop();
//
// Description: Pop a element from the Stack.
//
// Input Parameter: Nothing
//
// Output Parameter: Nothing
//
// Return: Poped element.
//
// Others: This function will delete the top element of the initial Stack.
template<typename DataType>
DataType Stack<DataType>::pop()
{
	int __NaN = 0xFFC00000;
	const DataType NaN = *((DataType *)&__NaN);
	if(empty())
	{
		cout << "Error in Stack::pop! The stack is empty!" << endl;
		return NaN;
	}
	DataType element = head->link->data;
	StackNode<DataType> *p = head->link;
	head->link = head->link->link;
	delete p;
	return element;
}

//-------------------------------------------------------------------------------

// Function: DataType top()const;
//
// Description: Look the top element of the Stack.
//
// Input Parameter: Nothing
//
// Output Parameter: Nothing
//
// Return: Poped element.
template<typename DataType>
DataType Stack<DataType>::top()const
{
	int __NaN = 0xFFC00000;
	const DataType NaN = *((DataType *)&__NaN);
	if(empty())
	{
		cout << "Error in Stack::top! The stack is empty!" << endl;
		return NaN;
	}
	return head->link->data;
}

//-------------------------------------------------------------------------------

// Function: bool Stack<DataType>::empty()const;
//
// Description: To judge if a Stack is empty or not.
//
// Input Parameter: Nothing
//
// Output Parameter: Nothing
//
// Return: "true" when Stack is empty.
template<typename DataType>
bool Stack<DataType>::empty()const
{
	return (head->link == NULL);
}

//-------------------------------------------------------------------------------

// Function: int Stack<DataType>::length()const;
//
// Description: To count there are how many elements in the stack.
//
// Input Parameter: Nothing
//
// Output Parameter: Nothing
//
// Return: The number of elements in the Stack.
template<typename DataType>
int Stack<DataType>::length()const
{
	int n = 0;

	StackNode<DataType> *p = head;
	while(p->link != NULL)
	{
		n++;
		p = p->link;
	}

	return n;
}

//-------------------------------------------------------------------------------

// Function: Stack<DataType>& Stack<DataType>::inverse();
//
// Description: To reverse a Stack.
//
// Input Parameter: Nothing
//
// Output Parameter: Nothing
//
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