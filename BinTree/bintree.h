#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

template<class DataType>
class BinTree
{
public:
	class Node
	{
	private:
		DataType _data;
		Node *_parent = NULL;
		Node *_lchild = NULL;
		Node *_rchild = NULL;
	
	public:
		Node(){} // tested
		Node(const DataType& data, Node *parent = NULL, Node *lchild = NULL, Node *rchild = NULL) :
		_data(data), _parent(parent), _lchild(lchild), _rchild(rchild){} // tested
		~Node(){_parent = NULL; _lchild = NULL; _rchild = NULL;} // tested
		int size()const; // tested
		int height()const;
		Node*& lchild();
		Node*& rchild();
		Node*& parent();
		DataType data()const;
		Node* insert_lchild(const DataType& value);
		Node* insert_rchild(const DataType& value);
		bool isleaf()const;
	};

private:
	int _iterate_method = 0;

	Node *_root = NULL;
	int _size = 0;

private:
	static Node* new_Node(const DataType& value, Node* parent = NULL, Node* lchild = NULL, Node* rchild = NULL);
	void copy(BinTree<DataType>& dest_tree, const BinTree<DataType>& src_tree);

public:
	BinTree(){}
	BinTree(const BinTree<DataType>& tree);
	~BinTree();
	void clear();
	int size()const;
	int height()const;
	bool empty()const;
	bool hasnode(const Node& node)const;
	bool hasnode(Node* node)const;
	Node* root()const;
	Node* insert_root(const DataType& value);
	Node* insert_lchild(Node* node, const DataType& value);
	Node* insert_rchild(Node* node, const DataType& value);
	Node* attach_lchild(Node* node, const BinTree<DataType>& tree);
	Node* attach_rchild(Node* node, const BinTree<DataType>& tree);
	int remove(Node* node);
	BinTree<DataType>& secede(Node* node);
	static BinTree<DataType>& subtree(Node* node);
	int iterate_method(int method);
	void show(const string& filename = "temp.pdf")const;
	void write(const string& filename)const;

	BinTree<DataType>& operator =(const BinTree<DataType>& tree);
};

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::new_Node(const DataType& value,
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

template<class DataType>
int BinTree<DataType>::Node::size()const
{
	if(isleaf())
	{
		return 1;
	}

	int n = 1;
	if(_lchild)
	{
		n += _lchild->size();
	}
	if(_rchild)
	{
		n += _rchild->size();
	}

	return n;
}

template<class DataType>
int BinTree<DataType>::Node::height()const
{
	if(isleaf())
	{
		return 0;
	}

	int lheight = -1, rheight = -1;
	if(_lchild)
	{
		lheight = _lchild->height();
	}
	if(_rchild)
	{
		rheight = _rchild->height();
	}

	return max(lheight, rheight) + 1;
}

template<class DataType>
typename BinTree<DataType>::Node*& BinTree<DataType>::Node::lchild()
{
	return _lchild;
}

template<class DataType>
typename BinTree<DataType>::Node*& BinTree<DataType>::Node::rchild()
{
	return _rchild;
}

template<class DataType>
typename BinTree<DataType>::Node*& BinTree<DataType>::Node::parent()
{
	return _parent;
}

template<class DataType>
DataType BinTree<DataType>::Node::data()const
{
	return _data;
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::Node::insert_lchild(const DataType& value)
{
	if(_lchild)
	{
		cout << "Error in 'typename BinTree<DataType>::Node* BinTree<DataType>::Node::insert_lchild(const DataType& value)'" << endl
			 << "Current node already has left child!" << endl;
		exit(-1);
	}
	_lchild = new_Node(value, this);

	return _lchild;
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::Node::insert_rchild(const DataType& value)
{
	if(_rchild)
	{
		cout << "Error in 'typename BinTree<DataType>::Node* BinTree<DataType>::Node::insert_rchild(const DataType& value)'" << endl
			 << "Current node already has right child!" << endl;
		exit(-1);
	}
	_rchild = new_Node(value, this);

	return _rchild;
}

template<class DataType>
bool BinTree<DataType>::Node::isleaf()const
{
	return !(_lchild || _rchild);
}

template<class DataType>
void BinTree<DataType>::copy(BinTree<DataType>& dest_tree, const BinTree<DataType>& src_tree)
{
	dest_tree.clear();
	dest_tree._size = src_tree._size;
	dest_tree._iterate_method = src_tree._iterate_method;

	Node* src_node;
	Node* dest_node = dest_tree._root;
	dest_tree._root = new_Node(src_tree._root->data());

	Stack<Node*> src_stack, dest_stack;
	src_stack.push(src_tree._root);
	dest_stack.push(dest_tree._root);

	while(!src_stack.empty())
	{
		src_node = src_stack.pop();
		dest_node = dest_stack.pop();
		if(src_node->rchild())
		{
			dest_node->rchild() = new_Node(src_node->rchild()->data(), dest_node);
			src_stack.push(src_node->rchild());
			dest_stack.push(dest_node->rchild());
		}
		if(src_node->lchild())
		{
			dest_node->lchild() = new_Node(src_node->lchild()->data(), dest_node);
			src_stack.push(src_node->lchild());
			dest_stack.push(dest_node->lchild());
		}
	}
}

template<class DataType>
BinTree<DataType>::BinTree(const BinTree<DataType>& tree)
{
	copy(*this, tree);
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::operator =(const BinTree<DataType>& tree)
{
	copy(*this, tree);

	return *this;
}

template<class DataType>
BinTree<DataType>::~BinTree()
{
	clear();
}

template<class DataType>
void BinTree<DataType>::clear()
{
	if(empty())
	{
		return;
	}

	Stack<Node*> stack;
	stack.push(_root);
	while(!stack.empty())
	{
		Node *p_node = stack.pop();
		if(p_node->rchild())
		{
			stack.push(p_node->rchild());
		}
		if(p_node->lchild())
		{
			stack.push(p_node->lchild());
		}
		delete p_node;
	}

	_root = NULL;
	_size = 0;
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
		if(node->rchild())
		{
			stack.push(node->rchild());
		}
		if(node->lchild())
		{
			stack.push(node->lchild());
		}
		delete node;
		n++;
	}
	_size -= n;

	return n;
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::secede(Node* p_node)
{
	if(!hasnode(p_node))
	{
		cout << "Error in 'BinTree<DataType>& BinTree<DataType>::secede(Node* p_node)'" << endl
			 << "Current node is not in this tree!" << endl;
		exit(-1);
	}

	BinTree<DataType>* p_dest_tree = new BinTree<DataType>;
	p_dest_tree->_root = p_node;
	p_dest_tree->_size = p_node->size();
	p_dest_tree->_iterate_method = _iterate_method;
	
	_size -= p_dest_tree->_size;

	if(p_node == _root)
	{
		_root = NULL;
	}
	else
	{
		if(p_node->parent()->lchild() == p_node)
		{
			p_node->parent()->lchild() = NULL;
		}
		else if(p_node->parent()->rchild() == p_node)
		{
			p_node->parent()->rchild() = NULL;
		}
	}

	return *p_dest_tree;
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::subtree(Node* p_node)
{
	if(!hasnode(p_node))
	{
		cout << "Error in 'BinTree<DataType>& BinTree<DataType>::subtree(Node* p_node)'" << endl
			 << "Current node is not in this tree!" << endl;
		exit(-1);
	}

	BinTree<DataType>* ptr_dest_tree = new BinTree<DataType>;
	if(!ptr_dest_tree)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	ptr_dest_tree->_root = new_Node(p_node->data());

	Node* src_node;
	Node* dest_node;

	Stack<Node*> src_stack, dest_stack;
	src_stack.push(p_node);
	dest_stack.push(ptr_dest_tree->_root);

	ptr_dest_tree->_size = 1;
	while(!src_stack.empty())
	{
		src_node = src_stack.pop();
		dest_node = dest_stack.pop();
		if(src_node->rchild())
		{
			dest_node->rchild() = new_Node(src_node->rchild()->data(), dest_node);
			ptr_dest_tree->_size++;
			src_stack.push(src_node->rchild());
			dest_stack.push(dest_node->rchild());
		}
		if(src_node->lchild())
		{
			dest_node->lchild() = new_Node(src_node->lchild()->data(), dest_node);
			ptr_dest_tree->_size++;
			src_stack.push(src_node->lchild());
			dest_stack.push(dest_node->lchild());
		}
	}

	return *ptr_dest_tree;
}

template<class DataType>
int BinTree<DataType>::size()const
{
	return _size;
}

template<class DataType>
int BinTree<DataType>::height()const
{
	return _root->height();
}

template<class DataType>
bool BinTree<DataType>::empty()const
{
	return (_root == NULL);
}

template<class DataType>
bool BinTree<DataType>::hasnode(Node* p_node)const
{
	while(p_node->parent())
	{
		p_node = p_node->parent();
	}

	return (p_node == _root);
}

template<class DataType>
bool BinTree<DataType>::hasnode(const Node& node)const
{
	Node* p_node = &node;
	while(p_node->parent)
	{
		p_node = p_node->parent;
	}

	return (p_node == _root);
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::root()const
{
	return _root;
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::insert_root(const DataType& value)
{
	if(!empty())
	{
		clear();
	}
	_size++;
	return (_root = new_Node(value));
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::insert_lchild(BinTree<DataType>::Node* node, const DataType& value)
{
	_size++;
	return node->insert_lchild(value);
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::insert_rchild(BinTree<DataType>::Node* node, const DataType& value)
{
	_size++;
	return node->insert_rchild(value);
}

template<class DataType>
typename BinTree<DataType>::Node*
BinTree<DataType>::attach_lchild(BinTree<DataType>::Node* p_node, const BinTree<DataType>& tree)
{
	if(p_node->lchild())
	{
		cout << "Error in 'BinTree<DataType>::Node*" << endl
			 << "          BinTree<DataType>::attach_lchild(BinTree<DataType>::Node*," << endl
			 << "                                           const BinTree<DataType>&)'" << endl
			 << "Current node already has left child!" << endl;
		exit(-1);
	}

	BinTree<DataType>* p_tree = new BinTree<DataType>(tree);

	_size += p_tree->_size;
	p_node->lchild() = p_tree->_root;
	p_tree->_root->parent() = p_node;

	return p_tree->_root;
}

template<class DataType>
typename BinTree<DataType>::Node*
BinTree<DataType>::attach_rchild(BinTree<DataType>::Node* p_node, const BinTree<DataType>& tree)
{
	if(p_node->rchild())
	{
		cout << "Error in 'BinTree<DataType>::Node*" << endl
			 << "          BinTree<DataType>::attach_rchild(BinTree<DataType>::Node*," << endl
			 << "                                           const BinTree<DataType>&)'" << endl
			 << "Current node already has right child!" << endl;
		exit(-1);
	}

	BinTree<DataType>* p_tree = new BinTree<DataType>(tree);

	_size += p_tree->_size;
	p_node->rchild() = p_tree->_root;
	p_tree->_root->parent() = p_node;

	return p_tree->_root;
}

template<class DataType>
void BinTree<DataType>::write(const string& filename)const
{
	if(empty())
	{
		cout << "The tree is empty, nothing to write!" << endl;
		return;
	}

	ofstream file("Figures/bintree.dot");
	file << "graph BinTree" << endl
		 <<	"{" << endl
		 << "	graph[ordering=\"out\"];" << endl << endl;
		 
	Node* p_node;
	Stack<Node*> stack, stack_all;
	Stack<int> stack_name;
	stack.push(_root);
	stack_all.push(_root);
	int node_name = 0;
	stack_name.push(node_name);

	while(!stack.empty())
	{
		p_node = stack.pop();
		int current_name = stack_name.pop();
		if(p_node && !(p_node->isleaf()) )
		{
			node_name++;
			if(p_node->lchild())
			{
				file << "\t" << current_name << "--" << node_name << ";" << endl;
			}
			else
			{
				file << "\t" << current_name << "--NULL" << node_name << "[style=\"invis\"];" << endl;
			}
			stack.push(p_node->lchild());
			stack_all.push(p_node->lchild());
			stack_name.push(node_name);

			node_name++;
			if(p_node->rchild())
			{
				file << "\t" << current_name << "--" << node_name << ";" << endl;
			}
			else
			{
				file << "\t" << current_name << "--NULL" << node_name << "[style=\"invis\"];" << endl;
			}
			stack.push(p_node->rchild());
			stack_all.push(p_node->rchild());
			stack_name.push(node_name);
		}
	}

	file << endl;
	while(!stack_all.empty())
	{
		p_node = stack_all.pop();
		if(!p_node)
		{
			file << "	NULL" << node_name-- << "[shape=\"circle\",label=A,style=\"invis\"];" << endl;
		}
		else
		{
			file << "\t" << node_name-- << "[shape=\"circle\",label=\"" << p_node->data() << "\"];" << endl;
		}
	}

	file << "}" << endl;
	file.close();
	string cmd = "dot Figures/bintree.dot | gvpr -c -f Figures/binarytree.gvpr | neato -n -Tpdf -o Figures/" + filename;
	system(cmd.data());
}

template<class DataType>
void BinTree<DataType>::show(const string& filename)const
{
	if(empty())
	{
		cout << "The tree is empty, nothing to show!" << endl;
		return;
	}

	write(filename);
	string cmd = "start sumatrapdf Figures/" + filename;
	system(cmd.data());
}

// int iterate_method(int method);

// iterator& operator ++();
// iterator operator ++(int);
// char& operator *();

#endif