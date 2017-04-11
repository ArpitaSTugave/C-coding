#include <iostream>
#include <string>
#include<vector>

using namespace std;

template <typename T>
class Queue{
private:
	vector<T> datastore;
	int back;
	const static int front = 0;
	void shift(){
		for (int i = front; i < back; ++i) {
			datastore[i] = datastore[i + 1];
		}
		datastore.pop_back();
		--back;
	}
public:
	Queue() {
		back = -1;
	}

	void in(T value) {
		++back;
		datastore.push_back(value);
	}

	T out() {
		T retVal = datastore[front];
		shift();
		return retVal;
	}

	void show() {
		for (int i = front; i <= back; ++i) {
			cout << datastore[i] << " ";
		}
		cout << endl;
	}

	int count() {
		int cnt = 0;
		for (int i = front; i <= back; ++i) {
			++cnt;
		}
		return cnt;
	}

	T Qfront() {
		return datastore[front];
	}

	T Oback() {
		return datastore[back];
	}

	bool isEmpty() {
		if (back == -1){
			return true;
		}
		return false;
	}

	void clear() {
		for (int i = front; i <= back; ++i) {
			datastore[i] = "";
		}
	}

};

int main() {
	
	Queue<string> letters;
	letters.in("A");
	letters.in("B");
	letters.in("C");
	cout << "front: " << letters.Qfront() << endl;
	cout << "back: " << letters.Oback() << endl;
	cout << "cout: " << letters.count() << endl;
	letters.show();
	letters.out();
	cout << "front: " << letters.Qfront() << endl;
	cout << "back: " << letters.Oback() << endl;
	cout << "cout: " << letters.count() << endl;
	letters.show();
	letters.in("D");
	letters.in("E");
	cout << "front: " << letters.Qfront() << endl;
	cout << "back: " << letters.Oback() << endl;
	cout << "cout: " << letters.count() << endl;
	letters.show();
	return 0;

}
