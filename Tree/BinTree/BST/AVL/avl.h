#ifndef AVL_H
#define AVL_H

#include <bst.h>

template<class KeyType>
class AVL : public BST<KeyType>
{
private:
	int balance_factor(typename BinTree<KeyType>::Node* node);
	bool balanced(typename BinTree<KeyType>::Node* node);
	typename BinTree<KeyType>::Node* taller_child(typename BinTree<KeyType>::Node* node);
	
public:
	typename BinTree<KeyType>::Node* insert(const KeyType& key);
	typename BinTree<KeyType>::Node* remove(const KeyType& key);
};

#include <avl.cpp>
#endif