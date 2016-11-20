#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Foo{
	T tVar;
public:
	Foo(T t) : tVar(t) { };
	Foo(){};
};
class FooDerived : public Foo<string> {};
int main(){
	FooDerived d;
	return 0;
}

//FooDerived constructor calls empty constructor, hence(a) is the option 
