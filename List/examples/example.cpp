#include <circlist.h>

int main()
{
	CircList<int> list1;
	list1.push_back(0);
	list1.push_back(2);
	list1.push_back(10);
	list1.push_back(7);
	list1.push_back(8);
	list1.push_back(3);
	list1.push_back(23);
	CircList<int> list2(5, 0);
	list1.cat(list2);
	cout << list1 << endl;
}