#include <bst.h>

int main()
{
	BST<int> bst;
	bst.insert(8);
	auto node2 = bst.insert(2);
	bst.insert(6);
	bst.insert(4);
	bst.insert(5);
	bst.insert(1);
	bst.insert(9);
	bst.insert(0);
	bst.insert(6);
	bst.remove(6);

	bst.show("1");

	// bst.zag(node2);

	// bst.show("2");

	return 0;
}