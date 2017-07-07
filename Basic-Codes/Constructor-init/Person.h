#pragma once

#include <iostream>

using namespace std;

class Person
{
private:
	string name;
	int age;
public:
	Person() : name("unnammed"), age(0) {};
	Person(string name , int age);
	string toString();
	//void setName(string newName);
	string getName();
};

