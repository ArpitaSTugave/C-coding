#include "Person.h"


Person::Person(string name, int age) : name(name) , age(age){


	cout << "Memory location of this: " << this << endl;
}

string Person::toString(){
	return "Person's name is: " + name;
}


string Person::getName(){

	return name;

}
