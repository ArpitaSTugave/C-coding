#include <iostream>
#include <string>
using namespace std;

class Test {
private:
	int id;
	static int count;
public:
	static int const MAX = 99;
public:
	Test() { // can use both static and otherwise
		id = count++;
	}

	int getId() {
		return id;
	}

	static void showInfo() { //can onky use static variables
		cout << count << endl;
	}
};

int Test::count = 0;

int main() {

	cout << Test::MAX << endl;

	Test test1;
	cout << "Object Id: " << test1.getId() << endl;

	Test test2;
	cout << "Object Id: " << test2.getId() << endl;

	Test::showInfo();

	return 0;
}
