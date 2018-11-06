#include <redblack.h>
#include <time.h>

int main()
{
	RedBlack<int> redblack_tree;
	
	redblack_tree.insert(6);
	redblack_tree.insert(9);
	redblack_tree.insert(11);
	redblack_tree.insert(26);
	redblack_tree.insert(3);
	redblack_tree.insert(10);
	redblack_tree.insert(7);
	redblack_tree.insert(22);
	redblack_tree.insert(20);
	redblack_tree.insert(17);
	redblack_tree.insert(13);
	redblack_tree.insert(5);
	redblack_tree.insert(0);
	redblack_tree.insert(1);
	redblack_tree.insert(10);
	redblack_tree.insert(4);
	redblack_tree.insert(3);
	redblack_tree.insert(9);
	redblack_tree.insert(2);
	redblack_tree.insert(15);
	redblack_tree.insert(5);
	redblack_tree.insert(7);

	redblack_tree.remove(22);
	redblack_tree.remove(11);
	redblack_tree.remove(6);
	redblack_tree.remove(13);
	redblack_tree.remove(7);
	redblack_tree.remove(26);
	redblack_tree.remove(17);
	redblack_tree.remove(20);
	redblack_tree.remove(9);
	redblack_tree.remove(15);
	redblack_tree.remove(0);
	redblack_tree.remove(5);
	redblack_tree.remove(4);
	redblack_tree.remove(10);
	redblack_tree.remove(1);
	redblack_tree.remove(2);
	redblack_tree.remove(3);

	// redblack_tree.remove(3);

	redblack_tree.show();

	return 0;
}