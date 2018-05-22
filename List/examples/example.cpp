#include <circularlist.h>

int main()
{
	CircularList<double> list;
	list.push_back(20);
	list.push_back(10);
	list.push_back(7);
	list.push_front(0);
	cout << list << endl;
	list.swap(1,9);
	cout << list << endl;
	// cout << list.pop_front() << endl;
	// cout << list.pop_front() << endl;
	// cout << list.pop_front() << endl;
	// cout << list.empty() << endl;
}