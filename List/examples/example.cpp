#include <circlist.h>

int main()
{
	cout << "1. Creat an empty \'list1\'" << endl;
	CircList<int> list1;
	cout << "list1 = " << list1 << endl;

	cout << "2. Creat \'list2\' with length 5" << endl;
	CircList<int> list2(5);
	cout << "list2 = " << list2 << endl;

	cout << "3. Creat \'list3\' with length 5 and value 0" << endl;
	CircList<int> list3(5, 0);
	cout << "list3 = " << list3 << endl;

	cout << "4. Creat \'list4\' and initialize it with \'list3\'" << endl;
	CircList<int> list4 = list3;
	cout << "list4 = " << list4 << endl;

	cout << "5. Use clear() to clear \'list2\'" << endl;
	list2.clear();
	cout << "list2 = " << list2 << endl;

	cout << "6. Use push_back() add element 1 and 5 to \'list1\'" << endl;
	list1.push_back(1);
	list1.push_back(5);
	cout << "list1 = " << list1 << endl;

	cout << "7. Use push_front() add element 12 and 23 to \'list1\'" << endl;
	list1.push_front(12);
	list1.push_front(23);
	cout << "list1 = " << list1 << endl;

	cout << "8. Use \'=\' copy \'list1\' to \'list3\'" << endl;
	list3 = list1;
	cout << "list3 = " << list3 << endl;

	cout << "9. Use \'pop_back()\' to remove the last element of \'list3\'" << endl;
	int e = list3.pop_back();
	cout << "After remove the last element \'" << e << "\' of \'list3\', \'list3\' becomes:" << endl;
	cout << "list3 = " << list3 << endl;

	cout << "10. Use \'pop_front()\' to remove the first element of \'list3\'" << endl;
	e = list3.pop_front();
	cout << "After remove the first element \'" << e << "\' of \'list3\', \'list3\' becomes:" << endl;
	cout << "list3 = " << list3 << endl;

	cout << "11. Use \'size()\' to get the length of \'list3\'" << endl;
	cout << "length of list3 is: " << list3.size() << endl << endl;

	cout << "12. Use \'empty()\' to judge if list3 is empty or not" << endl;
	if(list3.empty())
	{
		cout << "list3 is empty now!" << endl << endl;
	}
	else
	{
		cout << "list3 is not empty." << endl;
	}
	list3.clear();
	cout << "After clear list3, ";
	if(list3.empty())
	{
		cout << "list3 is empty now!" << endl << endl;
	}
	else
	{
		cout << "list3 is not empty." << endl;
	}

	cout << "13. Use [] to get value of list1" << endl;
	for(int i = 0; i < list1.size(); i++)
	{
		cout << "list1[" << i << "] = " << list1[i] << endl;
	}
	cout << endl;

	cout << "14. Use [] to set value of list1" << endl;
	for(int i = 0; i < list1.size(); i++)
	{
		cout << "set list1[" << i << "] = " << (list1[i] = i*i) << endl;
	}
	cout << "now list1 becomes:" << endl;
	cout << "list1 = " << list1 << endl;

	cout << "15. Use erase(int) to the element in list1 whose index is 2" << endl;
	list1.erase(2);
	cout << "list1 = " << list1 << endl;

	cout << "16. Use insert(2, 12) to insert element 12 to index 2" << endl;
	list1.insert(2, 12);
	cout << "list1 = " << list1 << endl;

	cout << "17. Use swap(0, 3) to swap the elements with index 0 and index 3" << endl;
	list1.swap(0, 3);
	cout << "list1 = " << list1 << endl;
	
	cout << "18. Use const_iterator to cout all elements in list1" << endl;
	int i = 0;
	for(CircList<int>::const_iterator it = list1.begin(); i < list1.size(); i++, it++)
	{
		cout << (*it) << endl;
	}
	cout << endl;

	cout << "19. Use iterator to assign value to all elements of list1" << endl;
	i = 0;
	for(CircList<int>::iterator it = list1.begin(); i < list1.size(); i++, it++)
	{
		*it = i;
	}
	cout << "list1 = " << list1 << endl;

	cout << "20. list4 catch list1 on the right side:" << endl;
	cout << "list4 = " << list4.cat(list1) << endl;
}