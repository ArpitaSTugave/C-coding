#include <iostream>
#include <string>

using namespace std;

class Animal {
private:
	string name;

public:
	Animal() { cout << "Animal created. " << endl; };
	Animal(const Animal& other) : name(other.name) { other.speak(); cout << "Animal created by copying. " << endl; }; //only costant methods can be called
	~Animal() { cout << "Destructor called" << endl; };
	void setname(string name) { this->name = name; };
	void speak() const { cout << "my name is: " << name << endl; };
};

int main() {

	Animal *pCat1 = new Animal();
	(*pCat1).setname("Freddy");
	(*pCat1).speak();
	pCat1->setname("Freddy");
	pCat1->speak();
	delete pCat1;

	cout << sizeof(pCat1) << endl;

	return 0;
}
