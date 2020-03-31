#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>

// TODO реализовать компараторы в виде аргументов

#define PR(arg) cout << #arg << " = " << (arg) << endl;
#define LINE(arg) cout << "// ==========  " << arg << "  ========== //" << endl;

using namespace std;

void print_arr(int * arr, int size);

template<typename T>
class vec {
private:
    int _capacity = 1;
    int _size = 0;
    double k_increase = 2;
    T * buffer;
    void increase_capacity();
public:
    vec();
    vec(const vec &right) = delete;
    void operator=(const vec &right) = delete;
    ~vec();
    void push_back(T value);
    int size() const;
    int capacity() const;
    T& operator[](int i);
    T operator[](int i) const;
    void size_clear();
    void clear();
    void print() const;
};


template<typename T> void vec<T>::increase_capacity() {
    _capacity *= k_increase;
    T * new_buffer = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        new_buffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = new_buffer;
}
template<typename T> vec<T>::vec() {
    buffer = new T[_capacity];
}
template<typename T> vec<T>::~vec() {
    delete [] buffer;
}
template<typename T> void vec<T>::push_back(T value) {
    if (_size >= _capacity) increase_capacity();
    buffer[_size] = value;
    _size++;
}
template<typename T> int vec<T>::size() const {
    return _size;
}
template<typename T> int vec<T>::capacity() const {
    return _capacity;
}
template<typename T> T& vec<T>::operator[](int i) {
    return buffer[i];
}
template<typename T> T vec<T>::operator[](int i) const {
    return buffer[i];
}
template<typename T> void vec<T>::size_clear() {
    _size = 0;
}
template<typename T> void vec<T>::clear() {
    delete[] buffer;
    _capacity = 1;
    _size = 0;
    buffer = new T[_capacity];
}
template<typename T> void vec<T>::print() const {
    for (int i = 0; i < _size; i++) {
        cout << buffer[i] << "   ";
    }
    cout << endl;
}


class lsd_sort {
private:
    vec<long long> ** radix_arr;
public:

    void sort(long long * arr, int size);

};

void lsd_sort::sort(long long * arr, int size) {
    radix_arr = new vec<long long> * [256];
    for (int i = 0; i < 256; i++) {
        radix_arr[i] = new vec<long long>;
    }

    for (int byte_i = 0; byte_i < sizeof(long long); byte_i++) {
        for (int i = 0; i < size; i++) {

            int byte = (arr[i] >> (8 * byte_i)) & 255;

            radix_arr[byte]->push_back(arr[i]);
        }
        int k = 0;
        int sum = 0;
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < radix_arr[i]->size(); j++) {
                sum++;
                arr[k] = (*radix_arr[i])[j];
                k++;
            }
            radix_arr[i]->clear();
        }
    }

}



void insertion_sort(long long * arr, int size) {
    int j;
    long long temp;
    for (int i = 1; i < size; i++) {
        j = i;
        temp = arr[j];
        j--;
        while (arr[j] > temp && j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}



long long * generate(int size, long long max) {
    long long * arr = new long long[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() * 32000 + rand() * 30300L + rand() % max + 1;
    }
    return arr;
}
void print_arr(long long * arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << "   ";
    }
    cout << endl;
}


void radix_ll_test() {

    for (long long num = -3; num < 10; num++) {

        long long bsize = sizeof(num) * 8;
        //PR(sizeof(num));

        PR(sizeof(num) * 8);


        unsigned long long check = 1;
        for (int i = 0; i < bsize - 1; i++) {
            check <<= 1;
            //cout << check << endl;
        }



        for (int i = 0; i < bsize; i++) {
            //cout << (num & check) << endl;
            if ((num & check) == 0) {
                cout << 0;
            }
            else cout << 1;
            check >>= 1;
            //cout << check << endl;
        }
        cout << endl;
    }
}

void sort_test() {
    int n;
    cin >> n;
    long long * arr = new long long[n];
    lsd_sort srt;


    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    srt.sort(arr, n);
    print_arr(arr, n);
    delete[] arr;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "rus");

    //test3(4);

    //radix_ll_test();

    sort_test();


    return 0;
}




