#ifndef REDBLACK_H
#define REDBLACK_H

#include <bst.h>

template<class KeyType>
class RedBlack : public BST<KeyType>
{
private:
	static typename BinTree<KeyType>::Node* red_child(typename BinTree<KeyType>::Node* node);

protected:
	void update_height(typename BinTree<KeyType>::Node* node);
	void solve_red2(typename BinTree<KeyType>::Node* node);
	void solve_black2(typename BinTree<KeyType>::Node* node);
	static bool is_red(typename BinTree<KeyType>::Node* node);
	static bool is_black(typename BinTree<KeyType>::Node* node);

public:
	enum Color {NONE, BLACK, RED};
	typename BinTree<KeyType>::Node* insert(const KeyType& key);
	typename BinTree<KeyType>::Node* remove(const KeyType& key);
};

#include <redblack.cpp>
#endif