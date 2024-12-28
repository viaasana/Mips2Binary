#include "J_Type.h"


void J_Type::split(string in, string out[]) {
	string temp = "";
	int i = 0;
	for (; i < in.length(); i++) {
		if (in[i] == 32)
			break;
		temp += in[i];
	}
	out[0] = temp;
	temp = "";
	i++;
	for (; i < in.length(); i++) {
		if (in[i] == 32) break;
		temp += in[i];
	}
	out[1] = temp;
}

void J_Type::input(string in, int curentPC, vector<Lable> lableList) {
	string ingredient[2] = { "jal", "getName" };
	string JType_instructions[] = { "j", "jal" };
	string JType_opcode[] = { "000010", "000011" };
	split(in, ingredient);
	for(int i=0; i<2; i++)
		if (JType_instructions[i].compare(ingredient[0]) == 0) {
			opcode = JType_opcode[i];
			break;
		}
	for(int i=0; i<lableList.size(); i++)
		if (ingredient[1].compare(lableList[i].getName()) == 0) {
			address = lableList[i].getAddress();
			break;
		}
}

string Jtype_D2B(int adr) {
	string out = "";
	for (int i = 25; i >= 0; i--) {
		int flag = (adr >> i) & 1;
		if (flag)
			out += "1";
		else
			out += "0";
	}
	return out;
}

string J_Type::getBinary() {
	int JumAddreess = (address) >> 2;
	return opcode + Jtype_D2B(JumAddreess);
}