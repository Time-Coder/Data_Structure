#include "bintree.h"

int main()
{
	BinTree<char> tree;
	tree.insert_root('A');
	BinTree<char>::Node* node = tree.insert_lchild(tree.root(), 'B');
	tree.insert_lchild(node, 'K');
	tree.insert_rchild(node, 'L');

	node = tree.insert_rchild(tree.root(), 'C');
	tree.insert_rchild(node, 'F');
	tree.attach_lchild(node, tree);
	tree.show("Origine");
	cout << tree.size() << endl;

	BinTree<char> subtree = tree.secede(node);
	tree.show("Current");
	cout << tree.size() << endl;
	subtree.show("Subtree");
	cout << subtree.size() << endl;
	
	return 0;
}