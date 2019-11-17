#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map>

#define PR(arg) cout << #arg << " = " << (arg) << endl;
#define LINE(arg) cout << "// ==========  " << arg << "  ========== //" << endl;

using namespace std;


const int DEFAULT_SIZE_old = 4;
const double MAX_ALPHA_old = 3.0;

size_t hash_func(const string &key, size_t size) {
	size_t res = (key[0] * 101) % size;
	for (int i = 0; i < key.size(); i++) {
		res = (res + key[i] * 101) % size;
	}
	return res;
}


template <typename T>
class hash_table_old {
private:
	size_t _table_size;
	size_t _size;
	template <typename T1>
	struct node {
		T1 key;
		node * next;
	};
	node<T> ** table;
	void full_clear() {
		for (int i = 0; i < _table_size; i++) {
			if (table[i] != NULL) {
				node<T> *temp1, *temp2;
				temp1 = table[i];
				temp2 = temp1->next;
				while (temp1 != NULL) {
					delete temp1;
					temp1 = temp2;
					if (temp2 != NULL) temp2 = temp2->next;
				}
			}
		}
		delete table;
		_size = 0;
	}
	void init(size_t _table_size) {
		this->_table_size = _table_size;
		table = new node<T> *[_table_size];
		for (int i = 0; i < _table_size; i++) {
			table[i] = NULL;
		}
	}
	void add_to_table(node<T> ** temp_table, size_t temp_table_size, size_t &temp_size, const T &key) {
		size_t hash_code = hash_func(key, temp_table_size);
		if (temp_table[hash_code] == NULL) {
			temp_table[hash_code] = new node<T>{ key, NULL };
			temp_size++;
		}
		else {
			node<T> * temp = temp_table[hash_code];
			bool flag = true;
			while (temp != NULL) {
				if (temp->key == key) flag = false;
				temp = temp->next;
			}
			if (flag) {
				temp_table[hash_code] = new node<T>{ key, temp_table[hash_code] };
				temp_size++;
			}
		}
	}
	void grow() {
		size_t new_size = 0;
		size_t new_table_size = 2 * _table_size;
		node<T> ** new_table = new node<T> *[new_table_size];;
		for (int i = 0; i < new_table_size; i++) {
			new_table[i] = NULL;
		}
		for (size_t i = 0; i < _table_size; i++) {
			node<T> * temp = table[i];
			while (temp != NULL) {
				add_to_table(new_table, new_table_size, new_size, temp->key);
				temp = temp->next;
			}
		}
		full_clear();
		_table_size = new_table_size;
		table = new_table;
		_size = new_size;
	}

public:
	hash_table_old(size_t _table_size = DEFAULT_SIZE_old) {
		init(_table_size);
	}
	~hash_table_old() {
		full_clear();
	}
	bool add(const T &key) {
		if (alpha() > MAX_ALPHA_old) grow();
		if (has(key)) return false;
		add_to_table(table, _table_size, _size, key);
		return true;
	}
	bool has(const T &key) const {
		for (size_t i = 0; i < _table_size; i++) {
			node<T> * temp = table[i];
			while (temp != NULL) {
				if (temp->key == key) return true;
				temp = temp->next;
			}
		}
		return false;
	}
	bool delete_key(const T &key) {
		size_t hash_code = hash_func(key, _table_size);
		if (table[hash_code] == NULL) return false;
		else if (table[hash_code]->next == NULL) {
			if (table[hash_code]->key == key) {
				delete table[hash_code];
				table[hash_code] = NULL;
				_size--;
				return true;
			}
			else return false;
		}
		else {
			node<T> * temp = table[hash_code];
			if (temp->key == key) {
				table[hash_code] = temp->next;
				delete temp;
				_size--;
				return true;
			}
			else {
				node<T> * temp2 = temp->next;
				while (temp2 != NULL) {
					if (temp2->key == key) {
						temp->next = temp2->next;
						delete temp2;
						_size--;
						return true;
					}
					temp = temp->next;
					temp2 = temp->next;
				}

			}
			return false;
		}
	}
	size_t size() const {
		return _size;
	}
	size_t table_size() const {
		return _table_size;
	}
	double alpha() const {
		return double(size()) / table_size();
	}
	void print() const {
		for (size_t i = 0; i < _table_size; i++) {
			node<T> * temp = table[i];
			while (temp != NULL) {
				cout << temp->key << endl;
				temp = temp->next;
			}
		}
	}
	void clear(size_t _new_table_size = DEFAULT_SIZE_old) {
		full_clear();
		init(_new_table_size);
	}
	bool is_empty() const {
		return _size == 0;
	}
};








const int DEFAULT_SIZE = 8;
const double MAX_ALPHA = 0.75;

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





template <typename T, typename hasher>
class hash_table {
private:
	hasher hash_func;

	struct elem {
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
		for (size_t i = 0; i < _table_size; i++) {
			_table[i].mode = EMPTY;
		}
	}
	void grow() {
		size_t new_table_size = _table_size * 2;
		elem * new_table = new elem[new_table_size];
		for (size_t i = 0; i < new_table_size; i++) {
			new_table[i].key = EMPTY;
		}
		for (size_t i = 0; i < _table_size; i++) {
			if (_table[i].mode == FULL) {
				size_t hash_code = hash_func(_table[i].key, new_table_size);
				if (new_table[hash_code].mode == EMPTY) {
					new_table[hash_code].key = _table[i].key;
					new_table[hash_code].mode = FULL;
				}
				else {
					for (size_t j = 1; i < new_table_size; i++) {
						size_t ind = try_to(hash_code, j);
						if (new_table[ind].mode == EMPTY) {
							new_table[ind].key = _table[i].key;
							new_table[ind].mode = FULL;
						}
					}
				}
			}
		}
		delete[] _table;
		_table = new_table;
		_table_size = new_table_size;
	}
	size_t try_to(size_t hash_code, size_t i) {
		return (hash_code + i * (i + 1) / 2) % _table_size;
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
		size_t hash_code = hash_func(key, _table_size);
		if (_table[hash_code].mode == EMPTY) {
			_table[hash_code].key = key;
			_table[hash_code].mode = FULL;
			_size++;
		}
		else {
			bool is_there_deleted = false;
			for (size_t i = 0; i < _table_size; i++) {
				size_t ind = try_to(hash_code, i);
				if (_table[ind].mode == FULL && _table[ind].key == key) {
					return false;
				}
				else if (_table[ind].mode == DELETED) {
					is_there_deleted = true;
				}
				else if (_table[ind].mode == EMPTY) {
					_table[ind].mode = FULL;
					_table[ind].key = key;
					_size++;
					return true;
				}
			}
			for (size_t i = 0; i < _table_size && is_there_deleted; i++) {
				size_t ind = try_to(hash_code, i);
				if (_table[ind].mode == DELETED) {
					_table[ind].key = key;
					_table[ind].mode = FULL;
					_size++;
				}
			}
		}
	}
	bool has(const T& key) {
		size_t hash_code = hash_func(key, _table_size);
		for (size_t i = 0; i < _table_size; i++) {
			size_t ind = try_to(hash_code, i);
			if (_table[ind].mode == EMPTY) {
				return false;
			}
			if (_table[ind].mode == FULL && _table[ind].key == key) {
				return true;
			}
		}
		return false;
	}
	bool delete_key(const T& key) {
		size_t hash_code = hash_func(key, _table_size);
		for (size_t i = 0; i < _table_size; i++) {
			size_t ind = try_to(hash_code, i);
			if (_table[ind].mode == EMPTY) {
				return false;
			}
			if (_table[ind].mode == FULL && _table[ind].key == key) {
				_table[ind].mode = DELETED;
				_size--;
				return true;
			}
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
		return double(_size) / _table_size;
	}

	void print() const {
		for (size_t i = 0; i < _table_size; i++) {
			if (_table[i].mode == FULL) {
				cout << _table[i].key << "   ";
			}
		}
		cout << endl;
	}
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
	hash_table_old<string> ht2;
	map<string, int> mp;
	for (int i = 0; i < 100; i++) {
		size_t randnum = rand() % 3;
		string str = rand_word(2);
		bool flag;
		bool flag2;
		bool flag3;
		switch (randnum) {
			case 0:
				flag = ht.add(str);
				flag2 = ht2.add(str);

				if (mp.find(str) == mp.end()) {
					flag3 = true;
					mp[str] = 0;
				}
				else flag3 = false;

				cout << flag << " " << flag2 << " " << flag3 << endl;
				break;
			case 1:
				flag = ht.has(str);
				flag2 = ht2.has(str);

				if (mp.find(str) != mp.end()) flag3 = true;
				else flag3 = false;

				cout << flag << " " << flag2 << " " << flag3 << endl;
				break;
			case 2:
				flag = ht.delete_key(str);
				flag2 = ht2.delete_key(str);

				if (mp.find(str) != mp.end()) {
					flag3 = true;
					mp.erase(str);
				}

				cout << flag << " " << flag2 << " " << flag3 << endl;
				break;
		}
	}
}


void main_test() {
	hash_table<string, string_hash> ht;
	char operation;
	string str;
	while (!cout.eof()) {
		cin >> operation;
		cin >> str;
		switch (operation) {
			case '+':
				if (ht.add(str)) cout << "OK" << endl;
				else cout << "FAIL" << endl;
				break;
			case '?':
				if (ht.has(str)) cout << "OK" << endl;
				else cout << "FAIL" << endl;
				break;

			case '-':
				if (ht.delete_key(str)) cout << "OK" << endl;
				else cout << "FAIL" << endl;
				break;
			case '<':
				cout << "Your hash table: " << endl;
				if (ht.is_empty()) cout << "No elements" << endl;
				ht.print();
				break;
		}
	}
}




int main() {
    srand(time(NULL));


//	test1();
//	test2();
//	test3();
//	test4();

//
//	main_test();

	for (size_t i = 0; i < 1; i++) {
		if (i % 10 == 0) cout << i << "  ";
		if (i % 100 == 0) cout << endl;
		test5();
	}
	cout << endl;

    return 0;

}