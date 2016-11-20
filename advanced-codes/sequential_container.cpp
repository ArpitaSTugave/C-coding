#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
using namespace std;

void Display(list <string> names){
	list <string> ::iterator iter = names.begin();

	while (iter != names.end()){
		cout << *iter << endl;
		iter++;
	}
}

int find(deque <string> d, string value) {
	for (int i = 0; i < d.size(); i++){
		if (d.at(i) == value) {
			return i;
		}
	}
	return -1;
}

int main() {

	//vectors:
	vector <int> number(10);
	int sum = 0;

	for (int i = 1; i < 11; i++) {
		number.push_back(i);
	}

	for (int i = 0; i < number.size(); i++) {
		sum += number[i];
	}

	cout << "sum is: " << sum << endl;

	//lists:
	list <string> names;
	names.push_back("jill");
	names.push_back("marry");
	names.push_back("hill");
	Display(names);

	cout << "first item: " << names.front() << endl;
	cout << "last item: " << names.back() << endl;

	names.reverse();
	Display(names);

	names.sort();
	Display(names);

	names.push_front("Barry");
	Display(names);

	names.remove("hill");
	Display(names);

	names.pop_back();
	names.pop_front();
	Display(names);

	names.clear();
	if (names.empty()) {
		cout << "ceared" << endl;
	}
	else
		cout << "not cleared" << endl;

	//deque // double ended queue
	deque<string> line;
	line.push_back("customer 2");
	line.push_front("customer 1");
	line.push_back("customer 3");

	line.pop_back();
	line.pop_front();

	for (int i = 0; i < line.size(); i++) {
		cout << line[i] << endl;
	}

	line.push_back("customer 3");
	line.push_back("customer 4");
	line.push_back("customer 5");
	line.push_back("customer 6");
	line.push_back("customer 7");
	line.push_back("customer 8");

	cout << find(line, "customer 7") << endl;

	deque <string> ::iterator iter = line.begin();
	++iter;
	line.insert(iter, "arpita");

	for (iter = line.begin(); iter != line.end(); iter++){
		cout << *iter << endl;
	}

	return 0;
}
