#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
void Display(T arr[], int size){
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

template <typename T>
T Maxfunc(T &arg1, T &arg2) {
	if (arg1 > arg2) {
		return arg1;
	}
	else
		return arg2;
}

template <typename T>
class Stack
{
private:
	int top;
	T array[100];
public:
	Stack() {
		top = -1;
	}

	void push(T value){
		++top;
		array[top] = value;
	}

	T pop() {
		T ret = array[top];
		array[top] = 0;
		--top;
		return ret;
	}

	T val() {
		return array[top];
	}
};

//template specialization:
template <>
class Stack<string>
{
private:
	int top;
	string array[100];
public:
	Stack() {
		top = -1;
	}

	void push(string value){
		++top;
		array[top] = value;
	}

	string pop() {
		string ret = array[top];
		array[top] = "";
		--top;
		return ret;
	}

	string val() {
		return array[top];
	}

};

template <typename T, typename U>
T max1(T arg1, U arg2) {
	return (arg1 >= arg2) ? arg1 : arg2;
}

template <typename T, typename U>
class Cmap{
private:
	vector <T> key;
	vector <U> value;
public:
	void insert(T k, U v){
		key.push_back(k);
		value.push_back(v);
	}
	void show(int n) {
		cout << "key and value:" << key[n] << "," << value[n] << endl;
	}
};

int main() {

	Cmap<string, int> cc;
	cc.insert("hi", 25);
	cc.insert("hello", 2500);
	cc.show(1);

	int val1 = 130;
	double val2 = 12.5;
	cout << max1(val1, val2) << endl;

	Stack<double> sta;
	sta.push(12);
	sta.push(14);
	cout << sta.val() << endl;
	sta.pop();
	cout << sta.val() << endl;

	Stack<string> sta1;
	sta1.push("hi");
	sta1.push("hello");
	cout << sta1.val() << endl;
	sta1.pop();
	cout << sta1.val() << endl;

	const int size = 10;
	int numbers[size];
	for (int i = 0; i < size; i++) {
		numbers[i] = 2 * i;
	}
	Display(numbers, size);

	string strn[] = { "hi", "hi1", "hi2", "hi3", "hi4", "hi5", "hi6", "hi7", "hi8", "hi9" };
	Display(strn, size);

	int in1 = 10;
	int in2 = 12;
	cout << Maxfunc(in1, in2) << endl;
	double do1 = 13.9;
	double do2 = 2.00;
	cout << Maxfunc(do1, do2) << endl;
	string str1 = "laal1";
	string str2 = "lala2";
	cout << Maxfunc(str1, str2) << endl;

	return 0;
}
