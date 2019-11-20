#include <iostream>

using namespace std;


#define PR(a) cout << #a << " = " << a << endl;



template <typename T, typename Comp>
class AvlTree {
private:
    template <typename Tn>
    class Node {
    public:
        Node(Node * left, Node * right, Node * parent, int factor, const Tn& value) :
            left(left), right(right), parent(parent), factor(factor), value(value) {}
        Node * left;
        Node * right;
        Node * parent;
        int factor;
        Tn value;
    };
    size_t _size;
public:

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}