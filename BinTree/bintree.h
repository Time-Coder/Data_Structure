#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <stack.h>

using namespace std;

template<class DataType>
class BinTree
{
	class Node
	{
	private:
		DataType _data;
		Node *_parent;
		Node *_lchild;
		Node *_rchild;

	public:
		Node();
		Node(const DataType& data, Node *parent = NULL, Node *lchild = NULL, Node *rchild = NULL);
		int size()const;
		int height()const;
		Node* insert_lchild(const DataType& value);
		Node* insert_rchild(const DataType& value);
	};

	class iterator
	{
	private:
		Node *_ptr = NULL;

	public:
		iterator(){}
		iterator(Node *ptr) : _ptr(ptr);
	    iterator& operator =(const iterator& it);
	    bool operator !=(const iterator& it);
	    bool operator ==(const iterator& it);
	    iterator& operator ++();
	    iterator operator ++(int);
	    char& operator *();
	};

private:
	int _iterate_method = 0;

	Node *_root = NULL;
	int _size = 0;

private:
	Node* new_Node(const DataType& value, Node* parent = NULL, Node* lchild = NULL, Node* rchild = NULL);

public:
	BinTree(){}
	BinTree(const BinTree<DataType>& tree);
	~BinTree();
	void clear();
	int size()const;
	bool empty()const;
	Node* root()const;
	Node* insert_root(const DataType& value);
	Node* insert_lchild(Node* node, const DataType& value);
	Node* insert_rchild(Node* node, const DataType& value);
	Node* attach_lchild(Node* node, const BinTree<DataType>& tree);
	Node* attach_rchild(Node* node, const BinTree<DataType>& tree);
	int remove(Node* node);
	BinTree<DataType>& secede(Node* node);
	BinTree<DataType>& subtree(Node* node);
	int iterate_method(int method);
	void show()const;

	BinTree<DataType>& operator =(const BinTree<DataType>& tree);
};

template<class DataType>
BinTree<DataType>::iterator& BinTree<DataType>::operator =(const iterator& it)
{
	_ptr = it._ptr;
	return *this;
}

template<class DataType>
bool BinTree<DataType>::operator !=(const iterator& it)
{
	return (_ptr != it._ptr);
}

template<class DataType>
bool BinTree<DataType>::operator ==(const iterator& it)
{
	return (_ptr != it._ptr);
}

template<class DataType>
DataType& BinTree<DataType>::operator *()
{
	return (_ptr->_data);
}

template<class DataType>
BinTree<DataType>::Node* BinTree<DataType>::new_Node(const DataType& value,
													 Node* parent,
													 Node* lchild,
													 Node* rchild)
{
	BinTree<DataType>::Node* p_node = new BinTree<DataType>::Node(value, parent, lchild, rchild);
	if(!p_node)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	return p_node;
}

// template<class DataType>
// BinTree<DataType>::BinTree(const BinTree<DataType>& tree)
// {
// 	Node* src_node;

// 	Node* void_node = NULL;
// 	Node** last_dest_node = &void_node;
// 	Node** dest_node = &_root;

// 	Stack<Node*> stack;
// 	stack.push(tree._root);
// 	while(!stack.empty())
// 	{
// 		src_node = stack.pop();
// 		if(src_node->rchild)
// 		{
// 			stack.push(src_node->rchild);
// 		}
// 		if(src_node->lchild)
// 		{
// 			stack.push(src_node->lchild);
// 		}
// 		*dest_node = new_Node(src_node->_data, *last_dest_node, NULL, NULL);
// 		*last_dest_node = *dest_node;
// 	}
// }

template<class DataType>
BinTree<DataType>::~BinTree()
{
	Stack<Node*> stack;
	stack.push(_root);
	while(!stack.empty())
	{
		Node *p_node = stack.pop();
		if(p_node->rchild)
		{
			stack.push(p_node->rchild);
		}
		if(p_node->lchild)
		{
			stack.push(p_node->lchild);
		}
		delete p_node;
	}
}

template<class DataType>
void BinTree<DataType>::clear()
{
	Stack<Node*> stack;
	stack.push(_root);
	while(!stack.empty())
	{
		Node *p_node = stack.pop();
		if(p_node->rchild)
		{
			stack.push(p_node->rchild);
		}
		if(p_node->lchild)
		{
			stack.push(p_node->lchild);
		}
		delete p_node;
	}
}

template<class DataType>
int BinTree<DataType>::remove(Node* node)
{
	Stack<Node*> stack;
	stack.push(node);
	int n = 0;
	while(!stack.empty())
	{
		node = stack.pop();
		if(node->rchild)
		{
			stack.push(node->rchild);
		}
		if(node->lchilde)
		{
			stack.push(node->lchild)
		}
		delete node;
		n++;
	}

	return n;
}

// BinTree<DataType>& secede(iterator node);
// BinTree<DataType>& subtree(iterator node);

template<class DataType>
int BinTree<DataType>::size()const
{
	return _size;
}

template<class DataType>
bool BinTree<DataType>::empty()const
{
	return (_root != NULL);
}

template<class DataType>
BinTree<DataType>::Node* BinTree<DataType>::root()const
{
	return _root;
}

template<class DataType>
BinTree<DataType>::Node* insert_root(const DataType& value)
{
	if(!empty())
	{
		clear();
	}

	return (_root = new_Node(value));
}

template<class DataType>
BinTree<DataType>::Node* BinTree<DataType>::insert_lchild(BinTree<DataType>::Node* node, const DataType& value)
{
	return node._ptr->insert_lchild(value);
}

template<class DataType>
BinTree<DataType>::Node* BinTree<DataType>::insert_rchild(BinTree<DataType>::Node* node, const DataType& value)
{
	return node._ptr->insert_rchild(value);
}

template<class DataType>
BinTree<DataType>::Node*
BinTree<DataType>::attach_lchild(BinTree<DataType>::Node* p_node, BinTree<DataType> tree)
{
	if(p_node->lchild)
	{
		cout << "Error in 'BinTree<DataType>::Node*" << endl
			 << "          BinTree<DataType>::attach_lchild(BinTree<DataType>::Node*," << endl
			 << "                                           const BinTree<DataType>&)'" << endl
			 << "Current node already has left child!" << endl;
		exit(-1);
	}

	p_node->lchild = tree._root;
	tree._root->parent = p_node;

	return tree._root;
}

template<class DataType>
BinTree<DataType>::Node*
BinTree<DataType>::attach_rchild(BinTree<DataType>::Node* p_node, BinTree<DataType> tree)
{
	if(p_node->rchild)
	{
		cout << "Error in 'BinTree<DataType>::Node*" << endl
			 << "          BinTree<DataType>::attach_rchild(BinTree<DataType>::Node*," << endl
			 << "                                           const BinTree<DataType>&)'" << endl
			 << "Current node already has right child!" << endl;
		exit(-1);
	}

	p_node->rchild = tree._root;
	tree._root->parent = p_node;

	return tree._root;
}

template<class DataType>
void BinTree<DataType>::show()
{
	ofstream file("bintree.dot");
	file << "digraph BinTree"
			"{"
			"	"
}

// int iterate_method(int method);

// iterator& operator ++();
// iterator operator ++(int);
// char& operator *();

#endif