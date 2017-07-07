#include <iostream>
#include "Cat.h"

using namespace std;

int main() {

	cout << "Class started" << endl;

	{
		Cat cat1;

		cat1.speak();
		cat1.jump();
	}

	cout << "Class ended" << endl;

	return 0;
}
