#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
	/*
	virtual void speak() {
		cout << "hello animals!!!" << endl;
	}
	*/ // virtual class ; class called method will be used else base class method
	virtual void speak() = 0; //abstract class ; should be initialized in child class
	virtual ~Animal() {};
};

class Cat : public Animal {
public: 
	virtual void speak() {
		cout << "hello kitty!!!" << endl;
	}
	virtual ~Cat() {};
};

class HouseCat : public Cat {
public:
	virtual void speak() {
		cout << "hello home!!!" << endl;
	}
	virtual ~HouseCat() {};
};

int main() {

	Animal *pAnimal = new Cat; // cannot instantiate abstract class= Animal

	pAnimal->speak();

	delete pAnimal;

	return 0;
}
