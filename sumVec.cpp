#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

//Шаблонная функция, выводящая массив на экран
template<typename T>
void PrintVector(const vector<T>& v) {
    for (const auto& item : v) {
        cout << item << " ";
    }
    cout << endl;
}

//Функция, суммирующая вектор векторов 
vector<int> sum(const vector<vector<int>>& v) {
    vector<int> result;
    for (const auto& item : v) {
        result.push_back(accumulate(item.begin(), item.end(), 0)); //запушить в конец(сумма(вектор.начало, вектор.конец, начальная сумма))
    }
    return result;
}

//шаблонная функиця суммы вектора векторов
template<typename T>
vector<T> sum(const vector<vector<T>>& v) {
    vector<T> result;
    for (const auto& item : v) {
        result.push_back(accumulate(item.begin(), item.end(), 0));
    }
    return result;
}

template<typename T>
class MatrixReduceOperation {
protected:
    vector<vector<T>> matrix;
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

template<typename T>
class MatrixRowSum : virtual public MatrixReduceOperation<T> {
public:
    MatrixRowSum() : MatrixReduceOperation<T>() {}
    MatrixRowSum(const vector<vector<T>>& v) : MatrixReduceOperation<T>(v) {}
    vector<T> calc() {
        vector<T> result;
        for (const auto& item : MatrixReduceOperation<T>::matrix) {
            result.push_back(accumulate(item.begin(), item.end(), 0));
        }
        return result;
    }
};

int main() {
    vector<vector<int>> v = { {1, 2, 3, 6, 4, 5}, {6, 4, 3, 21}, {5, 6, 2, 1} };
    vector<int> m = sum(v);
    PrintVector(m);

    MatrixReduceOperation<int> k(v);
    PrintVector(k.calc());

    return 0;
}
