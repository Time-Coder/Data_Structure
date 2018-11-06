#include <avl.h>
#include <time.h>
int main()
{
	AVL<int> avl_tree;
	// srand((unsigned)time(NULL));
	// for(int i = 0; i < 100; i++)
	// {
	// 	avl_tree.insert(rand()%30);
	// }
	avl_tree.insert(7);
	avl_tree.insert(5);
	avl_tree.insert(8);
	avl_tree.insert(3);
	avl_tree.insert(6);
	avl_tree.insert(4);
	avl_tree.insert(2);
	avl_tree.insert(0);
	avl_tree.insert(1);
	avl_tree.insert(10);
	avl_tree.insert(11);
	avl_tree.insert(30);
	avl_tree.insert(21);
	avl_tree.insert(28);
	avl_tree.insert(15);
	avl_tree.show("1");
	avl_tree.remove(5);
	avl_tree.show("2");

	return 0;
}