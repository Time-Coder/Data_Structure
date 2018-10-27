#include <sort.h>

int main()
{
	Vector<int> v = int_rand(0, 20, 20);
	cout << "Before sort: " << v << endl;
	count_sort(v);
	cout << "After  sort: " << v << endl;
	
	return 0;
}