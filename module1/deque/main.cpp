#include <iostream>

using namespace std;

template<typename T>
class Deque {
private:
    size_t _capacity;
    size_t _size;
    T * buffer;
    size_t begin;
    size_t end;
    void grow() {
        _capacity *= 2;
        T * newBuffer = new T [_capacity];
        for (int i = 0; i < _size; i++) {
            newBuffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = newBuffer;
    }
public:
    Deque() : _capacity(8), _size(0), begin(0), end(0) {
        buffer = new T[_capacity];
    }

    void pushBack(const T& value) {
        if (_size > _capacity - 2) grow();
        buffer[end] = value;
        end = (end + 1) % _capacity;
        _size++;
    }
    void pushFront(const T& value) {
        if (_size > _capacity - 2) grow();
        begin--;
        if (begin < 0) begin += _capacity;
        buffer[begin];
    }
    T popBack() {
        if (_size > _capacity - 2) grow();

    }
    T popFront() {
        if (_size > _capacity - 2) grow();

    }

    T& operator[](int i) {
        return buffer[(begin + i) % _capacity];
    }

    T operator[](int i) const {
        return buffer[(begin + i) % _capacity];
    }

    void print() const {
        for (int i = 0; i < _size; i++) {
            cout << (*this)[i] << "  ";
        }
        cout << endl;
    }

    size_t size() const {
        return _size;
    }
    size_t capacity() const{
        return _capacity;
    }
};

void test() {
    Deque<int> d;
    for (int i = 0; i < 4; i++) {
        d.pushBack(i);
    }
    for (int i = 10; i < 12; i++) {
        d.pushFront(i);
    }
    d.print();
}


int main() {
    test();
    return 0;
}
