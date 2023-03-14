#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Бинарная куча. 
template <class T>
class HeapOverArray
{
    vector<T> v;
public:
    vector<T> getVector() { return v; } 
    HeapOverArray() {}
     HeapOverArray(vector<T> a) { v = a; } 
    bool addNode(const T& o)
    {
        size_t pos = v.size();
        if (pos == 0) //если куча пустая, то пушим первый элемент
        {
            v.push_back(o);
            return true;
        }
         int parent_pos = (pos + 1) / 2 - 1; //вычилеие позиции родителя 
        v.push_back(o); //пушим новый элемент в конец кучи
        while (parent_pos >= 0 && o > v[parent_pos]) //вертикальная сортировака кучи пока есть родитель и значение элемента больше родителя
        {
            swap(v[pos], v[parent_pos]);
            pos = parent_pos;
            parent_pos = ((pos + 1) / 2) - 1;
        }
        if (pos == 0) //если пушимый элемент стал основанием кучи, то мы сортируем горизонтально
        {
            if (v[1] > v[2])
                swap(v[1], v[2]);
        }
        else //иначе сортируем на уровень ниже, чем тот в котором лежит элемент о
        {
            if (v[(parent_pos + 1) * 2 - 1] > v[(parent_pos + 1) * 2])
                swap(v[(parent_pos + 1) * 2], v[(parent_pos + 1) * 2 - 1]);
        }
        return true;
    } 
    
    bool removeNode(const T& o) //удаление узла
    {
        int indx = 0;
        while (indx < v.size() && v[indx] != o) //поиск удаляемого элемента
            indx++;
        
        if (indx == v.size())//элемент не найден
            return false;
        
        v[indx] = v[v.size() - 1];//удаление элемента
        v.pop_back();
        
        if (indx == v.size())//если искомый элемент оказался послежним, то струкра не нарушена - можно оставить как есть
            return true;
        
        if (indx > 0 && v[indx] > v[(indx + 1) / 2 - 1]) //иначе сортировка
        {
            while (indx > 0 && v[indx] > v[(indx + 1) / 2 - 1])//свапаем родителей и потомков до тех пр, пока не отсортируется  
            {
                swap(v[indx], v[(indx + 1) / 2 - 1]);
                indx = (indx + 1) / 2 - 1;
            }
            if (indx == 0) //если удаленный элемент оказался первым, возращаем 1
                return true;
            if (v[indx] > v[((indx + 1) / 2 - 1) * 2 + 1])
            {
                swap(v[indx], v[((indx + 1) / 2 - 1) * 2 + 1]);
            }
            return true;
        }
        else
        {
            while (indx * 2 + 2 < v.size())
            {
                if ((v[indx] < v[indx * 2 + 2]) && (v[indx] < v[indx * 2 + 1]))
                {
                    if (v[indx * 2 + 2] > v[indx * 2 + 1])
                    {
                        swap(v[indx], v[indx * 2 + 2]);
                        indx = indx * 2 + 2;
                    }
                    else
                    {
                        swap(v[indx], v[indx * 2 + 1]);
                        indx = indx * 2 + 1;
                    }
                }
                else if (v[indx] < v[indx * 2 + 2])
                {
                    swap(v[indx], v[indx * 2 + 2]);
                    indx = indx * 2 + 2;
                }
                else if (v[indx] < v[indx * 2 + 1])
                {
                    swap(v[indx], v[indx * 2 + 1]);
                    indx = indx * 2 + 1;
                }
                else
                    return true;
            }
            if (indx * 2 + 1 < v.size() && v[indx] < v[indx * 2 + 1])
                swap(v[indx], v[indx * 2 + 1]);
            return true;
        }
    }
};


template<class T>
    bool testHeapAdd(const vector<T>& initial, const T& value, const vector<T>& expected)
{
    HeapOverArray<T> a(initial);
    a.addNode(value);
    auto v = a.getVector();
    if (v.size() != expected.size())
    {
        cerr << "size difference: expected " << expected.size() << ", got" << v.size() << '\n';
        return false;
    }
    for (size_t i = 0; i < expected.size(); i++)
         {
        if (v[i] != expected[i])
        {
            cerr << " difference in " << i << " expected: " << expected[i] << ", got" << v[i] << '\n';
            return false;
        }
    }
    return true;
}


template<class T>
bool testHeapDell(const vector<T>& initial, const T& value, const vector<T>& expected)
{
    HeapOverArray<T> a(initial);
    a.removeNode(value);
    auto v = a.getVector();
    if (v.size() != expected.size())
    {
        cerr << "size difference: expected " << expected.size() << ", got" << v.size() << '\n';
        return false;
    }
    for (size_t i = 0; i < expected.size(); i++)
    {
        if (v[i] != expected[i])
        {
            cerr << " difference in " << i << " expected: " << expected[i] << ", got" << v[i] << '\n';
            return false;
        }
    }
    return true;
}


template<class T>
class iterator
{
     vector<T>* v;
    size_t idx;
public:
    iterator() : v(nullptr) {}
    iterator(std::vector<T>* v_, size_t idx_) : v(v_), idx(idx_) {}
    size_t getindex() { return idx; }
    iterator& operator++()
    {
        if (((idx + 1) * 2 + 1) > (*v).size())
        {

            while ((idx + 1) % 2 != 0)
            {
                idx = idx / 2 - 1;
            }
            if (idx == 0)
                v = nullptr;
            idx = idx / 2;
        }
        else
        {
            idx = idx * 2 + 2;
            while (idx * 2 + 1 < (*v).size())
                idx = idx * 2 + 1;
        }
        return *this;
    }

    iterator operator++(int) {
        auto prev = *this;
        ++(*this);
        return prev;
    }
const T& operator*() const { return v[idx]; }
    T& operator*() { return v[idx]; }
};


template<class T>
bool testHeapIter(const vector<T>& initial, int const& indx, const vector<T>& expected)
{
    HeapOverArray<T> a(initial);
    auto v = a.getVector();
    ::iterator<T> b(&v, indx);
    for (auto i = 0; i < expected.size(); i++)
    {
        if (v[b.getindex()] != expected[i])
        {
            cerr << " difference in " << i << " expected: " << expected[i] << ", got" << v[i] << '\n';
            return false;
        }
        b++;
    }
    return true;
}
int main()
{
    vector <int> a = { 17, 10, 13, 5,8,6,7,1,2, };
    vector <int> b = { 17, 10, 13, 5,8,6,7,1, };
    testHeapDell(a, 2, b);
    a = b;
    b = { 17, 10, 13, 1,8,6,7, };
    testHeapDell(a, 5, b);
    a = b;
    b = { 17, 10, 7, 1,8,6, };
    testHeapDell(a, 13, b);
    a = b;
    b = { 10, 8, 7, 1,6, };
    testHeapDell(a, 17, b);
    a = b;
    testHeapDell(a, 17, b);


    a = { 30,10,16,5,9,6,7,0,2,4 };
    b = { 0,5,2,10,4,9,30,6,16,7 };
    testHeapIter(a, 7, b);
    return 0;
}
