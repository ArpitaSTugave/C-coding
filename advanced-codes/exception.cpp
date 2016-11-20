#include <iostream>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

const int deivideBYZero = 1;
/*
void mightGoWrong() {
	bool error = true;

	if(error) {
		throw 8;
	}
}

*/

class DivideByZero: public runtime_error {
public:
	DivideByZero() : runtime_error("Divided by zero") {};

};

double divide(double numer, double denom) {
	if (denom ==0 ){
		throw DivideByZero();
	}
	else
		return numer/denom;
}

int main() {

	//mightGoWrong();
/*
	try {
		int nume = 10;
		int denom = 0;

		if(denom == 0)
			throw deivideBYZero;
		else
		cout << nume/denom << endl;
	}
	catch(int e){
		if (e == deivideBYZero){
			cout << "cant divide by zero" << endl;
		}
	}
*/
	int numer , denom , ratio;
	cout << "Enter numerator: " << endl;
	cin >> numer;
	cout << "Enter denominator: " << endl;
	cin >> denom;

	try {
		ratio = divide(numer, denom);
		cout << ratio << endl;
	}
	catch(DivideByZero &e){
		cout << e.what() << endl;
	}
	return 0;
}
