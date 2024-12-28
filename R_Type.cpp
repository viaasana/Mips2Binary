#include "R_Type.h"
#include <iostream>

using namespace std;

R_Type::R_Type() {
	opcode = "";
	shamt = ""; 
	funct = "";
}


void R_Type::split(string s, string output[]) {
	string temp = "";

	//get opcode
	int i = 0;
	for ( i = 0; i < s.length(); i++)
		if (s[i] == 32)
			break;
		else
			temp += s[i];
	output[0] = temp;

	if (temp[0] == 'j') {
		temp = "";
		i += 2;
		for (; i < s.length(); i++)
			if (s[i] == 32)
				break;
		output[1] = temp;
		return;
	}

	//get rd
	temp = "";
	i++;
	for (; i < s.length(); i++)
		if (s[i] == 32 || s[i] == ',')
			break;
		else if(s[i]!='$')
			temp += s[i];
	output[1] = temp;

	//get rs
	i++;
	if (s[i] == 32)
		i++;
	
	temp = "";
	for (; i < s.length(); i++)
		if (s[i] == 32 || s[i] == ',')
			break;
		else if (s[i] != '$')
			temp += s[i];
	output[2] = temp;

	// get rt or shamt
	i++;
	if (s[i] == 32)
		i++;
	
	temp = "";
	for (; i < s.length(); i++)
		if (s[i] == 32 || s[i] == ',')
			break;
		else if (s[i] != '$')
			temp += s[i];
	output[3] = temp;
}

bool isShamt(string s) {
	for (int i = 0; i < s.length(); i++)
		if (s[i] >= 'A' && s[i] <= 'z')
			return 0;
	return 1;
}

void R_Type::input(string in, int curentPC, vector<Lable> lables) {
	this->input(in);
}

void R_Type::input(string in) {
	string ingredient[4];
	split(in, ingredient);
	opcode = ingredient[0];
	if (opcode[0] == 'j') {
		
		rs = Register(ingredient[1]);
		return;
	}
	rd = Register(ingredient[1]);
	if (isShamt(ingredient[3])) {
		rt = Register(ingredient[2]);
		shamt = ingredient[3];
	}
	else {		
		rs = Register(ingredient[2]);
		rt = Register(ingredient[3]);
	}
}

string rD_2_5B(int d) { //5bit
	string s = "";
	for (int i = 4; i >= 0; i--) {
		bool flag = (d >> i) & 1;
		if (flag)
			s += '1';
		else
			s += '0';
	}
	return s;
}

string R_Type::getBinary() {
	string binary = "000000";
	string RType_instructions[] = { "add", "addu" , "and", "jr" };
	string function[] = { "100000", "100001" , "100100", "001000" };
	if (shamt.length() == 0)
		binary += rs.getBinary();
	else
		binary += "00000";
	int i = 0;
	binary += rt.getBinary();
	binary += rd.getBinary();
	for (; i < 4; i++) {
		if (opcode.compare(RType_instructions[i]) == 0)
			break;
	}
	if (shamt.length() == 0)
		binary += "00000";
	else
		binary += rD_2_5B(stoi(shamt));
	binary +=function[i];
	return binary;
}