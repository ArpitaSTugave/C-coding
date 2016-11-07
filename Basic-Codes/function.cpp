#include <iostream>
#include "utils.h"

using namespace std;

int main() {

	doSomething();

	int value = 4;

	const int number = 4;

	switch (value) 
	{
	case number :
		cout << "Value is 4" << endl;
		break;
	default:
		cout << "Unrecognized value" << endl;
		break;
	}

	return 0;
}

void doSomething() {
	cout << "Hello" << endl;
}
