#include <iostream>
#include <string>

using namespace std;

class Animal {
private:
	string name;

public:
	void setname(string name) { this->name = name; };
	void speak() const { cout << "my name is: " << name << endl; };
};

int main() {

	const double PI = 3.141592;
	cout << PI << endl;

	Animal animal;
	animal.setname("Freddy");
	animal.speak();

	int value = 8;

	int * pValue = &value;

	cout << *pValue << endl;

	int number = 11;

	pValue = &number; // error if int * const pValue = &value;

	*pValue = 12; // error if const int *pValue = &value;

	cout << *pValue << endl;

	return 0;
}
