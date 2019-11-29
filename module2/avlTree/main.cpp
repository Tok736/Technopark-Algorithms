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
                value(value), left(nullptr), right(nullptr), parent(parent), factor(0), size(1)  {}
        Node * left, *right, *parent;
        int factor;
        size_t size;
        Tn value;
    };
    Node<T> * root;
    Comp comp;
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
    void correctSizeUpMinus(Node<T> * temp) {
        while (temp->parent != nullptr) {
            temp = temp->parent;
            temp->size -= 1;
        }
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

        size_t sizeLeftTree = (temp->left == nullptr) ? 0 : temp->left->size;
        size_t sizeRightTree = ((*base)->right == nullptr) ? 0 : (*base)->right->size;
        (*base)->size += sizeLeftTree + 1;
        temp->size += -sizeRightTree - 1;

        return *base;
    }
    Node<T> * bigRotateLeft(Node<T> * temp) {
        rotateRight(temp->right);
        temp = rotateLeft(temp);
        return temp;
    }
    Node<T> * rotateRight(Node<T> * temp) {
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

        // Here a little problem
        if (abs((*base)->factor) - 1 > tAFac) correctBalanceUpPlus((*base));
        else if (abs((*base)->factor) + 1 < tAFac) correctBalanceUpMinus((*base));

        size_t sizeRightTree = (temp->right == nullptr) ? 0 : temp->right->size;
        size_t sizeLeftTree = ((*base)->left == nullptr) ? 0 : (*base)->left->size;

        (*base)->size += sizeRightTree + 1;
        temp->size += -sizeLeftTree - 1;

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
            correctSizeUpMinus(temp);
            correctBalanceUpMinus(temp);
            bool is_left = temp->parent->left == temp;
            if (is_left) temp->parent->left = nullptr;
            else temp->parent->right = nullptr;
            rebalanceUp(temp->parent);
            delete temp;
        }
    }
public:
    AvlTree() : root(nullptr) {}
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
                delete temp2;
            }
        }
    }
    void insert(const T& value) {
        if (root == nullptr) root = new Node<T>(value, nullptr);
        else {
            Node<T> * temp = root;
            bool isAdded = false;
            while (!isAdded) {
                temp->size += 1;
                if (!comp(temp->value, value)) {
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
    }
    void pop(Node<T> * temp) {
        if (temp != nullptr) {
            if (temp->left == nullptr && temp->right == nullptr) {
                popList(temp);
            }
            else if (temp->right == nullptr) {
                if (temp->parent == nullptr) {
                    root = temp->left;
                    root->parent = nullptr;
                    delete temp;
                }
                else {
                    correctSizeUpMinus(temp);
                    correctBalanceUpMinus(temp);
                    bool is_left = temp->parent->left == temp;
                    if (is_left) {
                        temp->parent->left = temp->left;
                        temp->parent->left->parent = temp->parent;
                    }
                    else {
                        temp->parent->right = temp->left;
                        temp->parent->right->parent = temp->parent;
                    }
                    rebalanceUp(temp->parent);
                    delete temp;
                }
            }
            else if (temp->left == nullptr) {
                if (temp->parent == nullptr) {
                    root = temp->right;
                    root->parent = nullptr;
                    delete temp;
                }
                else {
                    correctSizeUpMinus(temp);
                    correctBalanceUpMinus(temp);
                    bool is_left = temp->parent->left == temp;
                    if (is_left) {
                        temp->parent->left = temp->right;
                        temp->parent->left->parent = temp->parent;
                    }
                    else {
                        temp->parent->right = temp->right;
                        temp->parent->right->parent = temp->parent;
                    }
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
    }
    void pop(const T& value) {
        Node<T> * temp = find(value);
        pop(temp);
    }
    Node<T> * getByK(int kStat) {
        Node<T> * temp = root;
        int k = (temp->left == nullptr) ? 0 : temp->left->size;
        while (true) {
            if (k == kStat) return temp;
            else {
                if (k > kStat) {
                    temp = temp->left;
                    if (temp == nullptr) break;
                    k += -1 - ((temp->right == nullptr) ? 0 : temp->right->size);
                }
                else {
                    temp = temp->right;
                    if (temp == nullptr) break;
                    k += 1 + ((temp->left == nullptr) ? 0 : temp->left->size);
                }
            }
        }
        return nullptr;
    }
    void popByK(int kStat) {
        pop(getByK(kStat));
    }
    int kStatistic(const T& value) {
        Node<T> * temp = root;
        int k = (temp->left == nullptr) ? 0 : temp->left->size;
        while (temp != nullptr) {
//            PR(k);
            if (temp->value == value) return k;
            else {
                if (comp(temp->value, value)) {
                    temp = temp->left;
                    if (temp == nullptr) break;
                    k += -1 - ((temp->right == nullptr) ? 0 : temp->right->size);
                }
                else {
                    temp = temp->right;
                    if (temp == nullptr) break;
                    k += 1 + ((temp->left == nullptr) ? 0 : temp->left->size);
                }
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
                if (comp(value, temp->value)) {
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
        return root->size;
    }
    bool empty() const {
        return root->size == 0;
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
        int w = 10;
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
                    cout.width(4);
                    cout << temp->value;
                    cout.width(3);
                    cout << temp->size;
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
        int k;
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
                case 'p':
                    this->print();
                    break;
                case 'd':
                    cout << "k stat: ";
                    cin >> k;
                    pop(getByK(k));
                    break;
                case 'K':
                    cout << "k stat: ";
                    cin >> k;
                    cout << "elem: " << getByK(k)->value << endl;
                    break;
                case 'f':
                    cout << "elem: ";
                    cin >> elem;
                    Node<T> * temp = find(elem);
                    if (temp == nullptr) {
                        cout << "nullptr" << endl;
                    }
                    else {
                        cout << "finded: " << temp->value << endl;
                    }
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
    for (int i = 0; i < 100; i++) {
        at.insert(randint(0, 30));
    }
    at.printTree();
    cout << "Height: " << at.height() << endl;
}

void test2() {
    AvlTree<int, ComparatorOver<int>> at;
    const int N = 14;
    int arr[N] = {15, 21, 9, 24, 3, 19, 18, 30, 6, 12, 4, 7, 10, 13/**/};
    for (int i = 0; i < N; i++) {
        at.insert(arr[i]);
    }
    at.printTree();

    at.rotating();
}

void test3() {
    AvlTree<int, ComparatorLess<int>> at;
    const int N = 16;
    for (int i = 0; i < N; i++) {
        at.insert(i);
    }
    at.printTree();
    cout << endl;
    at.print();
    at.rotating();
}

void mainTest() {
    AvlTree<int, ComparatorLess<int>> at;
    int N, f, s;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> f >> s;
        switch (f) {
            case 1:
                at.insert(s);
                cout << at.kStatistic(s) << endl;
                break;
            case 2:
                at.popByK(s);
                break;
        }
    }
}

void Test() {
    AvlTree<int, ComparatorLess<int>> at;
    int N, f, s, size;


    N = rand() % 30000 + 40000;

    for (int i = 0; i < N; i++) {
        cout << i << " ";
        f = (size > 0) ? rand() % 2 + 1 : 1;
        switch (f) {
            case 1:
                at.insert(rand() + rand() + rand());
                size++;
                break;
            case 2:
                size--;
                at.popByK(randint(0, size));
                break;
        }
    }
}

int main() {
    srand(time(nullptr));
//    mainTest();
    test2();

//    for (int i = 0; i < 1; i++) {
//        Test();
//    }
    return 0;
}