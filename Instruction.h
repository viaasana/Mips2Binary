#pragma once
#include <string>
#include "Lable.h"
#include <vector>
using namespace std;

class Instruction
{
protected:
	string str;
public:
	virtual void input(string);
	virtual void input(string, int, vector<Lable>);
	virtual string getBinary();
	virtual void split(string, string[]);
};

