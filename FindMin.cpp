#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Объявление шаблона, В данном случае шаблонной функции. Функция подстраивается и изменякется в зависимости от того какой тип данных в нее входит. 

//Шаблонная функция копирования одного массива в другой
template<typename T>
void copy_array(const T* from, T* to, size_t count) { // 
	for (size_t i = 0; i < count; i++) {
		to[i] = from[i];
	}
}

// функци вывода массива
template<typename T>
void print_array(const T* parr, size_t count) {
	for (size_t i = 0; i < count; i++) {
		cout << parr[i] << " ";
	}
	cout << endl;
}

//поиск индекса, принадлежащему минимальному элементу массива
template<typename T>
int findmin(const T* parr, size_t count) {
	size_t min = 0;
	if (count == 0) {
		return 0;
	}
	T elem = parr[0];
	for (size_t i = 0; i < count; i++) {
		if (parr[i] < elem) {
			elem = parr[i];
			min = i;
		};
	};
	return min;
}


int main(int argc, char** argv) {
    int arr[20], arr2[20];
    for (auto i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        arr[i] = rand();
    copy_array(arr, arr2, sizeof(arr) / sizeof(arr[0]));
    print_array(arr, sizeof(arr) / sizeof(arr[0]));
    print_array(arr2, sizeof(arr2) / sizeof(arr2[0]));
    return 0;
}
