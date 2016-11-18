#include<iostream>
#include<string>
#include<sstream>
#include<vector>

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

	virtual double grossPay(int hours) {
		return pay * hours;
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

	virtual double grossPay(int hours) {
		if (salaried) {
			return pay;
		}
		else {
			return pay * hours;
		}
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

	vector<Employee> emp;
	Employee emp1("Jhones", 25.00);
	Manager mag1("Smith", 50.00, true);

	emp.push_back(emp1);
	emp.push_back(mag1);

	for (int i = 0; i < emp.size(); ++i) {
		cout << emp[i].grossPay(40) << endl; //called grosspay of employee for both calls
	}

	Employee *emp2;
	emp2 = &emp1;
	cout << emp2->getName() << endl;
	cout << emp2->grossPay(40) << endl;
	emp2 = &mag1;
	cout << emp2->getName() << endl;
	cout << emp2->grossPay(40) << endl;

	vector<Employee*> emp3;

	emp3.push_back(&emp1);
	emp3.push_back(&mag1);

	for (int i = 0; i < emp.size(); ++i) {
		cout << emp3[i]->grossPay(40) << endl; //called grosspay of employee for both calls
	}

	return 0;
}
