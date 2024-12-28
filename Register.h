#pragma once
#include <string>
using namespace std;

class Register
{
	string name;
	int index;
public:
	Register();
	Register(string);
	string getBinary();
	string getName();
};

