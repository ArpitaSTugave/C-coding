#include <iostream>
#include <string>
using namespace std;

namespace firstnums {
	int num1 = 10;
	int num2 = 12;
}

namespace secondnums {
	int num1 = 1;
	int num2 = 2;
}

namespace minMax {
	int max(int num1, int num2){
		if (num1 > num2)
			return num1;
		else
			return num2;
	}

	int min(int num1, int num2){
		if (num1 < num2)
			return num1;
		else
			return num2;
	}
}

namespace People{
	class Person{
	private:
		string name;
		string sex;
	public:
		Person(string n, string s){
			name = n;
			sex = s;
		}
		string getPerson(){
			return sex + ", " + name;
		}
	};
}
int main() {

	cout << "num1 in firstnums:" << firstnums::num1 << endl;
	cout << "num1 in secondnums: " << secondnums::num1 << endl;

	cout << "num2 in firstnums:" << firstnums::num2 << endl;
	cout << "num2 in secondnums: " << secondnums::num2 << endl;

	{
		using namespace firstnums;
		cout << "num1 in firstnums:" << num1 << endl;
		cout << "num2 in firstnums:" << num2 << endl;
	}

	{
		using namespace secondnums;
		cout << "num1 in secondnums:" << num1 << endl;
		cout << "num2 in secondnums:" << num2 << endl;
	}

	{
		using namespace minMax;
		using namespace People;
		int a, b;
		cout << "enter a number: " << endl;
		cin >> a;
		cout << "enter another number: " << endl;
		cin >> b;
		cout << min(a, b) << endl;
		cout << max(a, b) << endl;
		Person p1("Jane Doe", "male");
		cout << p1.getPerson() << endl;
	}

	return 0;
}
