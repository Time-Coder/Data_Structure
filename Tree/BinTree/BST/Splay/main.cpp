#include <splay.h>
#include <time.h>

int main()
{
	Splay<int> splay_tree;
	for(int i = 1; i <= 15; i++)
	{
		splay_tree.insert(i);
	}

	splay_tree.search(1);
	splay_tree.search(3);
	splay_tree.search(10);
	// splay_tree.show("2");
	splay_tree.remove(10);
	// splay_tree.show("3");
	splay_tree.insert(17);
	// splay_tree.show("4");
	splay_tree.insert(0);
	// splay_tree.show("5");
	splay_tree.search(13);
	splay_tree.search(7);
	splay_tree.search(5);
	splay_tree.search(9);
	splay_tree.search(2);
	splay_tree.show();

	return 0;
}