#include <iostream>
#include <string>

using namespace std;

void show1(const int nElements, string texts[2]) { // can give any value 

	cout << sizeof(texts) << endl;

	for (int i = 0; i < nElements; i++) {
		cout << texts[i] << endl;
	}
}

void show2(const int nElements, string *texts) { 

	//cout << sizeof(texts) << endl;

	for (int i = 0; i < nElements; i++) {
		cout << texts[i] << endl;
	}
}

void show3(string (&texts)[3]) { // should give 3

	cout << sizeof(texts) << endl;

	for (int i = 0; i < sizeof(texts)/sizeof(string); i++) {
		cout << texts[i] << endl;
	}
}


int main() {

	string texts[] = { "apple", "orange", "banana" };

	cout << sizeof(texts) << endl;

	//show1(3, texts);

	//show2(3, texts);

	show3(texts);

	return 0;
}
