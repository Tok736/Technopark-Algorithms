#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>



#define PR(arg) cout << #arg << " = " << (arg) << endl;
#define LINE(arg) cout << "// ==========  " << arg << "  ========== //" << endl;

using namespace std;

class list {
private:
	int size;
	struct elem {
		int value;
		elem * next;
	};
	elem * head;
	elem * tail;
public:
	list();
	list(int size);

	int find(int k);
	void del(elem * &prev, elem * &deleting);


	void print();
};

list::list() {
	head = NULL;
}

list::list(int size) {
	this->size = size;
	head = NULL;
	head = new elem{ 1, NULL };
	elem * temp = head;
	elem * temp2;
	for (int i = 1; i < size; i++) {
		temp2 = new elem{ i + 1, NULL };
		temp->next = temp2;
		temp = temp->next;
	}
	temp->next = head;
	tail = temp;
}

int list::find(int k) {
	elem * prev_temp = tail;
	elem * temp = head;
	elem * temp2;
	int N = size;
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < k - 1; j++) {
			prev_temp = prev_temp->next;
			temp = temp->next;
		}
		temp2 = temp->next;
		del(prev_temp, temp);
		temp = temp2;
	}
	return head->value;
}

void list::del(elem * &prev, elem * &deleting) {
	if (deleting == head) head = deleting->next;
	elem * temp = deleting->next;
	delete deleting;
	prev->next = temp;
	deleting = temp;
	size--;
}

void list::print() {
	elem * temp = head;
	for (int i = 0; i < size; i++) {
		cout << temp->value << "   ";
		temp = temp->next;
	}
	cout << endl;
}




void test() {
	int N, k;

	cin >> N;
	cin >> k;

	list * lst = new list(N);


	cout << lst->find(k) << endl;
    delete lst;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	test();

	return 0;
}