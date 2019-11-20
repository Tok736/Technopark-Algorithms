#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <set>

#define PR(arg) cout << #arg << " = " << (arg) << endl;
#define LINE(arg) cout << "// ==========  " << arg << "  ========== //" << endl;

using namespace std;

const size_t DEFAULT_SIZE = 4;
const double MAX_ALPHA = 0.5;

const int EMPTY = 0;
const int FULL = 1;
const int DELETED = 2;


class string_hash {
public:
    size_t operator()(const string &key, size_t size) {
        size_t hash_code = (key[0] * 101) % size;
        for (size_t i = 0; i < key.size(); i++) {
            hash_code = (hash_code + key[0] * 53) % size;
        }
        return hash_code;
    }
};

class int_hash {
public:
    size_t operator()(int key, size_t size) {
        return key % size;
    }
};



template <typename T, typename hasher>
class hash_table {
private:
    hasher hash_func;

    struct elem {
        elem() : mode(EMPTY) {}
        T key;
        size_t mode;
    };

    size_t _size;
    size_t _table_size;
    elem * _table;


    void init(size_t _table_size) {
        _size = 0;
        this->_table_size = _table_size;
        _table = new elem[_table_size];
    }
    void grow() {
        size_t new_table_size = _table_size * 2;
        elem * new_table = new elem[new_table_size];
        for (size_t i = 0; i < _table_size; i++) {
            if (_table[i].mode == FULL) {
                size_t hash_code = hash_func(_table[i].key, new_table_size);
                for (size_t j = 0; j < new_table_size; j++) {
                    size_t ind = next(hash_code, j, new_table_size);
                    if (new_table[ind].mode == EMPTY) {
                        new_table[ind].mode = FULL;
                        new_table[ind].key = _table[i].key;
                        break;
                    }
                }
            }
        }
        delete[] _table;
        _table = new_table;
        _table_size = new_table_size;
    }
    bool find(const T& key, size_t& finded_hash) {
        size_t hash_code = hash_func(key, _table_size);
        for (size_t i = 0; i < _table_size; i++) {
            size_t ind = next(hash_code, i, _table_size);
            if (_table[ind].mode == EMPTY) {
                return false;
            }
            if (_table[ind].mode == FULL && _table[ind].key == key) {
                finded_hash = ind;
                return true;
            }
        }
        return false;
    }
    size_t next(size_t hash_code, size_t i, size_t temp_table_size) {
        return (hash_code + i) % temp_table_size;
    }
public:
    hash_table() {
        init(DEFAULT_SIZE);
    }
    ~hash_table() {
        delete[] _table;
    }
    bool add(const T& key) {
        if (alpha() > MAX_ALPHA) grow();
        size_t temp = 0;
        if (find(key, temp)) return false;
        else {
            size_t hash_code = hash_func(key, _table_size);
            for (size_t i = 0; i < _table_size; i++) {
                size_t ind = next(hash_code, i, _table_size);
                if (_table[ind].mode == DELETED || _table[ind].mode == EMPTY) {
                    _table[ind].mode = FULL;
                    _table[ind].key = key;
                    _size++;
                    return true;
                }
            }
        }
    }
    bool has(const T& key) {
        size_t temp = 0;
        return find(key, temp);
    }
    bool delete_key(const T& key) {
        size_t finded_hash = 0;
        if (find(key, finded_hash)) {
            _table[finded_hash].mode = DELETED;
            _size--;
            return true;
        }
        return false;
    }

    size_t size() const {
        return _size;
    }
    size_t table_size() const {
        return _table_size;
    };
    double alpha() const {
        return static_cast<double>(_size) / _table_size;
    }

    void print() const {
        for (size_t i = 0; i < _table_size; i++) {
            if (_table[i].mode == FULL) {
                cout << _table[i].key << "   ";
            }
        }
        cout << endl;
    }
    void print_full() const {
        for (size_t i = 0; i < _table_size; i++) {
            if (_table[i].mode == FULL) {
                cout << _table[i].key << "   ";
            }
            if (_table[i].mode == DELETED) {
                cout << "*" << "   ";
            }
            if (_table[i].mode == EMPTY) {
                cout << "-" << "   ";
            }
        }
        cout << endl;
    };
    void clear() {
        delete[] _table;
        init(DEFAULT_SIZE);
    }
    bool is_empty() const {
        return _size == 0;
    }
};

string rand_word(size_t max_len) {
    string str;
    size_t len = rand() % max_len + 1;
    for (size_t i = 0; i < len; i++) {
        str.push_back('a' + rand() % 26);
    }
    return str;
}


void test1() {
    hash_table<string, string_hash> ht;
    for (int i = 0; i < 8; i++) {
        ht.add(rand_word(5));
    }
    ht.print();
}
void test2() {
    hash_table<string, string_hash> ht;

    for (int i = 0; i < 20; i++) {
        ht.add(rand_word(5));
        PR(ht.alpha());
    }

    ht.print();


}
void test3() {

    hash_table<string, string_hash> ht;

    int N;
    cout << "How much strings? ";
    cin >> N;
    cout << "Enter string: " << endl;
    string temp;
    for (int i = 0; i < N; i++) {
        cin >> temp;
        ht.add(temp);
    }
    cout << "table: " << endl;
    ht.print();
    cout << "try to find three elements" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "word to find: ";
        cin >> temp;
        if (ht.has(temp)) cout << "found" << endl;
        else cout << "not found" << endl;
    }



}
void test4() {
    hash_table<string, string_hash> ht;

    for (int i = 0; i < 10; i++) {
        ht.add(rand_word(1));
    }


    ht.print();

    ht.clear();


    if (ht.is_empty()) cout << "empty" << endl;
    ht.print();

    for (int i = 0; i < 5; i++) {
        ht.add(rand_word(10));
    }



    ht.print();
}
void test5() {
    hash_table<string, string_hash> ht;
    for (int i = 0; i < 30000; i++) {
        size_t randnum = rand() % 3;
        string str = rand_word(2);
        switch (randnum) {
            case 0:
                ht.add(str);
                break;
            case 1:
                ht.has(str);
                break;
            case 2:
                ht.delete_key(str);
                break;
        }
    }
}
void test6() {
    hash_table<int, int_hash> ht;
    for (int i = 1; i < 20; i++) {
        ht.add(i);
    }
    ht.print();
}

void main_test() {
    hash_table<string, string_hash> ht;
    char operation;
    string str;
    while (cin >> operation >> str) {
        switch (operation) {
            case '?':
            {
                if (ht.has(str)) cout << "OK" << endl;
                else cout << "FAIL" << endl;
                break;
            }
            case '+':
            {
                if (ht.add(str)) cout << "OK" << endl;
                else cout << "FAIL" << endl;
                break;
            }
            case '-':
            {
                if (ht.delete_key(str)) cout << "OK" << endl;
                else cout << "FAIL" << endl;
                break;
            }

//            case '<':
//                cout << "Your hash table: " << endl;
//                if (ht.is_empty()) cout << "No elements" << endl;
//                ht.print_full();
//                break;
        }
    }
}

void int_main_test() {
    hash_table<int, int_hash> ht;
    char operation;
    int num;
    while (!cin.eof()) {
        cin >> operation;
        switch (operation) {
            case '+':
                cin >> num;
                if (ht.add(num)) cout << "OK" << endl;
                else cout << "FAIL" << endl;
                break;
            case '?':
                cin >> num;
                if (ht.has(num)) cout << "OK" << endl;
                else cout << "FAIL" << endl;
                break;

            case '-':
                cin >> num;
                if (ht.delete_key(num)) cout << "OK" << endl;
                else cout << "FAIL" << endl;
                break;
            case '<':
                cout << "Your hash table: " << endl;
                if (ht.is_empty()) cout << "No elements" << endl;
                break;
        }
        ht.print_full();
    }
}

void set_test() {
    hash_table<int, int_hash> ht;
    set<int> st;
    char operation;
    int num;
    bool htFlag = false;
    bool stFlag = false;
    for (int i = 0; i < 1000; i++) {
        operation = '0' + static_cast<char>(rand() % 3);
        num = rand() % 1000;
        switch (operation) {
            case '0':
                if (ht.add(num)) htFlag = true;
                else htFlag = false;

                if (st.find(num) == st.end()) {
                    st.insert(num);
                    stFlag = true;
                }
                else {
                    stFlag = false;
                }

                break;
            case '1':
                if (ht.has(num)) htFlag = true;
                else htFlag = false;

                if (st.find(num) != st.end()) {
                    stFlag = true;
                }
                else {
                    stFlag = false;
                }

                break;
            case '2':
                if (ht.delete_key(num)) htFlag = true;
                else htFlag = false;

                if (st.find(num) != st.end()) {
                    st.erase(num);
                    stFlag = true;
                }
                else {
                    stFlag = false;
                }

                break;
            case '3':
                cout << "Your hash table: " << endl;
                if (ht.is_empty()) cout << "No elements" << endl;
                ht.print_full();
                for (auto it = st.begin(); it != st.end(); it++) {
                    cout << *it << "   ";
                }
                break;
        }
        if (stFlag != htFlag) {
            cout << "Your hash table: " << endl;
            if (ht.is_empty()) cout << "No elements" << endl;
            ht.print_full();
            for (auto it = st.begin(); it != st.end(); it++) {
                cout << *it << "   ";
            }
            cout << "Error" << endl;
        }
    }
}

int main() {
    srand(time(NULL));

//    cout << "test1 " << endl;
//	test1();
//    cout << endl << "test2" << endl;
//	test2();
//    cout << endl << "test3" << endl;
//	test3();
//    cout << endl << "test4" << endl;
//	test4();
//    cout << endl;


    main_test();


//    for (int i = 0; i < 100; i++) {
//        int * arr = new int[100];
//
//        for (int j = 0; j < 100; j++) {
//            int temp = arr[10000000 + j * -10034];
//        }
//
//        i--;
//    }
//    int_main_test();

//    for (int i = 0; i < 1000; i++) {
//        cout << i << endl;
//        set_test();
//    }
//    test6();

    return 0;

}