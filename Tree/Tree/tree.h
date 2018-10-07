#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>

#include <list.h>
#include <stack.h>
#include <bintree.h>

using namespace std;

template<class DataType>
class BinTree;

template<class DataType>
class BinForest;

template<class DataType>
class Forest;

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
		Node(){}
		Node(const DataType& _data, Node *_parent = NULL) :
		data(_data), parent(_parent){}
		~Node(){parent = NULL;}
		int size()const;
		int height()const;
		int level()const;
		bool isleaf()const;
		bool isroot()const;
		bool belong_to(const Tree<DataType>& tree)const;
		Node* append_child(const DataType& value);
		Node* insert_child(int i, const DataType& value);
	};

private:
	Node* _root = NULL;
	int _size = 0;

private:
	static Node* new_Node(const DataType& value, Node* parent = NULL);
	bool bad_node(Node* node, const string& message, const string& function_name);

public:
	Tree(){}
	Tree(const Tree<DataType>& tree);
	Tree(const BinTree<DataType>& tree);
	Tree(const Forest<DataType>& forest);
	Tree(const BinForest<DataType>& forest);

	Tree<DataType>& operator =(const Tree<DataType>& tree);
	Tree<DataType>& operator =(const BinTree<DataType>& tree);
	Tree<DataType>& operator =(const Forest<DataType>& forest);
	Tree<DataType>& operator =(const BinForest<DataType>& forest);

	~Tree();

	void clear();
	int size()const{return _size;}
	int height()const{return _root->height();}
	bool empty()const{return !_root;}
	bool has_node(const Node& node)const{return node.belong_to(*this);}
	bool has_node(Node* node)const{return node->belong_to(*this);}
	Node* root()const{return _root;}

	Node* insert_root(const DataType& value);
	Node* append_child(Node* node, const DataType& value);
	Node* insert_child(Node* node, int i, const DataType& value);
	Node* attach(Node* node, const Tree<DataType>& tree);
	Node* attach(Node* node, int i, const Tree<DataType>& tree);

	int remove(Node* node);
	Tree<DataType>& secede(Node* node);
	Tree<DataType> subtree(Node* node);

	void show(const string& filename = "Tree")const;
	void write(const string& filename)const;
};

template<class DataType>
class Forest: public List< Tree<DataType> >
{
public:
	Forest() : List< Tree<DataType> >() {}
	Forest(const Forest<DataType>& forest) : List< Tree<DataType> >(forest) {}
	Forest(int n, const Tree<DataType>& tree) : List< Tree<DataType> >(n, tree) {}
	Forest(int n) : List< Tree<DataType> >(n) {}
	Forest(const BinForest<DataType>& forest);
	Forest(const Tree<DataType>& tree);
	Forest(const BinTree<DataType>& tree);

	Forest<DataType>& operator =(const BinForest<DataType>& forest);
	Forest<DataType>& operator =(const Tree<DataType>& tree);
	Forest<DataType>& operator =(const BinTree<DataType>& tree);
};

#include "tree.cpp"
#endif