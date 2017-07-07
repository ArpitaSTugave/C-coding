#include <iostream>
#include <string>

using namespace std;

class Animal {
private:
	string name;

public:
	Animal() { cout << "Animal created. " << endl; }
	Animal(const Animal& other) : name(other.name) { other.speak(); cout << "Animal created by copying. " << endl; }; //only costant methods can be called
	void setname(string name) { this->name = name; };
	void speak() const { cout << "my name is: " << name << endl; };
};

int main() {

	Animal animal1;
	animal1.setname("Freddy");
	animal1.speak();

	Animal animal2 = animal1;
	animal2.setname("Bob");
	animal2.speak();

	Animal animal3(animal1);
	animal3.speak();

	return 0;
}
