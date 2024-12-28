#include "Register.h"

Register::Register() {
	index = -1;
};


Register::Register(string name) {
	string regNames[] =	{	"zero", "at",
							"v0", "v1",
							"a0", "a1", "a2", "a3",
							"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
							"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
							"t8", "t9",
							"k0", "k1",
							"gp", "sp", "fp", "ra"
	};

	this->name = name;
	for (int i=0; i<32; i++)
		if (name == regNames[i] || name == to_string(i)) {
			index = i;
			break;
		}
}


string regD_2_5B(int d) { //5bit
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


string Register::getBinary() {
	if (index == -1)
		return "00000";
	return regD_2_5B(index);//regD_2_5B(index);
}

string Register::getName() {
	return name;
}