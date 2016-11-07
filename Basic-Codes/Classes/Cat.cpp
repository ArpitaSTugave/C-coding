#include <iostream>
#include "Cat.h"

using namespace std;

Cat::Cat() {
	cout << "cat created" << endl;

	happy = true;
}

Cat::~Cat() {
	cout << "cat destroyed" << endl;
}

void Cat::speak() {
	if (happy)
		cout << "Meoww!!!" << endl;
	else
		cout << "Sssss!!!!" << endl;
}

void Cat::jump() {
	cout << "jumping!!!!" << endl;
}
