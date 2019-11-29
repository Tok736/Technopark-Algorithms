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
        Node(const Tn& value) :
                value(value), left(nullptr), right(nullptr), height(1), size(1)  {}
        Node * left, *right;
        size_t height;
        size_t size;
        Tn value;
    };
    Node<T> * root;
    Comp comp;

    Node<T> * rotateRight(Node<T> * current)
    {
        Node<T> * temp = current->left;
        current->left = temp->right;
        temp->right = current;
        fixHeight(current);
        fixHeight(temp);

        size_t sizeRightTree = (current->right == nullptr) ? 0 : current->right->size;
        size_t sizeLeftTree = (temp->left == nullptr) ? 0 : temp->left->size;
        temp->size += sizeRightTree + 1;
        current->size += -sizeLeftTree - 1;

        return temp;
    }
    Node<T> * rotateLeft(Node<T> * current)
    {
        Node<T> * temp = current->right;
        current->right = temp->left;
        temp->left = current;
        fixHeight(current);
        fixHeight(temp);

        size_t sizeLeftTree = (current->left == nullptr) ? 0 : current->left->size;
        size_t sizeRightTree = (temp->right == nullptr) ? 0 : temp->right->size;
        temp->size += sizeLeftTree + 1;
        current->size += -sizeRightTree - 1;

        return temp;
    }
    size_t nodeHeight(Node<T> * current) const {
        return (current != nullptr) ? current->height : 0;
    }
    int bFactor(Node<T> * current) const {
        return nodeHeight(current->right) - nodeHeight(current->left);
    }
    void fixHeight(Node<T> * current) {
        size_t hl = nodeHeight(current->left);
        size_t hr = nodeHeight(current->right);
        current->height = (hl > hr ? hl : hr) + 1;
    }
    Node<T> * balance(Node<T> * current)
    {
        fixHeight(current);
        if( bFactor(current)==2 )
        {
            if( bFactor(current->right) < 0 )
                current->right = rotateRight(current->right);
            return rotateLeft(current);
        }
        if( bFactor(current)==-2 )
        {
            if( bFactor(current->left) > 0  )
                current->left = rotateLeft(current->left);
            return rotateRight(current);
        }
        return current;
    }
    Node<T> * insertRec(Node<T>* current, int value)
    {
        if (current == nullptr) return new Node<T>(value);
        if(comp(current->value, value)){
            current->size += 1;
            current->left = insertRec(current->left, value);
        }
        else {
            current->size += 1;
            current->right = insertRec(current->right, value);
        }
        return balance(current);
    }
    Node<T> * findMin(Node<T> * current) const
    {
        current->size -= 1;
        return current->left ? findMin(current->left) : current;
    }
    Node<T>* removeMin(Node<T>* current) {
        if (current->left == nullptr) {
            return current->right;
        }
        current->left = removeMin(current->left);
        return balance(current);
    }
    Node<T>* removeRec(Node<T>* current, int value)
    {
        if (current == nullptr) return nullptr;
        if (comp(current->value, value)) {
            current->size -= 1;
            current->left = removeRec(current->left, value);
        } else if (comp(value, current->value)) {
            current->size -= 1;
            current->right = removeRec(current->right, value);
        } else {
            current->size -= 1;
            Node<T> *q = current->left;
            Node<T> *r = current->right;
            size_t currentSize = current->size;
            delete current;
            if (r == nullptr) return q;
            Node<T> *min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            min->size = currentSize;
            return balance(min);
        }
        return balance(current);
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
        remove(getByK(kStat)->value);
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
    void insert(int value) {
        root = this->insertRec(root, value);
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
        size_t treeh = nodeHeight(root);
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
                    cout.width(3);
                    cout << temp->height;
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
    void remove(int value) {
        root = removeRec(root, value);
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
                case '-':
                    cout << "elem: ";
                    cin >> elem;
                    this->remove(elem);
                    break;
                case '+':
                    cout << "elem: ";
                    cin >> elem;
                    this->insert(elem);
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
                    remove(getByK(k)->value);
                    break;
                case 'K':
                    cout << "k stat: ";
                    cin >> k;
                    cout << "elem: " << getByK(k)->value << endl;
                    break;
            }
        }
    }

};

int randint(int down, int up) {
    return rand() % (up - down) + down;
}
void test1() {
    AvlTree<int, ComparatorLess<int>> at;
    for (int i = 0; i < 10; i++) {
        at.insert(randint(0, 30));
    }
    at.printTree();
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


int main() {
    srand(time(nullptr));
    mainTest();
    return 0;
}