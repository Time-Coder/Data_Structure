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

	tree.show("Origine");
	cout << tree.remove(node_B2) << endl;
	tree.show("Current1");
	tree.attach(node_C12, tree);
	tree.show("Current2");

	cout << node_C12->level() << endl;

	Forest<string> forest;
	forest.push_back(tree);

	return 0;
}