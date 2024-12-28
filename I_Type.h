#pragma once
#include "Instruction.h"
#include "Register.h"
#include <vector>
class I_Type : public Instruction
{
	string opcode;
	int immediate;
	Register rt, rs;
public:
	void input(string,int, vector<Lable>);
	string getBinary();
	void split(string, string[]);
};

