#include "Person.h"


Person::Person()
{
	name = "George";
}

Person::Person(string newName){

	name = newName;
}

string Person::toString(){
	return "Person's name is: " + name;
}


string Person::getName(){

	return name;

}
