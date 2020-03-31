#include <iostream>
#include <time.h>
#include <vector>

#define PR(arg) std::cout << #arg << " = " << (arg) << std::endl;
#define LINE(arg) cout << "// ==========  " << arg << "  ========== //" << endl;




template <typename T, typename comparator = std::greater<T>>
void merge(T * arr, T * temp, int left, int median, int right, comparator comp = comparator()) {
    int i = left, j = median, k = left;

    while (i < median || j < right) {
        if ((comp(arr[j], arr[i]) || j == right) && i < median) {
            temp[k] = arr[i];
            i++; k++;
        }
        else if ((comp(arr[i], arr[j]) || i == median) && j < right) {
            temp[k] = arr[j];
            j++; k++;
        }
        else {
            temp[k] = arr[i];
            i++; k++;
            temp[k] = arr[j];
            j++; k++;
        }
    }
    for (int y = left; y < right; y++)
        arr[y] = temp[y];
}
template <typename T, typename comparator = std::greater<T>>
void recMerge(T * arr, T * temp, int left, int right, comparator comp = comparator()) {
    int median = (right - left) / 2 + left;
    if (right - left > 1) {
        recMerge(arr, temp, left, median, comp);
        recMerge(arr, temp, median, right, comp);
        merge(arr, temp, left, median, right);
    }
}

template <typename T, typename comparator = std::greater<T>>
void sort (T * arr, int size, comparator comp = comparator()) {
    T * temp = new T[size];
    recMerge(arr, temp, 0, size, comp);
    delete[] temp;
}

struct date {
    int day, month, year;
    date() = default;
    date(int day, int month, int year) : day(day), month(month), year(year) {}

    bool operator>(const date& other) const {
        if (year > other.year) return true;
        else if (year < other.year) return false;
        else {
            if (month > other.month) return true;
            else if (month < other.month) return false;
            else {
                if (day > other.day) return true;
                else if (day < other.day) return false;
                else {
                    return false;
                }
            }
        }
    }
};

struct point {
    date d;
    bool isStart;
    point() = default;
    point(int day, int month, int year, bool isStart) : d(day, month, year), isStart(isStart) {}
    bool operator>(const point& other) const {
        return d > other.d;
    }
};

void contestTest() {
    int n;
    std::cin >> n;
    point * dates = new point[n * 2];
    for (int i = 0; i < n; i++) {
        bool adding = true;
        int day, month, year;
        std::cin >> day >> month >> year;
        point temp1(day, month, year, true);
        std::cin >> day >> month >> year;
        point temp2(day, month, year, false);
        point check = temp1;
        check.d.year += 80;
        if (temp2 > check) {
            temp2 = check;
            temp2.isStart = false;
        }
        temp1.d.year += 18;
        if (!(temp2 > temp1)) adding = false;
        if (adding) {
            dates[i * 2] = temp1;
            dates[i * 2 + 1] = temp2;
        }
        else {
            i--;
            n--;
        }
    }
    sort(dates, n * 2);
    int maxS = 0;
    int S = 0;
    for (int i = 0; i < n * 2; i++) {
        if (dates[i].isStart) S++;
        else S--;
        if (S > maxS) maxS = S;
    }
    std::cout << maxS << std::endl;
    delete[] dates;
}






int main()
{
    srand(time(NULL));

    contestTest();

    return 0;
}



