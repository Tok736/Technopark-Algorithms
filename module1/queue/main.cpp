#include <iostream>
#include <stdio.h>


const int defaultCapacity = 8;
const int kGrow = 2;

template <typename T>
class Queue {
private:
    T * buffer;
    int _capacity;
    int start;
    int end;
    void grow() {
        int s = size();
        T *newBuffer;
        newBuffer = new T[_capacity * kGrow];
        for (int i = start, j = 0; i != end; i = (i + 1) % _capacity, j++) {
            newBuffer[j] = buffer[i];
        }
        delete[] buffer;
        buffer = newBuffer;
        start = 0;
        end = s;
        _capacity *= kGrow;
    }
    void init(int startCapacity) {
        buffer = new T[startCapacity];
        _capacity = startCapacity;
        start = end = 0;
    }
public:
    Queue(int startCapacity = defaultCapacity) {
        init(startCapacity);
    }
    ~Queue() {
        delete[] buffer;
    }
    void pushBack(const T& value) {
        if (size() + 2 > capacity()) grow();
        buffer[end] = value;
        end = (end + 1) % _capacity;
    }
    T readFront() const {
        return buffer[start];
    }
    T popFront() {
        int temp = start;
        start = (start + 1) % _capacity;
        return buffer[temp];
    }
    int size() const {
        return (end >= start) ? end - start : end + _capacity - start;
    }
    int capacity() const {
        return _capacity;
    }
    bool isEmpty() const {
        return size() == 0;
    }
};



void contestTest() {
    int64_t n, command, value, temp;
    std::cin >> n;

    Queue<int64_t> q;

    bool flag = true;
    for (int64_t i = 0; i < n; i++) {
        std::cin >> command >> value;
        switch (command) {
            case 2:
                if (q.isEmpty()) temp = -1;
                else temp = q.popFront();
                if (temp != value) flag = false;
                break;
            case 3:
                q.pushBack(value);
                break;
        }
    }
    if (flag) std::cout << "YES" << std::endl;
    else std::cout << "NO" << std::endl;
}


int main() {

    contestTest();

    return 0;
}