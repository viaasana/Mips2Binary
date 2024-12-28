#include "I_Type.h"


void I_Type::split(string s, string output[]) {
	string temp = "";

	//get opcode
	int i = 0;
	for (i = 0; i < s.length(); i++)
		if (s[i] == 32)
			break;
		else
			temp += s[i];
	output[0] = temp;
	//get rt
	temp = "";
	i++;
	for (; i < s.length(); i++)
		if (s[i] == 32 || s[i] == ',')
			break;
		else if (s[i] != '$')
			temp += s[i];
	output[1] = temp;

	//get rs and immediate
	i++;
	if (s[i] == 32)
		i++;
	if (s[i] == '$') {			//if type like addi $t0, $t1, 5
		temp = "";
		for (; i < s.length(); i++)
			if (s[i] == 32 || s[i] == ',')
				break;
			else if (s[i] != '$')
				temp += s[i];
		output[2] = temp;

		i++;
		if (s[i] == 32)
			i++;

		temp = "";
		for (; i < s.length(); i++)
			if (s[i] == 32 || s[i] == ',')
				break;
			else
				temp += s[i];
		output[3] = temp;
	}
	else {	
		temp = "";// if type like sw $t0, 8($t2);
		for (; i < s.length(); i++) {
			if (s[i] == 32 || s[i] == '(')
				break;
			temp += s[i];
		}
		output[3] = temp;
		temp = "";
		i++;
		for (; i < s.length(); i++) {
			if (s[i] == 32 || s[i] == ')')
				break;
			temp += s[i];
		}
		output[2] = temp;
	}
}

void I_Type::input(string in, int curentPC, vector<Lable> lableList) {
	string ingredient[4];
	string IType_instructions[] = { "addi", "addiu", "andi", "beq", "bne", "lbu", "lhu", "lui", "lw", "sw" };
	string IType_opcode[] = { "001000", "001001", "001100", "000100", "000101", "100100", "100101", "001111", "100011", "101011" };
	split(in, ingredient);
	int i = 0;
	for (; i < 10; i++)
		if (ingredient[0] == IType_instructions[i])
			break;
	opcode = IType_opcode[i];
	if (ingredient[3][0] >= 'A' && ingredient[3][0] <= 'z') {
		rs = Register(ingredient[1]);
		rt = Register(ingredient[2]);
		for (int i = 0; i < lableList.size(); i++) {
			if (ingredient[3].compare(lableList[i].getName()) == 0) {
				int branchAddress = lableList[i].getAddress() - curentPC - 4;
				immediate = branchAddress >> 2;
				break;
			}
		}
	}
	else {
		rt = Register(ingredient[1]);
		rs = Register(ingredient[2]);
		immediate = stoi(ingredient[3]);
	}
}

string I_D2B(int in) {
	string out = "";
	for (int i = 15; i >= 0; i--) {
		bool flag = (in >> i) & 1;
		if (flag == 0)
			out += '0';
		else
			out += '1';
	}
	return out;
}

string I_Type::getBinary() {
	return opcode + rs.getBinary() + rt.getBinary() + I_D2B(immediate);
}