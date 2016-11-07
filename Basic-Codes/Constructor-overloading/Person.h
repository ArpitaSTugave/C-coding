#pragma once

#include <iostream>

using namespace std;

class Person
{
private:
	string name;
public:
	Person();
	Person(string newName);
	string toString();
	//void setName(string newName);
	string getName();
};

