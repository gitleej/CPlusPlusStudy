#include <iostream>
#include <string.h>

typedef enum TypeUpOrDownEnum
{
	UP,			// ����
	DOWN,		// ����
}TypeUpOrDown;

using namespace std;

// �������ģ��
template<typename T> 
void myPrint(T arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// ��������ģ��
template<typename T>
void mySwap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

// ������ģ��
template<typename T>
void mySort(T arr[], int size, TypeUpOrDown upOrDown) {
	
	switch (upOrDown)
	{
	case UP: {
		for (int i = 0; i < size; i++) {
			int max = i;
			for (int j = i + 1; j < size; j++) {
				if (arr[max] < arr[j]) {
					max = j;
				}
			}
			// ����
			if (max != i) {
				mySwap(arr[i], arr[max]);
			}
		};
		break;
	}
	case DOWN: {
		for (int i = 0; i < size; i++) {
			int min = i;
			for (int j = i + 1; j < size; j++) {
				if (arr[min] > arr[j]) {
					min = j;
				}
			}
			// ����
			if (min != i) {
				mySwap(arr[i], arr[min]);
			}
		};
		break;
	}
	default:
		break;
	}
	
}


// ����char����������
void testCharArr() {
	char arr[] = "bacgfhde";
	int arrSize = (int)strlen(arr);
	
	// �������ǰ�Ľ��
	cout << "before sort: " << endl;
	myPrint(arr, arrSize);

	// ������������
	mySort(arr, arrSize, UP);

	// ������
	cout << "after up sort: " << endl;
	myPrint(arr, arrSize);

	// ���н�������
	mySort(arr, arrSize, DOWN);

	// ������
	cout << "after down sort: " << endl;
	myPrint(arr, arrSize);
}

// ������������
void testIntArr() {
	int arr[] = { 3, 4, 2, 5, 1, 7, 6, 9, 8, 0 };
	int arrSize = sizeof(arr) / sizeof(int);

	// �������ǰ�Ľ��
	cout << "before sort: " << endl;
	myPrint(arr, arrSize);

	// ������������
	mySort(arr, arrSize, UP);

	// ������
	cout << "after up sort: " << endl;
	myPrint(arr, arrSize);

	// ���н�������
	mySort(arr, arrSize, DOWN);

	// ������
	cout << "after down sort: " << endl;
	myPrint(arr, arrSize);
}

// ���Ը���������
void testFloatArr() {
	double arr[] = { 3.3, 4.4, 2.2, 5.5, 1.1, 7.7, 6.6, 9.9, 8.8, 0.0 };
	int arrSize = sizeof(arr) / sizeof(double);

	// �������ǰ�Ľ��
	cout << "before sort: " << endl;
	myPrint(arr, arrSize);

	// ������������
	mySort(arr, arrSize, UP);

	// ������
	cout << "after up sort: " << endl;
	myPrint(arr, arrSize);

	// ���н�������
	mySort(arr, arrSize, DOWN);

	// ������
	cout << "after down sort: " << endl;
	myPrint(arr, arrSize);
}

int main(int argc, char** argv) {
    testCharArr();		// ����char������
    testIntArr();		// ����int������
    testFloatArr();		// ����float������

	system("pause");
	return 0;
}