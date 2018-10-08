#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <fstream>

#include <stack.h>
#include <queue.h>
#include <tree.h>

using namespace std;

template<class DataType>
class Tree;

template<class DataType>
class Forest;

template<class DataType>
class BinTree
{
public:
	enum TravType {NONE, PRE, POST, IN, LEVEL};
	class Node
	{
	public:
		DataType data;

		Node *parent = NULL;
		Node *lchild = NULL;
		Node *rchild = NULL;

		Node *next = NULL;
		Node *prev = NULL;
	
	public:
		Node(){}
		Node(const DataType& _data, Node *_parent = NULL, Node *_lchild = NULL, Node *_rchild = NULL) :
		data(_data), parent(_parent), lchild(_lchild), rchild(_rchild){}
		~Node(){parent = NULL; lchild = NULL; rchild = NULL;}
		int size()const;
		int height()const;
		int level()const;
		bool isleaf()const;
		bool isroot()const;
		bool islchild()const;
		bool isrchild()const;
		Node* brother()const;
		bool belong_to(const BinTree<DataType>& tree)const;
		Node* insert_lchild(const DataType& value);
		Node* insert_rchild(const DataType& value);
	};

	class iterator
	{
	private:
		Node* _ptr = NULL;

	public:
		iterator(){}
		iterator(Node* ptr) : _ptr(ptr){}
		iterator& operator =(Node* ptr);
		iterator& operator ++();
	    iterator operator ++(int);
	    iterator& operator --();
	    iterator operator --(int);
		bool operator ==(Node* ptr){return _ptr == ptr;}
		bool operator ==(const iterator& it){return it._ptr == _ptr;}
		bool operator !=(Node* ptr){return _ptr != ptr;}
		bool operator !=(const iterator& it){return it._ptr != _ptr;}
		Node* ptr()const{return _ptr;}
		DataType& operator *(){return _ptr->data;}
	};

private:
	Node *_root = NULL;
	int _size = 0;

	iterator _begin = iterator(NULL);
	iterator _rear = iterator(NULL);
	iterator _end = iterator(NULL);

private:
	static Node* new_Node(const DataType& value,
						  Node* parent = NULL,
						  Node* lchild = NULL,
						  Node* rchild = NULL); // finished
	void copy(BinTree<DataType>& dest_tree, const BinTree<DataType>& src_tree); // finished

	static Node* trav_left_branch(Node* node, Stack<Node*>& stack);
	void trav_pre();

	static void gotoHLVFL(Stack<Node*>& stack);
	void trav_post();

	static Node* goto_most_left(Node* node, Stack<Node*>& stack);
	void trav_in();

	void trav_level();

public:
	BinTree(){}
	BinTree(const BinTree<DataType>& tree); // finished
	BinTree(const Tree<DataType>& tree); // finished
	BinTree(const Forest<DataType>& forest); // finished
	~BinTree();

	BinTree<DataType>& operator =(const BinTree<DataType>& tree); // finished
	BinTree<DataType>& operator =(const Tree<DataType>& tree); // finished
	BinTree<DataType>& operator =(const Forest<DataType>& forest); // finished

	void clear();
	int size()const;
	int height()const;
	bool empty()const;
	bool has_node(const Node& node)const;
	bool has_node(Node* node)const;
	Node* root()const;

	Node* insert_root(const DataType& value);
	Node* insert_lchild(Node* node, const DataType& value);
	Node* insert_rchild(Node* node, const DataType& value);
	Node* attach_lchild(Node* node, const BinTree<DataType>& tree);
	Node* attach_rchild(Node* node, const BinTree<DataType>& tree);
	int remove(Node* node);
	BinTree<DataType>& secede(Node* node);
	static BinTree<DataType>& subtree(Node* node);
	void show(const string& filename = "BinTree")const;
	void write(const string& filename)const;

	void trav_method(TravType method);
	iterator begin()const;
	iterator rear()const;
	iterator end()const;
};

#include "bintree.cpp"
#endif