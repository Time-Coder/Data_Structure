#include <bintree.h>

int main()
{
	BinTree<char> bintree;
	bintree.insert_root('i');
	BinTree<char>::Node* node = bintree.insert_lchild(bintree.root(), 'd');
	node = bintree.insert_lchild(node, 'c');
	node = bintree.insert_lchild(node, 'a');
	node = bintree.insert_rchild(node, 'b');
	node = bintree.root()->lchild;
	node = bintree.insert_rchild(node, 'h');
	node = bintree.insert_lchild(node, 'f');
	node = bintree.insert_lchild(node, 'e');
	bintree.insert_rchild(node->parent, 'g');
	node = bintree.insert_rchild(bintree.root(), 'l');
	node = bintree.insert_lchild(node, 'k');
	node = bintree.insert_lchild(node, 'j');
	node = bintree.root()->rchild;
	node = bintree.insert_rchild(node, 'n');
	node = bintree.insert_lchild(node, 'm');
	node = node->parent;
	node = bintree.insert_rchild(node, 'p');
	node = bintree.insert_lchild(node, 'o');
	
	bintree.remove(bintree.root()->rchild);
	bintree.show();
	Tree<char> tree = bintree;
	tree.show();
	BinTree<char> bintree1 = tree;
	bintree1.show("BinTree1");
	// tree.show();
	// bintree.trav_method(BinTree<char>::IN);
	// for(BinTree<char>::iterator it = bintree.rear(); it != bintree.end(); it--)
	// {
	// 	cout << *it << "->";
	// }
	// cout << endl;

	// Tree<int> bintree;
	// auto node1 = bintree.insert_root(1);
	// auto node2 = bintree.append_child(node1, 2);
	// bintree.append_child(node1, 3);
	// auto node4 = bintree.append_child(node1, 4);
	// bintree.append_child(node2, 5);
	// bintree.append_child(node2, 6);
	// bintree.append_child(node4, 7);
	// bintree.show();

	// BinTree<int> binbintree = bintree;
	// binbintree.show();

	// Tree<char> bintree1;
	// auto node = bintree1.insert_root('A');
	// bintree1.append_child(node, 'B');
	// bintree1.append_child(node, 'C');
	// bintree1.append_child(node, 'D');

	// Tree<char> bintree2;
	// node = bintree2.insert_root('E');
	// bintree2.append_child(node, 'F');

	// Tree<char> bintree3;
	// node = bintree3.insert_root('G');
	// auto node_H = bintree3.append_child(node, 'H');
	// bintree3.append_child(node, 'I');
	// bintree3.append_child(node_H, 'J');

	// Forest<char> forest;
	// forest.push_back(bintree1);
	// forest.push_back(bintree2);
	// forest.push_back(bintree3);

	// Tree<char> tree = forest;
	// tree.show();

	return 0;
}