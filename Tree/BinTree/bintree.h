#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <fstream>

#include <stack.h>
#include <queue.h>

using namespace std;

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
		Node(){} // tested
		Node(const DataType& _data, Node *_parent = NULL, Node *_lchild = NULL, Node *_rchild = NULL) :
		data(_data), parent(_parent), lchild(_lchild), rchild(_rchild){} // tested
		~Node(){parent = NULL; lchild = NULL; rchild = NULL;} // tested
		int size()const; // tested
		int height()const; // tested
		int level()const; // finished
		bool isleaf()const; // finished
		bool isroot()const; // finished
		bool islchild()const; // finished
		bool isrchild()const; // finished
		Node* brother()const; // finished
		bool belong_to(const BinTree<DataType>& tree)const; // finished
		Node* insert_lchild(const DataType& value); // finished
		Node* insert_rchild(const DataType& value); // finished
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
	BinTree(){} // finished
	BinTree(const BinTree<DataType>& tree); // finished
	~BinTree(); // finished

	void clear(); // finished
	int size()const; // finished
	int height()const; // finished
	bool empty()const; // finished
	bool has_node(const Node& node)const; // finished
	bool has_node(Node* node)const; // finished
	Node* root()const; // finished, tested

	Node* insert_root(const DataType& value); // finished, tested
	Node* insert_lchild(Node* node, const DataType& value); // finished, tested
	Node* insert_rchild(Node* node, const DataType& value); // finished, tested
	Node* attach_lchild(Node* node, const BinTree<DataType>& tree); // finished, tested
	Node* attach_rchild(Node* node, const BinTree<DataType>& tree); // finished, tested
	int remove(Node* node); // finished
	BinTree<DataType>& secede(Node* node); // finished
	static BinTree<DataType>& subtree(Node* node); // finished
	BinTree<DataType>& operator =(const BinTree<DataType>& tree); // finished
	void show(const string& filename = "temp.pdf")const; // finished
	void write(const string& filename)const; // finished

	void trav_method(TravType method);
	iterator begin()const; // finished
	iterator rear()const;
	iterator end()const; // finished
};

class BinForest : public List< BinTree<DataType> >{};

#include "bintree.cpp"
#endif