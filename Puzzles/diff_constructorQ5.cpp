#include <iostream>
#include <string>
using namespace std;

class Someclass {
public:
	int x;
public:
	Someclass(int xx) : x(xx) { }
	Someclass(const Someclass& a) { x = a.x; x++; }
	void operator =(const Someclass& a1) { x = a1.x; x--; }
};
int main()
{
	Someclass a(4); // x is initialized to 4
	Someclass b = a; // constructor with object is called , hence 4++
	cout << b.x << endl;  // answer 5
	return 0;
}
