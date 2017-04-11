#include <iostream>
#include <utility>
#include <map>
#include <string>
#include <set>

using namespace std;

int main() {
	//pair
	pair<string, string> name1("Arpita", "352555");
	cout << name1.first << " " << name1.second << endl;
	pair<string, int> name2("Arpita", 80);
	cout << name2.first << " " << name2.second << endl;
	
	//map
	map<string, string> numbers;
	numbers["johnes"] = "365";
	numbers["killa"] = "678";
	numbers["fatty"] = "456";
	cout << "Johnes: " << numbers["johnes"] << endl;
	cout << "size: " << numbers.size() << endl;
	numbers.erase("fatty");
	cout << "size: " << numbers.size() << endl;
	
	map<string, int> grades;
	grades["Jones"] = 78;
	grades["Smith"] = 83;
	grades["Green"] = 92;
	string name;
	cout << "Enter a name to find: ";
	cin >> name;

	if (grades.find(name) != grades.end()) {
		cout << name << ": " << grades[name] << endl;
	}
	else {
		cout << "not found" << endl;
	}

	double average = 0.0;
	int sum = 0;
	map<string, int>::iterator iter = grades.begin();
	while (iter != grades.end()) {
		cout << iter->second << endl;
		sum += iter->second;
		++iter;
	}
	cout << endl;
	average = sum / grades.size();
	cout << "Average: " << average << endl;

	//set
	set<string> words;
	string word = "";
	do {
		cout << "Enter a word: (quit ti quit) ";
		cin >> word;
		words.insert(word);

	} while (word != "quit");

	set<string>::iterator it = words.begin();

	while (it != words.end()) {
		cout << *it << " ";
		++it;
	}

	//multi map
	multimap<string, string> numbers1;
	numbers1.insert(pair<string, string>("Johnes", "123"));
	numbers1.insert(pair<string, string>("Smith", "245"));
	numbers1.insert(pair<string, string>("Brown", "111"));
	numbers1.insert(pair<string, string>("Johnes", "333"));
	numbers1.insert(pair<string, string>("Green", "834"));
	numbers1.insert(pair<string, string>("Johnes", "627"));
	string searchName = "Johnes";
	multimap<string, string>::iterator iter1 = numbers1.find(searchName);
	multimap<string, string>::iterator last = numbers1.upper_bound(searchName);
	for (; iter1 != last; ++iter1) {
		cout << iter1->first << ": " << iter1->second << endl;
	}

	return 0;
}
