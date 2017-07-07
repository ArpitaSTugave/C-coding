#include <iostream>
#include <string>
#include<vector>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
void display(vector<T> v) {
	for (int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

int main() {
	
	vector<int> numbers;
	for (int i = 1; i < 10; i++) {
		numbers.push_back(i);
	}
	int sum = 0;
	for (int i = 0; i < numbers.size(); i++) {
		sum += numbers[i];
	}
	cout << "Sum: " << sum << endl;
	int sum1 = accumulate(numbers.begin(), numbers.end(), 0);
	cout << "Sum1: " << sum1 << endl;
	vector<string> words;
	words.push_back("a");
	words.push_back("man");
	words.push_back("went");
	words.push_back("uphill");
	words.push_back("to");
	words.push_back("fall");
	words.push_back("and");
	words.push_back("die");
	string palindrome = accumulate(words.begin(), words.end(), string(""));
	cout << "String: " << palindrome << endl;

	display(numbers);
	//fill(numbers.begin(), numbers.end(), 0);
	replace(numbers.begin(), numbers.end(), 5, 10);
	display(numbers);
	display(words);
	//fill(words.begin(), words.end(), string(""));
	replace(words.begin(), words.end(), string("die"), string("live"));
	display(words);
	sort(words.begin(), words.end());
	display(words);

	const int sizeNumbers = 10;
	int numbers1[] = { 10, 1, 9, 2, 8, 3, 7, 4, 6, 5 };
	vector<int> nums(numbers1, numbers1 + sizeNumbers);
	display(nums);
	sort(nums.begin(), nums.end());
	display(nums);

	copy(numbers.begin(), numbers.end(), back_inserter(nums));
	display(nums);
	// front inserter exists with deque

	for (vector<int>::reverse_iterator riter = nums.rbegin(); riter != nums.rend(); ++riter){
		cout << *riter << " ";
	}
	cout << endl;

	return 0;
}
