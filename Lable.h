#pragma once
#include<string>

using namespace std;
class Lable
{
	string name;
	int address;

public:
	Lable();
	Lable(string, int);
	string getName();
	int getAddress();
	string getBinary();
};

