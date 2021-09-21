#pragma once
#ifndef _MYARRAY_H_
#define _MYARRAY_H_

#include <iostream>

using namespace std;

/**
 * @brief	array template class
 */
template<class T>
class MyArray
{
public:
	MyArray(int capacity);
	~MyArray();

	// copy construct
	MyArray(const MyArray & arr);

	// 运算符重构
	MyArray& operator=(const MyArray& arr);

	// 尾插法
	void pushBack(const T& value);

	// 尾删法
	void popBack();

	// 按位置插入
	void posInsert(const int pos, const T & value);

	// 按位置删除
	void posDelete(const int pos);

	// 通过下标方式访问
	T& operator[](const int index);

	// 获取容量
	int getCapacity();

	// 获取大小
	int getSize();

private:
	T* m_pArray;		// array in heap area
	int m_capacity;		// the capacity of arrar
	int m_size;			// the size of array
};


#endif // !_MYARRAY_H_

template<class T>
MyArray<T>::MyArray(int capacity)
{
	this->m_capacity = capacity;
	this->m_size = 0;
	this->m_pArray = new T[this->m_capacity];
	cout << "构造函数" << endl;
}

template<class T>
MyArray<T>::~MyArray()
{
	if (this->m_pArray != NULL)
	{
		delete[] this->m_pArray;
		this->m_pArray = NULL;
		this->m_capacity = 0;
		this->m_size = 0;
		cout << "析构函数" << endl;
	}
}

template<class T>
MyArray<T>::MyArray(const MyArray & arr)
{
	this->m_capacity = arr.m_capacity;
	this->m_size = arr.m_size;

	// deep copy
	this->m_pArray = new T[this->m_capacity];

	// copy the value
	for (int i = 0; i < this->m_size; i++)
	{
		this->m_pArray[i] = arr.m_pArray[i];
	}

	cout << "拷贝构造函数" << endl;
}

template<class T>
MyArray<T>& MyArray<T>::operator=(const MyArray & arr)
{
	if (this->m_pArray != NULL)
	{
		delete[] this->m_pArray;
		this->m_capacity = 0;
		this->m_size = 0;
	}

	this->m_capacity = arr.m_capacity;
	this->m_size = arr.m_size;

	// deep copy
	this->m_pArray = new T[this->m_capacity];
	for (int i = 0; i < this->m_size; i++)
	{
		this->m_pArray[i] = arr.m_pArray[i];
	}

	cout << "operator=函数" << endl;

	return *this;
}

template<class T>
void MyArray<T>::pushBack(const T & value)
{
	// 容量不够时，开辟一倍容量
	if (this->m_size == this->m_capacity)
	{
		this->m_capacity *= 2;
		
		// deep copy
		T* temp = new T[this->m_capacity];
		for (int i = 0; i < this->m_size; i++)
		{
			temp[i] = this->m_pArray[i];
		}
		this->m_pArray = temp;
		/*delete[] this->m_pArray;
		this->m_pArray = new T[this->m_capacity];
		for (int i = 0; i < this->m_size; i++)
		{
			this->m_pArray[i] = temp[i];
		}
		delete[] temp;*/
	}
	
	// 插入元素
	this->m_pArray[this->m_size] = value;
	this->m_size++;
}

template<class T>
void MyArray<T>::popBack()
{
	if (this->m_size == 0)
	{
		return;
	}
	// this->m_pArray[this->m_size] = NULL;
	this->m_size--;
}

template<class T>
void MyArray<T>::posInsert(const int pos, const T & value)
{
	// 如果pos超过size，默认尾插
	if (pos >= this->m_size)
	{
		this->pushBack(value);
	}
	else
	{
		// 检查大小是否超容量
		if (this->m_size == this->m_capacity)
		{
			// deep copy
			this->m_capacity *= 2;
			T* temp = new T[this->m_capacity];
			for (int i = 0; i < this->m_size; i++)
			{
				temp[i] = this->m_pArray[i];
			}
			this->m_pArray = temp;
			/*delete[] this->m_pArray;
			this->m_pArray = new T[this->m_capacity];
			for (int i = 0; i < this->m_size; i++)
			{
				this->m_pArray[i] = temp[i];
			}
			delete[] temp;*/
		}

		T* tempArr = new T[this->m_capacity];
		for (int i = 0; i < pos; i++)
		{
			tempArr[i] = this->m_pArray[i];
		}
		tempArr[pos] = value;
		for (int i = pos + 1; i < this->m_size + 1; i++)
		{
			tempArr[i] = this->m_pArray[i - 1];
		}
		this->m_pArray = tempArr;
		/*delete[] this->m_pArray;
		this->m_pArray = new T[this->m_capacity];
		for (int i = 0; i < this->m_size + 1; i++)
		{
			this->m_pArray[i] = tempArr[i];
		}
		delete[] tempArr;*/
		this->m_size++;
	}
}

template<class T>
void MyArray<T>::posDelete(const int pos)
{
	// 如果pos大于等于数组大小，默认尾删
	if (pos >= this->m_size)
	{
		popBack();
	}
	else
	{
		for (int i = pos; i < this->m_size - 1; i++)
		{
			this->m_pArray[i] = this->m_pArray[i + 1];
		}
		// this->m_pArray[this->m_size] = NULL;
		this->m_size--;
	}
}

template<class T>
T & MyArray<T>::operator[](const int index)
{
	// TODO: 越界处理
	/*if (index >= this->m_size)
	{
		cout << "out of memory." << endl;
		T temp;
		return temp;
	}*/
	return this->m_pArray[index];
}

template<class T>
int MyArray<T>::getCapacity()
{
	return this->m_capacity;
}

template<class T>
int MyArray<T>::getSize()
{
	return m_size;
}
