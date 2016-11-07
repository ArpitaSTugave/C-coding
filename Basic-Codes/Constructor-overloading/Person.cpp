#include "Person.h"


Person::Person()
{
	name = "George";
}

Person::Person(string name){

	this->name = name;
}

string Person::toString(){
	return "Person's name is: " + name;
}


string Person::getName(){

	return name;

}
