#include <bintree.h>

int main()
{
	// 二叉树的遍历测试
	// BinTree<char> bintree;
	// auto node_i = bintree.insert_root('i');
	// auto node_d = bintree.insert_lchild(node_i, 'd');
	// auto node_c = bintree.insert_lchild(node_d, 'c');
	// auto node_a = bintree.insert_lchild(node_c, 'a');
	// bintree.insert_rchild(node_a, 'b');
	// auto node_h = bintree.insert_rchild(node_d, 'h');
	// auto node_f = bintree.insert_lchild(node_h, 'f');
	// bintree.insert_lchild(node_f, 'e');
	// bintree.insert_rchild(node_f, 'g');
	// auto node_l = bintree.insert_rchild(node_i, 'l');
	// auto node_k = bintree.insert_lchild(node_l, 'k');
	// bintree.insert_lchild(node_k, 'j');
	// auto node_n = bintree.insert_rchild(node_l, 'n');
	// bintree.insert_lchild(node_n, 'm');
	// auto node_p = bintree.insert_rchild(node_n, 'p');
	// bintree.insert_lchild(node_p, 'o');
	// bintree.show();

	// bintree.trav_method(BinTree<char>::IN2);
	// for(auto it = bintree.begin(); it != bintree.end(); it++)
	// {
	// 	cout << *it << ", ";
	// }
	// cout << endl << node_h->height << endl;
	// auto subtree = bintree.secede(node_l);
	// cout << node_i->height << endl;
	// subtree.show("subtree");
	// cout << subtree.root()->height << endl;

	// bintree.remove(bintree.root()->rchild);
	// bintree.show();
	// Tree<char> tree = bintree;
	// tree.show();
	// BinTree<char> bintree1 = tree;
	// bintree1.show("BinTree1");
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

	// 森林转二叉树测试
	Tree<char> tree1;
	auto node = tree1.insert_root('A');
	tree1.append_child(node, 'B');
	tree1.append_child(node, 'C');
	tree1.append_child(node, 'D');

	Tree<char> tree2;
	node = tree2.insert_root('E');
	tree2.append_child(node, 'F');

	Tree<char> tree3;
	node = tree3.insert_root('G');
	auto node_H = tree3.append_child(node, 'H');
	tree3.append_child(node, 'I');
	tree3.append_child(node_H, 'J');

	Forest<char> forest;
	forest.push_back(tree1);
	forest.push_back(tree2);
	forest.push_back(tree3);

	BinTree<char> bintree;
	bintree = forest;
	bintree.show("T1");
	BinTree<char*> bintree_ptr = &forest;
	bintree.show("T2");
	forest.show("T3");
	bintree_ptr.show_content("Ptr");
	
	return 0;
}