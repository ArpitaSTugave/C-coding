#include <iostream>
#include <string>
#include <vector> 
using namespace std;

void display(vector <int> names){
	vector <int> ::iterator iter = names.begin();

	while (iter != names.end()){
		cout << *iter << endl;
		iter++;
	}
}

int funcCost(int  val, vector <int> R, vector <int> C, int D) {

	vector <int> ::iterator iter1 = R.begin();
	vector <int> ::iterator iter2 = C.begin();
	int i = 1; int c_max = 100000, return_val = 0;

	while (iter1 != R.end() && iter2 != C.end()){
		int iter_val = *iter1;
		int C_val = *iter2;
		if ((val + iter_val) >= D){
			if (C_val < c_max) {
				c_max = C_val; return_val = i;
			}
		}
		iter1++; iter2++; i++;
	}

	return return_val;
}

int main(){

	//get input
	string rawInput;
	vector<int> R;
	vector<int> C;

	getline(cin, rawInput);

	const int n = rawInput[0] - '0';
	int D = rawInput[2] - '0';

	getline(cin, rawInput);

	for (int i = 0; i < rawInput.size(); i = i+2) {
		R.push_back(rawInput[i] - '0');
	}

	//display(R);

	getline(cin, rawInput);

	for (int i = 0; i < rawInput.size(); i = i + 2) {
		C.push_back(rawInput[i] - '0');
	}

	//display(C);

	vector <int> ::iterator iter = R.begin();

	while (iter != R.end()){
		//cout << *iter << endl;
		int pass_val = *iter;
		
		cout << funcCost(pass_val, R,  C, D) << " ";

		iter++;
	}

	cout << endl;
	

	return 0;
}