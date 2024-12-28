#pragma once
#include "Instruction.h"
#include "Register.h"
class R_Type : public Instruction
{
	string opcode, shamt, funct;
	Register rs, rt, rd;
	bool isShamt;
public:
	R_Type();
	void input(string);
	void input(string, int, vector<Lable>);
	string getBinary();
	void split(string, string[]);
};

