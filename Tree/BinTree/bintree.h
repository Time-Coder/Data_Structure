#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <direct.h>

#include <stack.h>
#include <queue.h>
#include <tree.h>

using namespace std;

#define is_ptr(type) (is_pointer<type>::value)
#define type_equal(type1, type2) ( is_same<type1, type2>::value )

template<class DataType>
class Tree;

template<class DataType>
class Forest;

template<class DataType>
class BinTree
{
	template<class ElemType>
	friend class Tree;

	template<class ElemType>
	friend class Forest;

public:
	enum TravType {NONE, PRE, POST, IN1, IN2, IN, LEVEL};
	class Node
	{
	public:
		DataType data;

		int height = 0;
		int color = 0;

		Node *parent = NULL;
		Node *lchild = NULL;
		Node *rchild = NULL;

		Node *next = NULL;
		Node *prev = NULL;

		int x0 = 0;
		int y0 = 0;
	
	public:
		Node(){}
		Node(const DataType& _data,
			 int _height = 0,
			 Node *_parent = NULL,
			 Node *_lchild = NULL,
			 Node *_rchild = NULL) :
		data(_data), height(_height), parent(_parent), lchild(_lchild), rchild(_rchild){}
		~Node(){height = 0; parent = NULL; lchild = NULL; rchild = NULL; next = NULL; prev = NULL;}
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
		DataType& operator  *(){return _ptr->data;}
		DataType* operator ->(){return &(_ptr->data);}
	};

protected:
	Node *_root = NULL;
	int _size = 0;

	iterator _begin = iterator(NULL);
	iterator _rear = iterator(NULL);
	iterator _end = iterator(NULL);

protected:
	static Node* new_Node(const DataType& value,
						  int height = 0,
						  Node* parent = NULL,
						  Node* lchild = NULL,
						  Node* rchild = NULL); // finished
	void copy(BinTree<DataType>& dest_tree, const BinTree<DataType>& src_tree); // finished

	static Node* trav_left_branch(Node* node, Stack<Node*>& stack);
	void trav_pre();

	static void gotoHLVFL(Stack<Node*>& stack);
	void trav_post();

	static Node* goto_most_left(Node* node, Stack<Node*>& stack);
	void trav_in1();
	void trav_in2();

	void trav_level();

	static int height(const Node* node);
	static void update_height(Node* node);
	static void update_height_above(Node* node);
	static void update_height_below(Node* node);

	template<class ElemType>
	static void check_ptr(const ElemType* ptr);
	void check_node(const Node* node, const char* function_name);

	template<class ElemType>
	static void circle(ofstream& file, int x0, int y0, const ElemType& label, const string& face_color, const string& font_color);
	static void connect(ofstream& file, int x1, int y1, int x2, int y2);

public:
	BinTree(){}
	BinTree(const BinTree<DataType>& bintree);
	BinTree(BinTree<DataType>&& bintree);
	BinTree(const Tree<DataType>& tree);
	BinTree(const Forest<DataType>& forest);
	~BinTree();

	template<class ElemType>
	BinTree(const Forest<ElemType>* forest);
	template<class ElemType>
	BinTree(const Tree<ElemType>* tree);

	BinTree<DataType>& operator =(const BinTree<DataType>& bintree);
	BinTree<DataType>& operator =(BinTree<DataType>&& bintree);
	BinTree<DataType>& operator =(const Tree<DataType>& tree);
	BinTree<DataType>& operator =(const Forest<DataType>& forest);

	template<class ElemType>
	BinTree<DataType>& operator =(const Tree<ElemType>* tree);
	template<class ElemType>
	BinTree<DataType>& operator =(const Forest<ElemType>* forest);

	void copy_from(const BinTree<DataType>& bintree);

	void clear();
	int size()const;
	int height()const;
	bool empty()const;
	bool has_node(const Node& node)const;
	bool has_node(const Node* node)const;
	Node* root()const;

	Node* insert_root(const DataType& value);
	Node* insert_lchild(Node* node, const DataType& value);
	Node* insert_rchild(Node* node, const DataType& value);
	Node* attach_lchild(Node* node, const BinTree<DataType>& tree);
	Node* attach_rchild(Node* node, const BinTree<DataType>& tree);
	int remove(Node* node);
	BinTree<DataType> secede(Node* node);
	static BinTree<DataType> subtree(Node* node);

	void show(const string& title = "Tree");
	void show_content(const string& title = "Tree");

	void trav_method(TravType method);
	iterator begin()const;
	iterator rear()const;
	iterator end()const;

	static int size(const Node* node);
	static int depth(const Node* node);
	static bool isleaf(const Node* node);
	static bool isroot(const Node* node);
	static bool islchild(const Node* node);
	static bool isrchild(const Node* node);
	Node*& branch(Node*& node);
	static Node*& brother(Node*& node);
};

#include <bintree.cpp>
#endif