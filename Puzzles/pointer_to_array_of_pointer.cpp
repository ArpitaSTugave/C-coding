#include <iostream>
#include <string>
using namespace std;
const int MAX = 3;

int main() {

	// declare array of pointers
	int  var[MAX] = { 10, 100, 200 };
	int *ptr[MAX];

	for (int i = 0; i < MAX; i++) {
		ptr[i] = &var[i]; // assign the address of integer.
	}

	for (int i = 0; i < MAX; i++) {
		cout << "Value of var[" << i << "] = ";
		cout << *ptr[i] << endl;
	}

	int *(*a1) = ptr; //array of int pointers

	int *(*a2)[5]; //array of int pointers

	int **a3 = ptr; // array of pointers (2d)

	int **a4[5]; // array of pointers (2d)

	//correct option is: (c)

	return 0;
}
