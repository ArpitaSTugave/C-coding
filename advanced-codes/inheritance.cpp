
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

//base class
class Employee {
protected:
	string name;
	double pay;
public: 
	Employee() {
		name = "";
		pay = 0;
	}

	Employee(string empName, double payRate) {
		name = empName;
		pay = payRate;
	}

	~Employee() {};

	string getName() const {
		return name;
	}

	void setName(string empname) {
		name = empname;
	}

	int getPay() {
		return pay;
	}

	void setPay(int payRate) {
		pay = payRate;
	}

	string toString() {
		stringstream stm;
		stm << name << ":" << pay;
		return stm.str();
	}
};

class Manager : public Employee {
private:
	bool salaried;

public:

	Manager() : salaried(true) {};

	Manager(string name, double payRate, bool isSalaried) : Employee(name, payRate) {
		salaried = isSalaried;
	}

	~Manager() {};

	bool getSalaried() {
		return salaried;
	}

	string toString() {
		stringstream stm;
		string salary;
		if (salaried) {
			salary = "Salaried";
		}
		else {
			salary = "Hourly";
		}
		stm << name << ": " << pay
			<< ": " << salary << endl;
		return stm.str();
	}
};

int main() {
	Employee emp1("Mary Smith", 15.00);
	cout << "Employee name: " << emp1.getName() << endl;
	cout << "Employee pay rate: " << emp1.getPay() << endl;
	Manager emp2("Bob Borwn", 1500, true);
	cout << "Employee name: " << emp2.getName() << endl;
	cout << "Employee pay rate: " << emp2.getPay() << endl;
	cout << "Employee name: " << emp2.getSalaried() << endl;

	return 0;
}
