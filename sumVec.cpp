#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

template<typename T>
void PrintVector(const vector<T>& v) {
	for (const auto& item : v) {
		cout << item << " ";
	}
	cout << endl;
}

//1
vector<int> sum(const vector<vector<int>>& v) {
	vector<int> result;
	for (const auto& item : v) {
		result.push_back(accumulate(item.begin(), item.end(), 0));
	}
	return result;
}

//1a
template<typename T>
vector<T> sum(const vector<vector<T>>& v) {
	vector<T> result;
	for (const auto& item : v) {
		result.push_back(accumulate(item.begin(), item.end(), 0));
	}
	return result;
}

template<typename <T>>
class MatrixReduceOperation {
protected: 
	vector<vector<T>> matrix:
public: 
	MatrixReduceOperation() {}

	MatrixReduceOperation(const vector<vector<T>>& v) {
		matrix = v;
	}

	virtual vector<T> calc() {
		vector<T> result;
		for (const auto& item : matrix){
			result.push_back(accumulate(item.begin(), item.end(), 0));

		}
		return result;
	}
};

template<typename <T1>>
class MatrixRowSum : virtual public MatrixReduceOperation<T1> {
public: 
	MatrixRowSum() : MatrixReduceOperation<T1>() {}
	MatrixRowSum(const vector<vector<T1>>& v) : MatrixReduceOperation<T1>(v) {}
	vector<T1> calc() {
		for (const auto& item : MatrixReduceOperation<T1>::matrix) {
			result.push_back(accumulate(item.begin(), item.end(), 0));
		}
		return result;
	}
};

int main() {
	vector<vector<int>> v = { {1, 2, 3, 6, 4, 5} {6, 4, 3, 21,} {5, 6, 2, 1} }
	vector<int> m = sum(v);
	PrintVector(m);

	MatrixReduceOperation k = v;
	PrintVector(k.calc());



}
