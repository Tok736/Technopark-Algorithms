#include <iostream>
#include <queue>
#include <cstdlib>

using namespace std;

#define PR(a) cout << #a << " = " << a << endl;

template <typename T>
class Stack {
public:
    Stack() {
        buffer = new T[_capacity];
    }
    ~Stack() {
        delete[] buffer;
    }
    void push(const T &value) {
        if (_len >= _capacity) grow();
        buffer[_len] = value;
        _len++;
    }
    T pop() {
        if (_len == 0) throw exception();
        _len--;
        return buffer[_len];
    }
    T read() const {
        if (_len == 0) throw exception();
        return buffer[_len - 1];
    }
    size_t len() const { return _len; }
    bool isEmpty() const { return _len == 0; }
    void print() const {
        for (size_t i = 0; i < _len; i++) {
            cout << buffer[i]->value << "  ";
        }
        cout << endl;
    }
private:
    void grow() {
        _capacity *= 2;
        T * new_buffer = new T[_capacity];
        for (size_t i = 0; i < _len; i++) {
            new_buffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = new_buffer;
    }
    size_t _len = 0;
    size_t _capacity = 4;
    T * buffer;

};

template <typename T>
class ComparatorOver {
public:
    bool operator()(const T& left, const T& right) {
        return left > right;
    }
};
class IntComparatorOver {
public:
    bool operator()(int left, int right) {
        return left > right;
    }
};
class IntComparatorLess {
public:
    bool operator()(int left, int right) {
        return left < right;
    }
};


template <typename X, typename Xcomp = ComparatorOver<X>, typename Y = int, typename Ycomp = ComparatorOver<Y>>
class Treap {
private:
    Xcomp xcomp;
    Ycomp ycomp;

    template<typename Xn, typename Yn>
    class Node {
    public:
        Node (Xn x, Yn y, Node * left, Node * right) : x(x), y(y), left(left), right(right) {}
        Xn x;
        Yn y;
        Node * left;
        Node * right;
    };

    size_t _size;
    Node<X, Y> * root;
    int heightRec(Node<X, Y> * current, int &hmax, int h) const {
        if (h > hmax) hmax = h;
        if (current->left != nullptr) heightRec(current->left, hmax, h + 1);
        if (current->right != nullptr) heightRec(current->right, hmax, h + 1);
    }
    void split(Node<X, Y> * current, X x, Node<X, Y> *& left, Node<X, Y> *& right) {
        if (current == nullptr) {
            left = nullptr;
            right = nullptr;
        }
        else if (current->x < x) {
            split(current->right, x, current->right, right);
            left = current;
        }
        else {
            split(current->left, x, left, current->left);
            right = current;
        }

    }
    Node<X, Y> * merge(Node<X, Y> * left, Node<X, Y> right) {
        if (left == nullptr || right == 0) {
            return left == 0 ? right : left;
        }
        if (left->y > right->y) {
            left->right = merge(left->right, right);
            return left;
        }
        else {
            right->left = merge(left, right->left);
            return right;
        }
    }
public:
    Treap() : _size(0), root(nullptr) {}
    void insert(X x, Y y) {
        if (root == nullptr) {
            root = new Node<X, Y>(x, y, nullptr, nullptr);
            _size++;
            return;
        }

        bool isLeft;

        Node<X, Y> * current = root;
        Node<X, Y> * parent = nullptr;

        while (current != nullptr && current->y >= y) {
            parent = current;
            if (current->x >= x) {
                current = current->left;
                isLeft = true;
            }
            else {
                current = current->right;
                isLeft = false;
            }
        }

        Node<X, Y> * left = nullptr;
        Node<X, Y> * right = nullptr;

        split(current, x, left, right);

        current = new Node<X, Y>(x, y, left, right);




        if (parent == nullptr) {
            root = current;
            return;
        }

        if (isLeft) {
            parent->left = current;
        }
        else {
            parent->right = current;
        }
    }
    void print() const {
        Stack<Node<X, Y>*> st;
        Node<X, Y> * temp = root;
        while (!st.isEmpty() || temp != nullptr) {
            if (temp != nullptr) {
                st.push(temp);
                temp = temp->left;
            }
            else {
                temp = st.pop();
                cout << temp->x << "  ";
                temp = temp->right;
            }
        }
        cout << endl;
    }
    void printRec(Node<X, Y> * root) const {
        if (root != nullptr) {
            printRec(root->left);
            cout << root->x << "  ";
            printRec(root->right);
        }
    }
    Node<X, Y> * getRoot() const {
        return root;
    }
    int height() const {
        if (root == nullptr) return 0;
        int hmax = 0;
        heightRec(root, hmax, 1);
        return hmax;
    }
};

int * generateArr(int N, int down, int up) {
    int * arr = new int[N];
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % (up - down) + down;
    }
    return arr;
}
void print(int * arr, int N) {
    for (int i = 0; i < N; i++) {
        cout << arr[i] << "  ";
    }
    cout << endl;
}
void test1() {
    srand(time(nullptr));
    Treap<int, IntComparatorOver> tr;
    int N = 3;
    int * arr = generateArr(N, 0, 100);
    print(arr, N);
    cout << "Treap word: " << endl;
    for (int i = 0; i < N; i++) {
        tr.insert(arr[i], rand() % 10000);
    }
    cout << endl;
    tr.print();
    cout << "Height: " << tr.height();
}
void test2() {
    Treap<int> tr;
    Node<int, int> * ltree;
    Node<int, int> * rtree;
    for (int i = 0; i < 20; i++) {
        tr.insert( rand() % 100, rand() % 1000);
    }

    tr.printRec(tr.getRoot());
    cout << endl;

    int k = 50;

    tr.split(tr.getRoot(), k, ltree, rtree);
    tr.printRec(ltree);
    cout << endl;
    tr.printRec(rtree);
    cout << endl;
    cout << "Success" << endl;
}





int main() {

    test1();

    return 0;
}