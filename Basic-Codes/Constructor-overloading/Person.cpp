#include "Person.h"


Person::Person()
{
	name = "George";
}

Person::Person(string name){

	this->name = name;

	cout << "Memory location of this: " << this << endl;
}

string Person::toString(){
	return "Person's name is: " + name;
}


string Person::getName(){

	return name;

}
