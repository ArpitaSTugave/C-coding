#include <iostream>
#include <string>

using namespace std;

int main() {

	int value = 4;

	const int number = 4;

	switch (value) 
	{
	case number :
		cout << "Value is 4" << endl;
		break;
	default:
		cout << "Unrecognized value" << endl;
		break;
	}

	return 0;
}
