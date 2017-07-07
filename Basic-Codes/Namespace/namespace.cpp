#include <iostream>
#include <string>
#include "Animal.h"
#include "Cat1.h"

using namespace std;
using namespace anim;

int main() {

	Cat cat;
	cat.speak();

	anim::Cat cat1;
	cat1.speak();

	cats::Cat cat2;
	cat2.speak();

	cout << anim::CATNAME << endl;
	cout << cats::CATNAME << endl;

	cout << CATNAME << endl;



	return 0;
}
