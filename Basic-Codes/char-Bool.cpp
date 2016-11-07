#include <iostream>
#include <iomanip>

using namespace std;

int main() {

	bool bValue = true;
	cout << bValue << endl;

	char cValue = 'g';
	cout << "cValue" << cValue << endl;
	cout << "size of cValue" << sizeof(cValue) << endl;

	wchar_t wValue = 'i';
	cout << "wValue" << (char)wValue << endl;
	cout << "char wValue" << wValue << endl;
	cout << "size of wValue" << sizeof(wValue) << endl;

	return 0;
}
