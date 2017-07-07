#include <iostream>
#include <string>
using namespace std;

class Machine {
private:
	int id;

public:
	Machine() : id(0) { cout << "Machine no-argument constructor is called." << endl; }
	Machine(int id) : id(id) { cout << "Machine parameterized constructor is called." << endl; }
	void info() { cout << "ID: " << id << endl;  }
};

class Vehicle: public Machine {

public:
	Vehicle() { cout << "Vehicle no-argument constructor is called." << endl; }
	Vehicle(int id) : Machine(id) { cout << "Vehicle parameterized constructor is called." << endl; }
};

class Car : public Vehicle {

public:
	Car() : Vehicle(999) { cout << "Car no-argument constructor is called." << endl; }
};

int main() {

	Car car;
	car.info();
	return 0;
}
