#include <heap.h>

int main()
{
	Vector<int> v = int_rand(0, 10, 20);
	Heap<int>::heapify(v);
	cout << Heap<int>::isheap(v) << endl;
	cout << v << endl;
	Heap<int>::insert(v, 7);
	cout << v << endl;
	cout << Heap<int>::isheap(v) << endl;
	return 0;
}