#pragma once
#include<iostream>
using namespace std;

namespace anim {

	const string CATNAME = "Simha";

	class Cat
	{
	public:
		Cat();
		virtual ~Cat();
		void speak();
	};

}

