#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main() {

	//initializations
	string str0;
	string str1 = "";
	string st2(str1); 
	string str3("hi there");
	string str4(10, '*'); // 10 as
	string str5 = "hello";
	string str6 = "world!";
	string str7 = str5 +  " " + str6;
	//string str8 = "hello" + "mymy"; // cannot contcatenate two literals together

	cout << str7 << endl;

	//compare strings
	string s1 = "clean";
	string s2 = "clear";

	if (s1 > s2)
		cout << s1 << " is greater than " << s2 << endl;
	else
		cout << s2 << " is greater than " << s1 << endl;

	cout << s1.compare(s2) << endl;

	//searching strings
	string s1_find = "a needle in a haystack needle";
	string word = "needle";
	int pos = s1_find.find(word); // find for first instance , rfind last instance

	cout << pos << endl;

	if (pos >= 0){
		cout << "needle found" << endl;
	}
	else
		cout << "no needle"  << endl;

	string numbers = "0123456789";
	string identifier = "name1";
	int pos1 = identifier.find_first_of(numbers);

	if (pos1 >= 0){
		cout << "illegal" << endl;
	}
	else
		cout << "legal" << endl;

	//substring and replace
	string s2_sub = s1_find.substr(pos, word.length());

	cout << s2_sub << endl;

	s2_sub = s1_find.substr(pos + word.length() + 1);
	
	cout << s2_sub << endl;

	s1_find.replace(pos, word.length(), "pin");

	cout << s1_find << endl;

	// C-Type strings

	char c1[] = { 'h', 'e', 'l', 'l', 'o' , '\0'};
	char c2[] = " word!";

	cout << c1 << " " << c2 << endl;

	int value = strcmp(c1, c2);

	cout << value << endl;
	/*
	#ifdef WIN
		strcat_s(c1,c2);
	#else
		strcat(c1, c2);
	#endif
	*/
	//cout << c1 << endl;

	return 0;
}
