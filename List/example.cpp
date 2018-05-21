#include "list.h"

int main()
{
	List<double> list;
	list.push_back(7);
	list.push_back(3);
	list.push_back(2);
	cout << list.locate(2);
}