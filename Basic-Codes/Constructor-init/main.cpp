#include <iostream>
#include "Person.h"
#include <string>

using namespace std;

int main() {

	Person person1;
	Person person2("Georgia", 5);
	Person person3("lala" , 5);

	cout << "location of object" << &person1 << endl;

	cout << person1.toString() << endl;

	cout << "Name of person with get method: " << person1.getName() << endl;

	cout << "location of object" << &person2 << endl;

	cout << person2.toString() << endl;

	cout << "Name of person with get method: " << person2.getName() << endl;

	cout << "location of object" << &person3 << endl;

	cout << person3.toString() << endl;

	cout << "Name of person with get method: " << person3.getName() << endl;

	return 0;
}
