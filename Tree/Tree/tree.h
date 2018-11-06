#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>

#include <list.h>
#include <bintree.h>

using namespace std;

template<class DataType>
class BinTree;

template<class DataType>
class Forest;

template<class DataType>
class Tree
{
	template<class ElemType>
	friend class BinTree;

	template<class ElemType>
	friend class Forest;

public:
	enum TravType {PRE, POST, LEVEL};

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

	template<class ElemType>
	static void check_ptr(const ElemType* ptr);

public:
	void write_part1(Stack<Node*>& stack_node2, Stack<int>& stack_number2, int n, ofstream& file)const;
	void write_part2(Stack<Node*>& stack_node2, Stack<int>& stack_number2, ofstream& file)const;
	void write_content_part2(Stack<Node*>& stack_node2, Stack<int>& stack_number2, ofstream& file)const;

public:
	Tree(){}
	Tree(const Tree<DataType>& tree);
	Tree(Tree<DataType>&& tree);
	Tree(const BinTree<DataType>& bintree);
	~Tree();
	
	Tree<DataType>& operator =(const Tree<DataType>& tree);
	Tree<DataType>& operator =(Tree<DataType>&& tree);
	Tree<DataType>& operator =(const BinTree<DataType>& bintree);

	void copy_from(const Tree<DataType>& tree);
	void clear();
	int size()const{return _size;}
	int height()const{return height(_root);}
	bool empty()const{return !_root;}
	bool has_node(const Node& node)const;
	bool has_node(Node* node)const;
	Node* root()const{return _root;}

	Node* insert_root(const DataType& value);
	Node* append_child(Node* node, const DataType& value);
	Node* insert_child(Node* node, int i, const DataType& value);
	Node* attach(Node* node, const Tree<DataType>& tree);
	Node* attach(Node* node, int i, const Tree<DataType>& tree);

	int remove(Node* node);
	Tree<DataType> secede(Node* node);
	Tree<DataType> subtree(Node* node);

	void show(const string& filename = "Tree")const;
	void show_content(const string& filename = "Tree")const;
	void write(const string& filename)const;
	void write_content(const string& filename)const;

	static int size(const Node* node);
	static int height(const Node* node);
	static int depth(const Node* node);
	static bool isleaf(const Node* node);
	static bool isroot(const Node* node);
};

template<class DataType>
class Forest: public List< Tree<DataType> >
{
	template<class ElemType>
	friend class Tree;

	template<class ElemType>
	friend class BinTree;
	
public:
	Forest() : List< Tree<DataType> >() {}
	Forest(const Forest<DataType>& forest) : List< Tree<DataType> >(forest) {}
	Forest(int n, const Tree<DataType>& tree) : List< Tree<DataType> >(n, tree) {}
	Forest(int n) : List< Tree<DataType> >(n) {}
	Forest(const BinTree<DataType>& bintree);

	Forest<DataType>& operator =(const BinTree<DataType>& bintree);

	void show(const string& filename = "Forest")const;
	void show_content(const string& filename = "Forest")const;
	void write(const string& filename)const;
	void write_content(const string& filename)const;
};

#include <tree.cpp>
#endif