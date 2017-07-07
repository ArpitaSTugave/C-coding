#include <iostream>
#include <string>
using namespace std;

string mergeStrings(string str1, string str2) {

	string result;

	int s1 = str1.size();
	int s2 = str2.size();

	int s = (s1 >= s2) ? s2 : s1;
	int se = (s1 >= s2) ? s1 : s2;
	string stre = (s1 >= s2) ? str1 : str2;

	for (int i = 0; i < s; i++){
		result = result + str1[i] + "" + str2[i];
	}

	for (int i = s; i < se; i++){
		result = result + "" + stre[i];
	}


	return result;

}

int main() {

	string str1, str2;

	cin >> str1;
	cin >> str2;

	cout << mergeStrings(str1, str2) << endl;

	return 0;
}