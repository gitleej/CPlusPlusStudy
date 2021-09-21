#include "MyArray.hpp"

#include <iostream>

/**
 * @brief	���������������
 */
template<typename T>
void printArray(MyArray<T>& arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

/**
 * @brief	�����������Ͳ���
 */
void test01() 
{
	MyArray<int> arr1(5);

	MyArray<int> arr2(arr1);

	MyArray<int> arr3(6);
	arr3 = arr1;
}

/**
 * @brief	�����������Ͳ���
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

	// βɾ����
	arr2.popBack();
	printArray(arr2);
	cout << "arr2 capacity: " << arr2.getCapacity() << "\tarr2 size: " << arr2.getSize() << endl;

	// ��λ�ò���
	arr3.posInsert(3, 'a' + 5);
	printArray(arr3);
	cout << "arr3 capacity: " << arr3.getCapacity() << "\tarr3 size: " << arr3.getSize() << endl;

	// ��λ��ɾ��
	arr3.posDelete(3);
	printArray(arr3);
	cout << "arr3 capacity: " << arr3.getCapacity() << "\tarr3 size: " << arr3.getSize() << endl;
}

int main(int argc, char** argv) 
{
	// test01();

	test02();

	system("pause");
	return 0;
}