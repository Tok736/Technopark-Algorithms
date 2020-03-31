#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>


void printArr(int * arr, int left, int right) {
    for (int i = left; i < right; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void printArr(int * arr, int n) {
    printArr(arr, 0, n);
}

int findMaximum(int * arr, int n) {
    int left = 0, right = 4, median;
    if (arr[n - 2] < arr[n - 1]) return n - 1;
    if (arr[0] > arr[1]) return 0;

    // exponencial search
    while (!(arr[left] < arr[left + 1] && arr[right - 2] > arr[right - 1])) {
        left = right - 2;
        right *= 2;
        if (right > n) right = n;
    }

    // binary search
    while (left != right - 1) {
        median = (right - left) / 2 + left;
        if (arr[median - 1] > arr[median]) right = median;
        else left = median;
    }
    return left;
}

int * generate(int n, int m) {
    int start = 0, stepDown = 1, stepUp = 4;
    int * arr = new int[n];
    arr[0] = start;
    for (int i = 1; i <= m; i++) {
        arr[i] = arr[i - 1] + rand() % (stepUp - stepDown) + stepDown;
    }
    for (int i = m + 1; i < n; i++) {
        arr[i] = arr[i - 1] - (rand() % (stepUp - stepDown) + stepDown);
    }
    return arr;
}


void contestTest() {
    int n;
    std::cin >> n;
    int * arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::cout << findMaximum(arr, n);
    delete[] arr;
}


void test() {
    int n = 10, m = 1;
    int * arr = generate(n, m);
    printArr(arr, n);
    int max = findMaximum(arr, n);
    std::cout << "maximum = " << arr[max] << std::endl;
}

int main() {
    srand(time(0));

    contestTest();

    return 0;
}