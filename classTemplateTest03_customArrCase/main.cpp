#include "MyArray.hpp"
#include "Person.h"

#include <iostream>

/**
 * @brief	内置数据类型输出
 */
template<typename T>
void printArray(MyArray<T>& arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i] << endl;
	}
	cout << endl;
}

/**
 * @brief	内置数据类型测试
 */
void test01() 
{
	MyArray<int> arr1(5);

	MyArray<int> arr2(arr1);

	MyArray<int> arr3(6);
	arr3 = arr1;
}

/**
 * @brief	内置数据类型测试
 */

void test02()
{
	MyArray<int> arr2(5);
	for (int i = 0; i < 5; i++)
	{
		arr2.pushBack(i);
	}

	MyArray<char> arr3(5);
	for (int i = 0; i < 5; i++)
	{
		arr3.pushBack('a' + i);
	}

	printArray(arr2);
	cout << "arr2 capacity: " << arr2.getCapacity() << "\tarr2 size: " << arr2.getSize() << endl;
	printArray(arr3);
	cout << "arr3 capacity: " << arr3.getCapacity() << "\tarr3 size: " << arr3.getSize() << endl;

	// 尾删测试
	arr2.popBack();
	printArray(arr2);
	cout << "arr2 capacity: " << arr2.getCapacity() << "\tarr2 size: " << arr2.getSize() << endl;

	// 按位置插入
	arr3.posInsert(3, 'a' + 5);
	printArray(arr3);
	cout << "arr3 capacity: " << arr3.getCapacity() << "\tarr3 size: " << arr3.getSize() << endl;

	// 按位置删除
	arr3.posDelete(3);
	printArray(arr3);
	cout << "arr3 capacity: " << arr3.getCapacity() << "\tarr3 size: " << arr3.getSize() << endl;
}

/**
 * @brief	自定义数据类型测试
 */
void test03()
{
	MyArray<Person> arr(10);

	Person p1("张三", 10);
	Person p2("李四", 20);
	Person p3("王五", 30);
	Person p4("赵六", 40);
	Person p5("孙七", 50);

	// 尾插
	arr.pushBack(p1);
	arr.pushBack(p2);
	arr.pushBack(p3);
	arr.pushBack(p4);
	arr.pushBack(p5);

	// 输出
	printArray(arr);
	cout << "arr capacity: " << arr.getCapacity() << "\tarr size: " << arr.getSize() << endl;

	// 尾删
	arr.popBack();
	cout << "尾删后数据" << endl;
	printArray(arr);
	cout << "arr capacity: " << arr.getCapacity() << "\tarr size: " << arr.getSize() << endl;

	// 指定位置插入
	Person p6("钱八", 60);
	arr.posInsert(7, p6);
	cout << "指定位置插入后数据" << endl;
	printArray(arr);
	cout << "arr capacity: " << arr.getCapacity() << "\tarr size: " << arr.getSize() << endl;

	// 指定位置删除
	arr.posDelete(3);
	cout << "指定位置删除后数据" << endl;
	printArray(arr);
	cout << "arr capacity: " << arr.getCapacity() << "\tarr size: " << arr.getSize() << endl;
}

int main(int argc, char** argv) 
{
	test01();

	test02();

	test03();

	system("pause");
	return 0;
}