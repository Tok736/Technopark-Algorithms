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

template <typename T>
class ComparatorLess {
public:
    bool operator()(const T& left, const T& right) {
        return left < right;
    }
};

class IntComparator {
public:
    bool operator()(int left, int right) {
        return left < right;
    }
};



template <typename T, class Comp>
class BinaryTree {
public:
    template <typename Tn>
    class Node {
    public:
        Node(const Tn &value, Node * left, Node * right): value(value), left(left), right(right) {}
        Tn value;
        Node * left;
        Node * right;
    };


    BinaryTree() {}
    ~BinaryTree() {
        Stack<Node<T>*> st;
        Node<T> * temp = root;
        while (!st.isEmpty() || temp != NULL) {
            if (temp != NULL) {
                st.push(temp);
                temp = temp->left;
            }
            else {
                temp = st.pop();
                Node<T> * temp2 = temp;
                temp = temp->right;
                delete temp2;
            }
        }
    }
    void insert(const T& value) {
        if (root == NULL) root = new Node<T>(value, NULL, NULL);
        else {
            Node<T> * temp = root;
            bool isAdded = false;
            while (!isAdded) {
                if (temp->value <= value) {
                    if (temp->right == NULL) {
                        temp->right = new Node<T>(value, NULL, NULL);
                        isAdded = true;
                    }
                    else temp = temp->right;
                }
                else {
                    if (temp->left == NULL) {
                        temp->left = new Node<T>(value, NULL, NULL);
                        isAdded = true;
                    }
                    else temp = temp->left;
                }
            }
        }
        _len++;
    }
    void print_rec(Node<T> * temp) const {
        if (temp != NULL) {
            print_rec(temp->left);
            cout << temp->value << "  ";
            print_rec(temp->right);
        }
    }
    void print() const {
        Stack<Node<T>*> st;
        Node<T> * temp = root;
        while (!st.isEmpty() || temp != NULL) {
            if (temp != NULL) {
                st.push(temp);
                temp = temp->left;
            }
            else {
                temp = st.pop();
                cout << temp->value << "  ";
                temp = temp->right;
            }
        }
    }
    void heightRec(Node<T> * current, int &hmax, int h) const {
        if (h > hmax) hmax = h;
        if (current->left != nullptr) heightRec(current->left, hmax, h + 1);
        if (current->right != nullptr) heightRec(current->right, hmax, h + 1);
    }
    int height() const {
        if (root == nullptr) return 0;
        int hmax = 0;
        heightRec(root, hmax, 1);
        return hmax;
    }
    size_t len() const {return _len; }
    bool isEmpty() const {return _len == 0; }
    Node<T> * getRoot() const { return root; }
private:
    Comp comp;
    Node<T> * root = NULL;
    size_t _len = 0;

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
    void heightRec(Node<X, Y> * current, int &hmax, int h) const {
        if (h > hmax) hmax = h;
        if (current->left != nullptr) heightRec(current->left, hmax, h + 1);
        if (current->right != nullptr) heightRec(current->right, hmax, h + 1);
    }
    void split(Node<X, Y> * current, X x, Node<X, Y> *& left, Node<X, Y> *& right) {
        if (current == nullptr) {
            left = nullptr;
            right = nullptr;
        }
        else if (xcomp(x, current->x)) {
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
        if (ycomp(left->y, right->y)) {
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

        while (current != nullptr && !ycomp(y, current->y)) {
            parent = current;
            if (!xcomp(x, current->x)) {
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
    Treap<int, ComparatorOver<int>> tr;
    BinaryTree<int, IntComparator> bt;
    int N = 16;
    int * arr = generateArr(N, 0, 100);
    print(arr, N);
    cout << "Treap word: " << endl;
    for (int i = 0; i < N; i++) {
        tr.insert(arr[i], rand() % 10000);
        bt.insert(arr[i]);
    }
    cout << endl;
    tr.print();
    bt.print();
    cout << endl;
    cout << "Height: " << tr.height() << endl;
    cout << "Height: " << bt.height() << endl;
}

void mainTest() {
    int N;
    cin >> N;
    Treap<int, ComparatorOver<int>> tr;
    BinaryTree<int, IntComparator> bt;
    int x, y;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        tr.insert(x, y);
        bt.insert(x);
    }
    cout << bt.height() - tr.height() << endl;
}





int main() {

    mainTest();

    return 0;
}