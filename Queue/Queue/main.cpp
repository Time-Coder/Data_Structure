#include <queue.h>

int main()
{
	// 1. Creat a queue

	// 1.1 Creat an empty queue
	Queue<double> queue1;

	// 1.2 Creat a queue using initializer_list
	Queue<double> queue2 = {1.02, 2.43, 5.67, 2.38, 7.49};

	// 1.3 Creat a queue using length and data
	Queue<double> queue3(3, 7.83);

	// 1.4 Creat a queue using other queue
	Queue<double> queue4 = queue2;

	// 2. cout a queue
	cout << "queue1 = " << queue1 << endl;
	cout << "queue2 = " << queue2 << endl;
	cout << "queue3 = " << queue3 << endl;
	cout << "queue4 = " << queue4 << endl;

	// 3. assign queue to each other with operator "="
	queue4 = queue3;
	cout << "After assign queue3 to queue4, queue4 = " << queue4 << endl;

	// 4. using clear() to manually empty a queue
	queue4.clear();

	// 5. using empty() to judge if a queue is empty or not
	if(queue4.empty())
	{
		cout << "After clear, queue4 is empty now!" << endl;
	}

	// 6. Get the size of queue using size()
	cout << "The size of queue2 is " << queue2.size() << endl;

	// 7. Read the first element in queue using front()
	cout << "The front element of queue2 is " << queue2.front() << endl;

	// 8. Read the last element in queue using back()
	cout << "The last element of queue2 is " << queue2.back() << endl;

	// 9. Push an element on the end of queue using push(element)
	queue2.push(3.24);
	cout << "After pushing 3.24 to queue2, queue2 = " << queue2 << endl;

	// 10. Pop out the last element in queue using pop(element)
	cout << "After pop out the front element " << queue2.pop() << " in queue2, queue2 = " << queue2 << endl;

	return 0;
}
