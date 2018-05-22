#include <sortlink.h>

int main()
{
	// 定义一个用于存储 double 的有序链表
	SortLink<double> X1;

	// 使用 insert 将元素插入到有序链表相应位置（由大到小排列）
	X1.insert(7);
	X1.insert(4);
	X1.insert(6);
	X1.insert(5.3);
	X1.insert(6.32);
	X1.insert(4.58);
	X1.insert(6.32);

	// 使用 cout 打印链表结构
	cout << "X1 = " << X1 << endl;

	// 调用拷贝构造函数定义一个新链表 X2，并用 X1 初始化它
	SortLink<double> X2 = X1;

	cout << "X2 = " << X2 << endl;

	SortLink<double> X3;

	// 使用 empty 函数判断链表是否为空
	if(X3.empty())
	{
		cout << "赋值前，X3 为空链表" << endl;
	}

	// 使用 "=" 拷贝 X2 给空链表 X3
	X3 = X2;

	if(!X3.empty())
	{
		cout << "赋值后，X3 = " << endl << endl;
	}
	
	// 使用只读迭代器 const_iterator 遍历链表中的所有元素
	for(SortLink<double>::const_iterator it = X3.begin(); it != X3.end(); it++)
	{
		cout << *it << endl;
	}

	// 使用 erase(int) 擦除链表中指定位置的元素(用索引指定位置)
	X3.erase(4);
	cout << "X3 擦除第 4 个元素(从 0 开始计数)后变为：" << X3 << endl;

	SortLink<double>::const_iterator it = X3.begin();

	// 使用 erase(const_iterator) 擦除链表中指定位置的元素(用迭代器指定位置)
	X3.erase(it);
	cout << "X3 再擦除第 0 个元素后变为：" << X3 << endl;

	// 使用 length 获取链表长度
	cout << "X3 的长度为：" << X3.length() << endl;

	double x = 7.65;
	cout << "在 X3 中寻找 "<< x << "..." << endl;

	// 使用 find 寻找特定元素在链表中的位置(用迭代器标记位置)
	it = X3.find(x);
	if(!it.empty())
	{
		cout << "元素 " << x << " 位置在 X3 的第 " << X3.locate(it) << " 位上" << endl;
	}
	else
	{
		cout << "在 X3 中没有找到 " << x << endl;
	}

	double y = 6.32;
	cout << "在 X3 中寻找 " << y << "..." << endl;
	it = X3.find(y);
	if(!it.empty())
	{
		cout << "元素 " << y << " 位置在 X3 的第 " << X3.locate(it) << " 位上" << endl;
	}
	else
	{
		cout << "在 X3 中没有找到 " << y << endl;
	}

	SortLink<double> X4;
	X4.insert(3.27);
	X4.insert(8.16);
	X4.insert(864);
	X4.insert(2.04);
	X4.insert(7.31);
	X4.insert(0.96);
	X4.insert(7.28);
	cout << "再次新建一个新的链表 X4 = " << X4 << endl;

	// 使用 merge 让 X4 与 X3 融合
	cout << "使 X4 与 X3 融合之后得到新链表：" << X4.merge(X3) << endl;

	return 0;
}