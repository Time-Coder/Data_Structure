#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>

#include <list.h>
#include <stack.h>

using namespace std;

template<class DataType>
class Tree
{
public:
	class Node
	{
	public:
		DataType data;
		Node* parent = NULL;
		List<Node*> children;

	public:
		Node(){} // finished, tested
		Node(const DataType& _data, Node *_parent = NULL) :
		data(_data), parent(_parent){} // finished, tested
		~Node(){parent = NULL;} // finished, tested
		int size()const; // finished, tested
		int height()const; // finished, tested
		int level()const; // finished, tested
		bool isleaf()const; // finished, tested
		bool isroot()const; // finished, tested
		bool belong_to(const Tree<DataType>& tree)const; // finished, tested
		Node* append_child(const DataType& value); // finished, tested
		Node* insert_child(int i, const DataType& value); // finished, tested
	};

private:
	Node* _root = NULL;
	int _size = 0;

private:
	static Node* new_Node(const DataType& value, Node* parent = NULL); // finished, tested
	bool bad_node(Node* node, const string& message, const string& function_name); // finished, tested

public:
	Tree(){} // finished, tested
	Tree(const Tree<DataType>& tree); // finished, tested
	~Tree(); // finished, tested

	void clear(); // finished, tested
	int size()const{return _size;} // finished
	int height()const{return _root->height();} // finished
	bool empty()const{return !_root;} // finished
	bool has_node(const Node& node)const{return node.belong_to(*this);} // finished
	bool has_node(Node* node)const{return node->belong_to(*this);} // finished
	Node* root()const{return _root;} // finished, tested

	Node* insert_root(const DataType& value); // finished, tested
	Node* append_child(Node* node, const DataType& value); // finished, tested
	Node* insert_child(Node* node, int i, const DataType& value); // finished, tested
	Node* attach(Node* node, const Tree<DataType>& tree); // finished, tested
	Node* attach(Node* node, int i, const Tree<DataType>& tree); // finished, tested

	int remove(Node* node); // finished, tested
	Tree<DataType>& secede(Node* node); // finished, tested
	Tree<DataType> subtree(Node* node); // finished, tested
	Tree<DataType>& operator =(const Tree<DataType>& tree); // finished, tested
	void show(const string& filename = "Tree")const; // finished, tested
	void write(const string& filename)const; // finished, tested
};

template<class DataType>
class Forest: public List< Tree<DataType> >{};

#include "tree.cpp"
#endif