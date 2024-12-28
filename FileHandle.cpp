#include "FileHandle.h"
#include "Instruction.h"
#include "R_Type.h"
#include "I_Type.h"
#include "J_Type.h"


void removeBOM(string& line) {  /// in case the file has been encoded
	if (line.size() >= 3 &&
		(unsigned char)line[0] == 0xEF &&
		(unsigned char)line[1] == 0xBB &&
		(unsigned char)line[2] == 0xBF) {
		line.erase(0, 3);
	}
}

string readLn(ifstream& f) {
	string s;
	getline(f, s);
	removeBOM(s);
	return s;
}

void writeLn(ofstream& f, string s) {
	f << s << "\n";
}
int removeSpace(string& s) {
	int i = 0;
	while (s[i] == 32 && i<s.length())
		i++;
	if (i == s.length()) {
		return 1;             // if s is emty return 1
	}
	s.erase(0, i);
	i = s.length() - 1;
	while (s[i] == 32)
		i--;
	if (i + 1 != s.length())
		s.erase(i + 1);
	for(int i=0; i<s.length(); i++)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] + 32;

	i = 0;
	while (i < (s.length() - 1)) {
		if ((s[i] == ' ' && s[i + 1] == ' ') || s[i] == '\t')
			s.erase(i, 1);
		else
			i++;
	}
	return 0;
}

int deleteComment(string& s, int i) {
	if (i == s.length() - 1)
		return 0;
	s.erase(i, s.length() - i);
	return (s.length() == 0); ///if s is just comment line
}

int isLabel(string s) {
	return (s[s.length() - 1] == ':');
}


void deleteCommentAndSaveLable(ifstream& fi, ofstream& fo, vector<Lable>& lables) {
	string s;

	int pc = 4194304;
	while (!fi.eof()) {
		s = readLn(fi);
		int isEmty = removeSpace(s);
		if (isEmty)
			continue;
		int i = 0;
		for ( i = 0; i < s.length(); i++) {
			if (s[i] == '#')
				break;
		}
		
		bool isCommentLine = deleteComment(s, i);
		if (isCommentLine) {
			continue;
		}
		if (isLabel(s)) {
			string name = "";
			int i = 0;
			while ( i<s.length() && s[i] != ' ' && s[i] != ':')
				name += s[i++];
			Lable lb(name, pc);
			lables.push_back(lb);
			continue;
		}
		string LableName = "";
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == ':') {
				Lable lb(LableName, pc);
				lables.push_back(lb);
				s.erase(0, (s[i + 1] == 32)?i+2:i+1);
				break;
			}
			LableName += s[i];
		}
		writeLn(fo, s);
		pc+=4;
	}

}

int getType(string s) { //-1: Rtype; 0: IType; 1: JType; 2: invallid input; 3: end of file (input emty)
	int i;
	string opcode = "";
	for (i = 0; i < s.length(); i++) {
		if (s[i] == 32)
			break;
		opcode += s[i];
	}
	if (opcode == "") return 3;
	string R[] = {"add", "addu", "and", "jr"};
	string I[] = { "addi", "addiu", "andi", "beq", "bne", "lbu", "lhu", "lui", "lw", "sw" };
	string J[] = { "j", "jal" };
	for (int i = 0; i < 4; i++)
		if (opcode.compare(R[i]) == 0)
			return -1;
	for(int i=0;i<10; i++)
		if (opcode.compare(I[i]) == 0)
			return 0;
	for(int i=0; i<2; i++)
		if (opcode.compare(J[i]) == 0)
			return 1;
	return 2;
}


void Mips2Binary(ifstream& in, ofstream& out, vector<Lable>& lableList) {
	int pc = 4194304;
	while (!in.eof()) {
		string s;
		s = readLn(in);
		Instruction* inst = NULL;
		int type = getType(s);
		if (type == -1)
			inst = new R_Type;
		else if (type == 0)
			inst = new I_Type;
		else if (type == 1)
			inst = new J_Type;
		else if(type==2){
			out << "Invalid input";
			return;
		}
		else
			return;
		inst->input(s, pc, lableList);
		out << inst->getBinary() << endl;
		pc += 4;
	}
}