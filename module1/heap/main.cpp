#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>


#define PR(arg) std::cout << #arg << " = " << (arg) << std::endl;
#define LINE(arg) std::cout << "// ==========  " << arg << "  ========== //" << std::endl;



template <typename T>
class greater {
public:
    bool operator() (const T& l, const T& r) {
        return l > r;
    }
};

template <typename T>
class less {
public:
    bool operator() (const T& l, const T& r) {
        return l < r;
    }
};


template<typename T, class comparator>
class Heap {
private:
    comparator comp;
    T * buffer;
    int _capacity = 1;
    int lastPosInd = -1;
    double kIncrease = 2;
    void siftUp(int elem_ind);
    void swap(int first, int second);
    void increaseCapacity();
    void siftDown(int elem_ind);
public:
    bool isEmpty() const;
    int isHeap(int ind = 0) const;

    Heap();
    ~Heap();
    void buildHeap();
    T readMax() const;
    T popMax();
    void insert(T value);
    void insertNoSift(T value);

    int height() const;
    int size() const;

    // Test func
    void putAt(T value, int ind);


    void print() const;
    void printTree() const;
};

template<typename T, class comparator> void Heap<T, comparator>::siftUp(int elem_ind) {
    int parent_ind = (elem_ind - 1) / 2;
    for (int i = 0; i < height() && comp(buffer[elem_ind], buffer[parent_ind]); i++) {
        swap(parent_ind, elem_ind);
        elem_ind = parent_ind;
        parent_ind = (parent_ind - 1) / 2;
    }
}
template<typename T, class comparator> void Heap<T, comparator>::siftDown(int elem_ind) {
    bool flag = true;
    int e_i = elem_ind;

    while (flag) {
        int child_l = e_i * 2 + 1;
        int child_r = e_i * 2 + 2;


        if (child_l > lastPosInd) {
            flag = false;
        }
        else {
            if (child_l == lastPosInd) {
                if (comp(buffer[child_l], buffer[e_i])) swap(child_l, e_i);
                flag = false;
            }
            else {
                if (comp(buffer[child_l], buffer[e_i]) || comp(buffer[child_r], buffer[e_i])) {
                    if (comp(buffer[child_l], buffer[child_r])) {
                        swap(child_l, e_i);
                        e_i = child_l;
                    }
                    else {
                        swap(child_r, e_i);
                        e_i = child_r;
                    }
                }
                else flag = false;
            }
        }
    }

}
template<typename T, class comparator> bool Heap<T, comparator>::isEmpty() const {
    return size() == 0;
}
template<typename T, class comparator> void Heap<T, comparator>::swap(int first, int second) {
    std::swap(buffer[first], buffer[second]);
}
template<typename T, class comparator> int Heap<T, comparator>::isHeap(int ind) const {
    if (ind > lastPosInd) return 0;
    int child_left = ind * 2 + 1;
    int child_right = ind * 2 + 2;
    if (child_left > lastPosInd) return 0;
    int res = 0;
    if (buffer[child_left] > buffer[ind]) res++;
    res += isHeap(child_left);
    if (buffer[child_right] > buffer[ind] && child_right <= lastPosInd) res++;
    res += isHeap(child_right);
    return res;
}
template<typename T, class comparator> Heap<T, comparator>::Heap() {
    buffer = new T[_capacity];
}
template<typename T, class comparator> Heap<T, comparator>::~Heap() {
    delete[] buffer;
}
template<typename T, class comparator> void Heap<T, comparator>::buildHeap() {
    for (int i = size() / 2 - 1; i >= 0; i--) {
        siftDown(i);
    }
}
template<typename T, class comparator> T Heap<T, comparator>::readMax() const {
    if (size() != 0) {
        return buffer[0];
    }
}
template<typename T, class comparator> T Heap<T, comparator>::popMax() {
    T temp = buffer[0];
    swap(0, lastPosInd);
    lastPosInd--;
    siftDown(0);
    return temp;
}
template<typename T, class comparator> void Heap<T, comparator>::insert(T value) {
    lastPosInd++;
    buffer[lastPosInd] = value;
    siftUp(lastPosInd);
    if (size() >= _capacity) increaseCapacity();
}
template<typename T, class comparator> void Heap<T, comparator>::insertNoSift(T value) {
    lastPosInd++;
    buffer[lastPosInd] = value;
    if (size() >= _capacity) increaseCapacity();
}
template<typename T, class comparator> int Heap<T, comparator>::height() const {
    int res = 0;
    int check_size = 1;
    while (check_size < lastPosInd + 2) {
        check_size *= 2;
        res++;
    }
    return res;
}
template<typename T, class comparator> int Heap<T, comparator>::size() const {
    return lastPosInd + 1;
}
template<typename T, class comparator> void Heap<T, comparator>::increaseCapacity() {
    _capacity *= kIncrease;
    T * newBuffer = new T[_capacity];
    for (int i = 0; i < size(); i++) {
        newBuffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
}
template<typename T, class comparator> void Heap<T, comparator>::putAt(T value, int ind) {
    buffer[ind] = value;
}
template<typename T, class comparator> void Heap<T, comparator>::print() const {
    for (int i = 0; i < size(); i++) {
        std::cout << buffer[i] << "   ";
    }
    std::cout << std::endl;
}
template<typename T, class comparator> void Heap<T, comparator>::printTree() const {
    int row = 2;
    for (int i = 0; i < size(); i++) {
        if (row - 1 == i) {
            std::cout << std::endl;
            row *= 2;
        }
        std::cout << buffer[i] << "  ";
    }
    std::cout << std::endl;
}


void contestTest() {
    Heap<int, less<int>> h;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        h.insert(temp);
    }

    int S = 0;
    while (h.size() > 1) {
        int min1 = h.popMax(), min2 = h.popMax();
        int temp = min1 + min2;
        S += temp;
        h.insert(temp);
    }
    std::cout << S << std::endl;
}

void test() {
    Heap<int, less<int>> h;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        h.insert(rand() % 30);
    }

    while (!h.isEmpty()) {
        int temp = h.popMax();
        std::cout << temp << " ";
    }
    std::cout << std::endl;
}


int main()
{
    srand(time(NULL));

    contestTest();

    return 0;
}