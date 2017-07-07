#include <iostream>
#include <string>
#include<vector>

using namespace std;

template <typename T>
class Stack{
private:
	vector<T> datastore;
public:

	void push(T val) {
		datastore.push_back(val);
	}

	void pop() {
		datastore.pop_back();
	}

	T peek(){
		return datastore.end();
	}

	int count(){
		return datastore.size();
	}

	void clear() {
		for (int i = 0; i < datastore.size(); i++) {
			datastore[i] = "";
		}
	}

	void display() {
		for (int i = 0; i < datastore.size(); i++){

		}
	}

	bool isEmpty() {
		if (datastore.front() == ""){
			return true;
		}
		else false;
	}
};

int main() {
	
	//Stack
	Stack<string> names;
	names.push("Mary");
	names.push("Joe");
	cout << "number of items: " << names.count() << endl;
	if (!names.isEmpty()){
		names.pop();
	}
	cout << "number of items: " << names.count() << endl;
	names.clear();
	cout << "number of items: " << names.count() << endl;

	return 0;
}
