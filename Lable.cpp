#include "Lable.h"



string D2B(int d) { //32bit
	string s = "";
	for (int i = 32; i >= 0; i--) {
		bool flag =  (d >> i) & 1;
		if (flag)
			s += '1';
		else
			s += '0';
	}
	return s;
}

string shiftLeft2(string s) {
	s += "00";
	return s;
}

Lable::Lable() { name = " "; address = 0; };

Lable::Lable(string s, int a) {
	name = s;
	address = a;
}

string Lable::getName() {
	return name;
}

int Lable::getAddress() {
	return address;
}

string Lable::getBinary() {
	string s = D2B(address);
	s.erase(0, 4);
	s.erase(s.length() - 2);
	return s;
}
