#include <iostream>
using namespace std;

void lShiftMas(int* source, int n, const int size) {
	cin >> n;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < size; i++) {
			if (size == i + 1) {
				break;
			}
			source[i] = source[i + 1];
		}
		source[size - 1] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		cout << source[i];
	}
	cout << endl;
}

bool compareArr(int* a, int* b, int size) {
	for (int i = 0; i < size; i++)
		if (a[i] != b[i]) return false;
	return true;
}

bool test(int n, int size) {
	int arr1[5] = { 1,2,3,4,5 };
	int arr2[5] = { 4,5,0,0,0 };
	lShiftMas(arr1, 3, 5);
	bool f1 = compareArr(arr1, arr2, 5);
	return (f1);
}

int main() {
	const int size = 5;
	int source[size] = { 1,2,3,4,5 };
	if (test(3, size)) {
		cout << "test ok";
	}
	else {

		cout << "test not ok";
	}
	return 0;
}