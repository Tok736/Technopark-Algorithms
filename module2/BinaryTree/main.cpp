#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

#define PR(a) cout << #a << " = " << a << endl;

template <typename T>
class Stack {
public:
    Stack();
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

template<typename T>
Stack<T>::Stack() {
    buffer = new T[_capacity];
}


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
                if (comp(value, temp->value)) {
                    if (temp->left == NULL) {
                        temp->left = new Node<T>(value, NULL, NULL);
                        isAdded = true;
                    }
                    else temp = temp->left;
                }
                else {
                    if (temp->right == NULL) {
                        temp->right = new Node<T>(value, NULL, NULL);
                        isAdded = true;
                    }
                    else temp = temp->right;
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
    void printLevel() const {
        queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            Node<T> * temp = q.front();
            q.pop();
            cout << temp->value << "  ";
            if (temp->left != nullptr) {
                q.push(temp->left);
            }
            if (temp->right != nullptr) {
                q.push(temp->right);
            }
        }
    }
    size_t len() const {return _len; }
    bool isEmpty() const {return _len == 0; }
    Node<T> * getRoot() const { return root; }
private:
    Comp comp;
    Node<T> * root = NULL;
    size_t _len = 0;

};


void test1() {
    BinaryTree<int, IntComparator> bt;
    int N;
    cin >> N;
    int temp;
    for (int i = 0; i < N; i++) {
        cin >> temp;
        bt.insert(temp);
    }
    bt.printLevel();

}

void test2() {
    BinaryTree<int, IntComparator> bt;
    int N = 8;
    int temp;
    for (int i = 0; i < N; i++) {
        temp = rand() % 64;
        cout << temp << "  ";
        bt.insert(temp);
    }
    cout << endl;
    bt.print_rec(bt.getRoot());
    cout << endl;
    bt.print();
}

void testStack() {
    Stack<int> st;
    for (int i = 0; i < 10; i++) {
        st.push(i);
    }
    for (int i = 0; !st.isEmpty(); i++) {
        cout << st.pop() << endl;
    }
}

int main() {
    srand(time(NULL));
    test1();
//    testStack();
    return 0;
}







