#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>

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

template <typename T, typename comparator = greater<T>>
int partition(T * arr, int left, int pivot, int right, comparator comp = comparator()) {
    int pivot_elem = arr[pivot];

    std::swap(arr[left], arr[pivot]);

    int it1 = right - 1;
    int it2 = right - 1;


    while (comp(arr[it1], pivot_elem)) {
        it1--;
        it2--;
    }

    while (it2 > left + 1 && it1 > left + 1) {
        it2--;
        if (comp(arr[it2], pivot_elem)) {
            std::swap(arr[it2], arr[it1]);
            it1--;
        }
    }
    if (comp(arr[left], arr[it1])) std::swap(arr[left], arr[it1]);

    return it1;
}

int getPivot(int left, int right) {
    return rand() % (right - left) + left;
}

template <typename T, typename comparator = greater<T>>
int findKOrder(T * arr, int size, int k, comparator comp = comparator()) {
    T * buffer = new T[size];
    for (int i = 0; i < size; i++) {
        buffer[i] = arr[i];
    }
    int left = 0, right = size;

    int pivot, temp_i = -1;
    while (temp_i != k) {
        pivot = getPivot(left, right);
        temp_i = partition(arr, left, pivot, right, comp);

        if (temp_i < k)
            left = temp_i + 1;
        else if (temp_i > k)
            right = temp_i;
        else
            return arr[temp_i];

        if (right == left) return arr[right];
    }
    delete[] buffer;

    return -1;
}

void contestTest() {
    int N, k;
    std::cin >> N >> k;
    int * arr = new int[N];
    for (int i = 0; i < N; i++) {
        std::cin >> arr[i];
    }
    std::cout << findKOrder(arr, N, k);
    delete[] arr;
}

int main()
{
    srand(time(0));

    contestTest();

    return 0;
}