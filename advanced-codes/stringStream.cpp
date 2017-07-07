#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*
streams:
-sequence of bytes
-iostream: cout, cin, cerr
-fstream: ifstream, ofstream
*/

class Person{
private:
	string middle, first, last;
	int age;
public:
	Person(string m, string f, string l, int a){
		middle = m;
		first = f;
		last = l;
		age = a;
	}

	string toString() {
		stringstream stm;
		stm << middle << " " << first << " " << last << " " << age;
		return stm.str();
	}
};

int main() {

	Person aperson("arpita", "subhash", "tugave", 24);
	cout << aperson.toString() << endl;

	//cout

	cout.put('h');
	cout.put('e');
	cout.put('l');
	cout.put('l');
	cout.put('o');
	cout.put(' ').put('w').put('o').put('r').put('l').put('d').put('!').put('\n');
	cout << "hello world!" << endl; //cout has its own buffer
	cout << "hello lala!" << flush; // flushed this buffer, helps to avoid buffer overflow
	cout << "hello grr!" << ends; // write null character before flushing

	//cin
	string name;
	cout << "\n enter your name: " << endl;
	getline(cin, name);
	cout << "can eneter as much character within a line: \n" << name << endl;
	/*
	char c;
	c = cin.get();
	do{
		cout.put(c);
		c = cin.get();
	} while (!cin.eof()); // ctrl + c
	*/

	return 0;
}
