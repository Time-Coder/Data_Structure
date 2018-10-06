#include "list.h"

int main()
{
	List<int> list;
	list.push_back(4);
	list.push_back(7);
	list.push_back(6);
	list.push_back(3);
	list.push_back(6);

	list.erase(0);
	list.erase(3);
	for(List<int>::iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << "->";
	}

	return 0;
}