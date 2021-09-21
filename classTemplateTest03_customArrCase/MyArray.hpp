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

	// ������ع�
	MyArray& operator=(const MyArray& arr);

	// β�巨
	void pushBack(const T& value);

	// βɾ��
	void popBack();

	// ��λ�ò���
	void posInsert(const int pos, const T & value);

	// ��λ��ɾ��
	void posDelete(const int pos);

	// ͨ���±귽ʽ����
	T& operator[](const int index);

	// ��ȡ����
	int getCapacity();

	// ��ȡ��С
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
	cout << "���캯��" << endl;
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
		cout << "��������" << endl;
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

	cout << "�������캯��" << endl;
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

	cout << "operator=����" << endl;

	return *this;
}

template<class T>
void MyArray<T>::pushBack(const T & value)
{
	// ��������ʱ������һ������
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
	
	// ����Ԫ��
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
	// ���pos����size��Ĭ��β��
	if (pos >= this->m_size)
	{
		this->pushBack(value);
	}
	else
	{
		// ����С�Ƿ�����
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
	// ���pos���ڵ��������С��Ĭ��βɾ
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
	// TODO: Խ�紦��
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
