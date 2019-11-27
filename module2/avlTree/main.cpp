#include <iostream>
#include <stack>
#include <queue>
#include <ctime>
#include <cmath>

using namespace std;


#define PR(a) cout << #a << " = " << a << endl;

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


template <typename T, typename Comp>
class AvlTree {
private:
    template <typename Tn>
    class Node {
    public:
        Node(const Tn& value, Node * parent) :
                value(value), left(nullptr), right(nullptr), parent(parent), factor(0)  {}
        Node * left, *right, *parent;
        int factor;
        Tn value;
    };
    Node<T> * root;
    size_t _size;
    void heightRec(Node<T> * current, int &hmax, int h) const {
        if (h > hmax) hmax = h;
        if (current->left != nullptr) heightRec(current->left, hmax, h + 1);
        if (current->right != nullptr) heightRec(current->right, hmax, h + 1);
    }
    void correctBalanceUp(Node<T> * temp, int adding) {
        bool is_left;
        while (temp->parent != nullptr) {
            is_left = temp->parent->left == temp;
            temp = temp->parent;
            if (is_left) {
                temp->factor += -adding;
                if (temp->factor >= 0) break;
            } else {
                temp->factor += adding;
                if (temp->factor <= 0) break;
            }
        }
    }
    void correctBalanceUpPlus(Node<T> * temp) {
        correctBalanceUp(temp, 1);
    }
    void correctBalanceUpMinus(Node<T> * temp) {
        correctBalanceUp(temp, -1);
    }
    void rebalanceUp(Node<T> * temp) {
        while (temp != nullptr) {
            if (temp->factor >= 2) {
                if (temp->right->factor >= 1) temp = rotateLeft(temp);
                else temp = bigRotateLeft(temp);
            }
            if (temp->factor <= -2) {
                if (temp->left->factor <= -1) temp = rotateRight(temp);
                else temp = bigRotateRight(temp);
            }
            if (abs(temp->factor) < 2)
                temp = temp->parent;
        }
    }
    Node<T> * rotateLeft(Node<T> * temp) {
//        PR("lL");
        int tAFac = abs(temp->factor);

        Node<T> ** base;
        if (temp->parent == nullptr) base = &root;
        else if (temp->parent->left == temp) base = &temp->parent->left;
        else base = &temp->parent->right;


        *base = temp->right;
        temp->right = (*base)->left;
        if((*base)->left != nullptr) (*base)->left->parent = temp;
        (*base)->left = temp;


        (*base)->parent = temp->parent;
        temp->parent = (*base);

        if ((*base)->factor > 0) temp->factor += -(*base)->factor - 1;
        else temp->factor += -1;
        if (temp->factor > 0) (*base)->factor += -1;
        else (*base)->factor += temp->factor - 1;

        if (abs((*base)->factor) - 1 > tAFac) correctBalanceUpPlus((*base));
        else if (abs((*base)->factor) + 1 < tAFac) correctBalanceUpMinus((*base));
        return *base;
    }
    Node<T> * bigRotateLeft(Node<T> * temp) {
        rotateRight(temp->right);
        temp = rotateLeft(temp);
        return temp;
    }
    Node<T> * rotateRight(Node<T> * temp) {
//        PR("rR");
        int tAFac = abs(temp->factor);

        Node<T> ** base;
        if (temp->parent == nullptr) base = &root;
        else if (temp->parent->left == temp) base = &temp->parent->left;
        else base = &temp->parent->right;

        *base = temp->left;
        temp->left = (*base)->right;
        if((*base)->right != nullptr) (*base)->right->parent = temp;
        (*base)->right = temp;

        (*base)->parent = temp->parent;
        temp->parent = (*base);

        if ((*base)->factor < 0) temp->factor -= (*base)->factor - 1;
        else temp->factor -= -1;
        if (temp->factor < 0) (*base)->factor -= -1;
        else (*base)->factor -= -temp->factor - 1;

        if (abs((*base)->factor) - 1 > tAFac) correctBalanceUpPlus((*base));
        else if (abs((*base)->factor) + 1 < tAFac) correctBalanceUpMinus((*base));

        return *base;
    }
    Node<T> * bigRotateRight(Node<T> * temp) {
        rotateLeft(temp->left);
        temp = rotateRight(temp);
        return temp;
    }
    void printUp(Node<T> * temp) {
        while (temp != nullptr) {
            cout << temp->value << "  ";
            temp = temp->parent;
        }
        cout << endl;
    }
    Node<T> * minimum(Node<T> * current) const {
        if (current->left == nullptr) return current;
        else return minimum(current->left);
    }
    void popList(Node<T> * temp) {
        if (temp->parent == nullptr) {
            delete temp;
            root = nullptr;
        }
        else {
            correctBalanceUpMinus(temp);
            bool is_left = temp->parent->left == temp;
            if (is_left) temp->parent->left = nullptr;
            else temp->parent->right = nullptr;
            rebalanceUp(temp->parent);
            delete temp;
        }
    }
public:
    AvlTree() : _size(0), root(nullptr) {}
    ~AvlTree() {
        stack<Node<T>*> st;
        Node<T> * temp = root;
        while (!st.empty() || temp != nullptr) {
            if (temp != nullptr) {
                st.push(temp);
                temp = temp->left;
            }
            else {
                temp = st.top();
                st.pop();
                Node<T> * temp2 = temp;
                temp = temp->right;
//                delete temp2;
            }
        }
    }
    void insertNaive(const T& value) {
        if (root == nullptr) root = new Node<T>(value, nullptr);
        else {
            Node<T> * temp = root;
            bool isAdded = false;
            while (!isAdded) {
                if (temp->value <= value) {
                    if (temp->right == nullptr) {
                        temp->right = new Node<T>(value, temp);
                        isAdded = true;
                    }
                    else temp = temp->right;
                }
                else {
                    if (temp->left == nullptr) {
                        temp->left = new Node<T>(value, temp);
                        isAdded = true;
                    }
                    else temp = temp->left;
                }
            }
        }
        _size++;
    }
    void insert(const T& value) {
        if (root == nullptr) root = new Node<T>(value, nullptr);
        else {
            Node<T> * temp = root;
            bool isAdded = false;
            while (!isAdded) {
                if (temp->value <= value) {
                    if (temp->right == nullptr) {
                        temp->right = new Node<T>(value, temp);
                        temp = temp->right;
                        isAdded = true;
                    }
                    else {
                        temp = temp->right;
                    }
                }
                else {
                    if (temp->left == nullptr) {
                        temp->left = new Node<T>(value, temp);
                        temp = temp->left;
                        isAdded = true;
                    }
                    else {
                        temp = temp->left;
                    }
                }
            }
            correctBalanceUpPlus(temp);
            rebalanceUp(temp->parent);
        }
        _size++;
    }
    void pop(Node<T> * temp) {
        if (temp != nullptr) {
            if (temp->left == nullptr && temp->right == nullptr) {
                popList(temp);
            }
            else if (temp->right == nullptr) {
                if (temp->parent == nullptr) {
                    root = temp->left;
                    delete temp;
                }
                else {
                    correctBalanceUpMinus(temp);
                    bool is_left = temp->parent->left == temp;
                    if (is_left) temp->parent->left = temp->left;
                    else temp->parent->right = temp->left;
                    rebalanceUp(temp->parent);
                    delete temp;
                }
            }
            else if (temp->left == nullptr) {
                if (temp->parent == nullptr) {
                    root = temp->right;
                    delete temp;
                }
                else {
                    correctBalanceUpMinus(temp);
                    bool is_left = temp->parent->left == temp;
                    if (is_left) temp->parent->left = temp->right;
                    else temp->parent->right = temp->right;
                    rebalanceUp(temp->parent);
                    delete temp;
                }
            }
            else {
                correctBalanceUpMinus(temp);
                Node<T> * min = minimum(temp->right);
                temp->value = min->value;
                popList(min);
            }
        }
        _size--;
    }
    void pop(const T& value) {
        Node<T> * temp = find(value);
        pop(temp);
    }
    void popByK(int kStat) {
        stack<Node<T>*> st;
        Node<T> * temp = root;
        int k = 0;
        while (!st.empty() || temp != nullptr) {

            if (temp != nullptr) {
                st.push(temp);
                temp = temp->left;
            }
            else {
                temp = st.top();
                st.pop();
                if (kStat = k) pop(temp);
                temp = temp->right;
                k++;
            }
        }
    }
    int kStatistic(const T& value) {
        stack<Node<T>*> st;
        Node<T> * temp = root;
        int k = 0;
        while (!st.empty() || temp != nullptr) {

            if (temp != nullptr) {
                st.push(temp);
                temp = temp->left;
            }
            else {
                temp = st.top();
                st.pop();
                if (temp->value == value) return k;
                temp = temp->right;
                k++;
            }
        }
        return -1;
    }
    Node<T> * find(T value) {
        if (root == nullptr) return nullptr;
        else {
            Node<T> * temp = root;
            while (true) {
                if (temp->value == value) return temp;
                if (temp->value <= value) {
                    if (temp->right == nullptr) {
                        return nullptr;
                    }
                    else temp = temp->right;
                }
                else {
                    if (temp->left == nullptr) {
                        return nullptr;
                    }
                    else temp = temp->left;
                }
            }
        }
    }
    size_t size() const {
        return _size;
    }
    bool empty() const {
        return _size == 0;
    }
    void printRec(Node<T> * temp) const {
        if (temp != nullptr) {
            print_rec(temp->left);
            cout << temp->value << "  ";
            print_rec(temp->right);
        }
    }
    void print() const {
        stack<Node<T>*> st;
        Node<T> * temp = root;
        while (!st.empty() || temp != nullptr) {
            if (temp != nullptr) {
                st.push(temp);
                temp = temp->left;
            }
            else {
                temp = st.top();
                st.pop();
                cout << temp->value << "  ";
                temp = temp->right;
            }
        }
        cout << endl;
    }
    void printTree() const {
        queue<Node<T>*> q;
        q.push(root);
        int treeh = this->height();
        int h = 0;
        int row = 1;
        int w = 6;
        int maxw = w * pow(2, treeh - 1);
        for (int h = 0; h < treeh; h++) {
            for (int i = 0; i < pow(2, treeh - 1 - h) - 1; i++) {
                for (int j = 0; j < w / 2; j++) cout << " ";
            }
            for (int i = 0; i < row; i++) {

                Node<T> * temp = q.front();
                q.pop();
                if (temp == nullptr) {
                    cout.width(w);
                    cout << "null";
                }
                else {
                    cout.width(w - 3);
                    cout << temp->value;
                    if (temp->factor > 0) cout << " +" << temp->factor;
                    else if (temp->factor < 0) cout << " " << temp->factor;
                    else cout << "  0";
                }

                for (int k = 0; k < pow(2, treeh - 1 - h) - 1 && i != row - 1; k++) {
                    for (int j = 0; j < w; j++) cout << " ";
                }

                if (temp != nullptr && temp->left != nullptr) {
                    q.push(temp->left);
                }
                else q.push(nullptr);
                if (temp != nullptr && temp->right != nullptr) {
                    q.push(temp->right);
                }
                else q.push(nullptr);

            }
            cout << endl;
            row *= 2;
        }
    }
    int height() const {
        if (root == nullptr) return 0;
        int hmax = 0;
        heightRec(root, hmax, 1);
        return hmax;
    }
    void rotating() {
        cout << "Start" << endl;
        char ch;
        T elem;
        Node<T> * temp;
        while (ch != 'q') {
            cout << "operation: ";
            cin >> ch;
            switch (ch) {
                case '<':
                    this->printTree();
                    break;
                case 'l':
                    cout << "elem: ";
                    cin >> elem;
                    this->rotateLeft(find(elem));
                    break;
                case 'r':
                    cout << "elem: ";
                    cin >> elem;
                    this->rotateRight(find(elem));
                    break;
                case 'L':
                    cout << "elem: ";
                    cin >> elem;
                    this->bigRotateLeft(find(elem));
                    break;
                case 'R':
                    cout << "elem: ";
                    cin >> elem;
                    this->bigRotateRight(find(elem));
                    break;
                case '-':
                    cout << "elem: ";
                    cin >> elem;
                    this->pop(elem);
                    break;
                case '+':
                    cout << "elem: ";
                    cin >> elem;
                    this->insert(elem);
                    break;
                case '|':
                    cout << "elem: ";
                    cin >> elem;
                    printUp(find(elem));
                    break;
                case 'k':
                    cout << "elem: ";
                    cin >> elem;
                    cout << "k stat: " << kStatistic(elem) << endl;
                    break;
            }
        }
    }
};

int randint(int down, int up) {
    return rand() % (up - down) + down;
}

void test1() {
    AvlTree<int, ComparatorOver<int>> at;
    for (int i = 0; i < 10; i++) {
        at.insert(randint(0, 30));
    }
    at.printTree();
    cout << "Height: " << at.height() << endl;
}

void test2() {
    AvlTree<int, ComparatorOver<int>> at;
    const int N = 14;
    int arr[N] = {15, 21, 9, 24, 3, 39, 18, 30, 6, 12, 27, 7, 8, 4};
    for (int i = 0; i < N; i++) {
        at.insert(arr[i]);
    }
    at.printTree();

    at.rotating();
}

void test3() {
    AvlTree<int, ComparatorOver<int>> at;
    const int N = 9;
    for (int i = 0; i < N; i++) {
        at.insert(i);
    }
    at.printTree();
    cout << endl;
    at.print();
    at.rotating();
}

void mainTest() {
    AvlTree<int, ComparatorOver<int>> at;
    int N, f, s;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> f >> s;
        switch (f) {
            case 1:
                at.insert(-s);
                cout << at.kStatistic(-s) << endl;
                break;
            case 2:
                at.popByK(s);
                break;
        }
    }
}

int main() {
    srand(time(nullptr));
    mainTest();
    return 0;
}