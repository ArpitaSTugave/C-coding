#include <iostream>
#include <string>

using namespace std;

int main() {

	char text[] = "hello";

	//cout << text << endl;

	int const NSIZE = sizeof(text) - 1;

	char *pStart = &text[0]; // text
	char *pEnd = &text[NSIZE - 1]; // text + NSIZE - 1

	cout << NSIZE << endl;

	while (pStart < pEnd)
	{

		char save = *pStart;
		*pStart = *pEnd;
		*pEnd = save;

		pStart++;
		pEnd--;
	}

	cout << text << endl;

	return 0;
}
