#include <sortlist.h>

int main()
{
	SortList<int> list;
	list.insert(4);
	list.insert(6);
	list.insert(2);
	list.insert(4);
	list.insert(3);
	
	cout << list << endl;

	return 0;
}