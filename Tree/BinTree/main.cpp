#include <bintree.h>

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
	tree.show();
	Forest<char> forest(tree);
	forest.show();
	// tree.trav_method(BinTree<char>::IN);
	// for(BinTree<char>::iterator it = tree.rear(); it != tree.end(); it--)
	// {
	// 	cout << *it << "->";
	// }
	// cout << endl;

	// Tree<int> tree;
	// auto node1 = tree.insert_root(1);
	// auto node2 = tree.append_child(node1, 2);
	// tree.append_child(node1, 3);
	// auto node4 = tree.append_child(node1, 4);
	// tree.append_child(node2, 5);
	// tree.append_child(node2, 6);
	// tree.append_child(node4, 7);
	// tree.show();

	// BinTree<int> bintree = tree;
	// bintree.show();

	// Tree<char> tree1;
	// auto node = tree1.insert_root('A');
	// tree1.append_child(node, 'B');
	// tree1.append_child(node, 'C');
	// tree1.append_child(node, 'D');

	// Tree<char> tree2;
	// node = tree2.insert_root('E');
	// tree2.append_child(node, 'F');

	// Tree<char> tree3;
	// node = tree3.insert_root('G');
	// auto node_H = tree3.append_child(node, 'H');
	// tree3.append_child(node, 'I');
	// tree3.append_child(node_H, 'J');

	// Forest<char> forest;
	// forest.push_back(tree1);
	// forest.push_back(tree2);
	// forest.push_back(tree3);

	BinTree<char> bintree = forest;
	bintree.show();

	return 0;
}