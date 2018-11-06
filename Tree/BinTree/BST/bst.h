#ifndef BST_H
#define BST_H

#include <bintree.h>

template<class KeyType>
class BST : public BinTree<KeyType>
{
protected:
	typename BinTree<KeyType>::Node* _hot = NULL;
	int color_removed;

public:
	void zig(typename BinTree<KeyType>::Node* node);
	void zag(typename BinTree<KeyType>::Node* node);
	typename BinTree<KeyType>::Node*
	connect34(typename BinTree<KeyType>::Node* a,
			  typename BinTree<KeyType>::Node* b,
			  typename BinTree<KeyType>::Node* c,
			  typename BinTree<KeyType>::Node* T0,
			  typename BinTree<KeyType>::Node* T1,
			  typename BinTree<KeyType>::Node* T2,
			  typename BinTree<KeyType>::Node* T3,
			  typename BinTree<KeyType>::Node* hole_parent,
			  typename BinTree<KeyType>::Node*& child_branch);
	typename BinTree<KeyType>::Node* rebalance(typename BinTree<KeyType>::Node* v,
											   typename BinTree<KeyType>::Node* p,
											   typename BinTree<KeyType>::Node* g);
	
public:
	virtual typename BinTree<KeyType>::Node*& search(const KeyType& key);
	virtual typename BinTree<KeyType>::Node* insert(const KeyType& key);
	virtual typename BinTree<KeyType>::Node* remove(const KeyType& key);
};

#include <bst.cpp>
#endif