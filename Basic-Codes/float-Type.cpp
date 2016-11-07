#include <iostream>
#include <iomanip>

using namespace std;

int main() {

	float fValue = 123.456789;

	cout << "Size of float" << sizeof(float) << endl;
	cout << setprecision(20) << fixed << fValue << endl;
	cout << setprecision(20) << scientific << fValue << endl;

	return 0;
}
