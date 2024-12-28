#pragma once
#include "Instruction.h"
class J_Type : public Instruction
{
	string opcode;
	int address;
public:
	void input(string, int, vector<Lable>);
	string getBinary();
	void split(string, string[]);
};

