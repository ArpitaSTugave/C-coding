#include <iostream>
#include <string>
#include <list> //this is a doubly linked list, we will use it as a single list
using namespace std;

void display(list <int> names){
	list <int> ::iterator iter = names.begin();

	while (iter != names.end()){
		cout << *iter << endl;
		iter++;
	}
}

list <int> removeNodes(list <int> names , int x){
	list <int> ::iterator iter = names.begin();
	list <int> returned_list;

	while (iter != names.end()){
		cout << *iter << endl;
		int value = *iter;
		if (x >= value) {
			//cout << "found: " << value << endl;
			returned_list.push_back(value);
		}
		iter++;
	}

	return returned_list;
}

int main(){

	int size = 0;
	int value = 0;
	int x = 0;
	list <int> linked_list;

	cin >> size;

	for (int i = 0; i < size; i++){
		cin >> value;
		linked_list.push_back(value);
	}

	cin >> x;


	//linked_list.remove(7);
	//display(linked_list);
	//cout << x << endl;
	list <int> returned_list  = removeNodes(linked_list, x);
	display(returned_list);

	return 0;
}
