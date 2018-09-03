#include <deque.h>

int main()
{
	// 1. Creat a deque

	// 1.1 Creat an empty deque
	Deque<double> deque1

	// 1.2 Creat a deque using initializer_list
	Deque<double> deque2 = {1.02, 2.43, 5.67, 2.38, 7.49};

	// 1.3 Creat a deque using length and data
	Deque<double> deque3(3, 7.83);

	// 1.4 Creat a deque using other deque
	Deque<double> deque4 = deque2;

	// 2. cout a deque
	cout << "deque1 = " << deque1 << endl;
	cout << "deque2 = " << deque2 << endl;
	cout << "deque3 = " << deque3 << endl;
	cout << "deque4 = " << deque4 << endl;

	// 3. assign deque to each other with operator "="
	deque4 = deque3;
	cout << "After assign deque3 to deque4, deque4 = " << deque4 << endl;

	// 4. using clear() to manually empty a deque
	deque4.clear();

	// 5. using empty() to judge if a deque is empty or not
	if(deque4.empty())
	{
		cout << "After clear, deque4 is empty now!" << endl;
	}

	// 6. Get the size of deque using size()
	cout << "The size of deque2 is " << deque2.size() << endl;

	// 7. Read the first element in deque using front()
	cout << "The front element of deque2 is " << deque2.front() << endl;

	// 8. Read the last element in deque using back()
	cout << "The last element of deque2 is " << deque2.back() << endl;

	// 9. Push an element on the back of deque using push_back(element)
	deque2.push_back(3.24);
	cout << "After pushing 3.24 to the back of deque2, deque2 = " << deque2 << endl;

	// 10. Push an element on the front of deque using push_front(element)
	deque2.push_front(6.28);
	cout << "After pushing 6.28 to the front of deque2, deque2 = " << deque2 << endl;

	// 11. Pop out the back element in deque using pop_back()
	cout << "After pop out the back element " << deque2.pop_back() << " in deque2, deque2 = " << deque2 << endl;

	// 12. Pop out the front element in deque using pop_front()
	cout << "After pop out the front element " << deque2.pop_front() << " in deque2, deque2 = " << deque2 << endl;

	return 0;
}
