#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
	void speak() { cout << "Grrrr!!!" << endl; }
};

class Cat:public Animal {
public:
	void jump() { cout << "jumping!!!!" << endl; }
};

class Tiger :public Cat {
public: 
	void attackAnimal() { cout << "Sttcking!!!" << endl; }
};

int main() {

	Animal a;
	a.speak();

	Cat cat;
	cat.speak();
	cat.jump();

	Tiger tiger;
	tiger.speak();
	tiger.jump();
	tiger.attackAnimal();

	return 0;
}
