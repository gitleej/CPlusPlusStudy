#include <iostream>
#include <string.h>

typedef enum TypeUpOrDownEnum
{
	UP,			// 升序
	DOWN,		// 降序
}TypeUpOrDown;

using namespace std;

// 输出函数模板
template<typename T> 
void myPrint(T arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// 交换数据模板
template<typename T>
void mySwap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

// 排序函数模板
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
			// 交换
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
			// 交换
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


// 测试char型数组排序
void testCharArr() {
	char arr[] = "bacgfhde";
	int arrSize = (int)strlen(arr);
	
	// 输出排序前的结果
	cout << "before sort: " << endl;
	myPrint(arr, arrSize);

	// 进行升序排序
	mySort(arr, arrSize, UP);

	// 输出结果
	cout << "after up sort: " << endl;
	myPrint(arr, arrSize);

	// 进行降序排序
	mySort(arr, arrSize, DOWN);

	// 输出结果
	cout << "after down sort: " << endl;
	myPrint(arr, arrSize);
}

// 测试整型数组
void testIntArr() {
	int arr[] = { 3, 4, 2, 5, 1, 7, 6, 9, 8, 0 };
	int arrSize = sizeof(arr) / sizeof(int);

	// 输出排序前的结果
	cout << "before sort: " << endl;
	myPrint(arr, arrSize);

	// 进行升序排序
	mySort(arr, arrSize, UP);

	// 输出结果
	cout << "after up sort: " << endl;
	myPrint(arr, arrSize);

	// 进行降序排序
	mySort(arr, arrSize, DOWN);

	// 输出结果
	cout << "after down sort: " << endl;
	myPrint(arr, arrSize);
}

// 测试浮点型数组
void testFloatArr() {
	double arr[] = { 3.3, 4.4, 2.2, 5.5, 1.1, 7.7, 6.6, 9.9, 8.8, 0.0 };
	int arrSize = sizeof(arr) / sizeof(double);

	// 输出排序前的结果
	cout << "before sort: " << endl;
	myPrint(arr, arrSize);

	// 进行升序排序
	mySort(arr, arrSize, UP);

	// 输出结果
	cout << "after up sort: " << endl;
	myPrint(arr, arrSize);

	// 进行降序排序
	mySort(arr, arrSize, DOWN);

	// 输出结果
	cout << "after down sort: " << endl;
	myPrint(arr, arrSize);
}

int main(int argc, char** argv) {
    testCharArr();		// 测试char型数组
    testIntArr();		// 测试int型数组
    testFloatArr();		// 测试float型数组

	system("pause");
	return 0;
}