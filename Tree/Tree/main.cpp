#include <tree.h>

using namespace std;

int main()
{
	Tree<string> tree;
	auto node_A = tree.insert_root("A1");
	auto node_B1 = tree.append_child(node_A, "B1");
	auto node_B2 = tree.append_child(node_A, "B2");
	auto node_B3 = tree.append_child(node_A, "B3");
	auto node_B4 = tree.append_child(node_A, "B4");
	tree.append_child(node_B1, "C1");
	tree.append_child(node_B1, "C2");
	tree.append_child(node_B1, "C3");
	tree.append_child(node_B2, "C4");
	tree.append_child(node_B2, "C5");
	tree.append_child(node_B2, "C6");
	tree.append_child(node_B3, "C7");
	tree.append_child(node_B3, "C8");
	tree.append_child(node_B3, "C9");
	tree.append_child(node_B4, "C10");
	tree.append_child(node_B4, "C11");
	auto node_C12 = tree.append_child(node_B4, "C12");

	BinTree<string> bintree = tree;
	BinTree<string*> bintree_ptr = tree.toBinTree();
	bintree.show("BinTree1");
	bintree_ptr.show("BinTree2");

	// tree.show("Origine");
	// cout << tree.remove(node_B2) << endl;
	// tree.show("Current1");
	// tree.attach(node_C12, tree);
	// tree.show("Current2");

	// cout << node_C12->level() << endl;

	// Forest<string> forest;
	// forest.push_back(tree);

	// BinTree<char> bintree;
	// auto node_A = bintree.insert_root('A');
	// auto node_B = bintree.insert_lchild(node_A, 'B');
	// auto node_E = bintree.insert_rchild(node_A, 'E');
	// auto node_C = bintree.insert_rchild(node_B, 'C');
	// bintree.insert_lchild(node_E, 'F');
	// bintree.insert_rchild(node_C, 'D');
	// auto node_G = bintree.insert_rchild(node_E, 'G');
	// auto node_H = bintree.insert_lchild(node_G, 'H');
	// bintree.insert_lchild(node_H, 'J');
	// bintree.insert_rchild(node_H, 'I');

	// bintree.show();
	// Forest<char> forest(bintree);
	// forest.show();
	// cout << forest[0].root()->children[2]->children.empty() << endl;
	// tree.show();

	return 0;
}