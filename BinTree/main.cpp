#include "bintree.h"

int main()
{
	BinTree<char> tree;
	tree.insert_root('i');
	BinTree<char>::Node* node = tree.insert_lchild(tree.root(), 'd');
	node = tree.insert_lchild(node, 'c');
	node = tree.insert_lchild(node, 'a');
	node = tree.insert_rchild(node, 'b');
	node = tree.root()->lchild;
	node = tree.insert_rchild(node, 'h');
	node = tree.insert_lchild(node, 'f');
	node = tree.insert_lchild(node, 'e');
	tree.insert_rchild(node->parent, 'g');
	node = tree.insert_rchild(tree.root(), 'l');
	node = tree.insert_lchild(node, 'k');
	node = tree.insert_lchild(node, 'j');
	node = tree.root()->rchild;
	node = tree.insert_rchild(node, 'n');
	node = tree.insert_lchild(node, 'm');
	node = node->parent;
	node = tree.insert_rchild(node, 'p');
	node = tree.insert_lchild(node, 'o');

	tree.trav_method(BinTree<char>::IN);
	for(BinTree<char>::iterator it = tree.rear(); it != tree.end(); it--)
	{
		cout << *it << "->";
	}
	cout << endl;
	return 0;
}