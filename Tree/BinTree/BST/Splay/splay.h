#ifndef SPLAY_H
#define SPLAY_H

#include <bst.h>

template<class KeyType>
class Splay : public BST<KeyType>
{
protected:
	void splay(typename BinTree<KeyType>::Node* node);

public:
	typename BinTree<KeyType>::Node*& search(const KeyType& key);
	typename BinTree<KeyType>::Node* insert(const KeyType& key);
	typename BinTree<KeyType>::Node* remove(const KeyType& key);
};

#include <splay.cpp>
#endif