#include <string>
#include<fstream>
#include<iostream>
#include<vector>
#include"Lable.h"

using namespace std;


string readLn(ifstream&);

void writeLn(ofstream& , string);

void deleteCommentAndSaveLable(ifstream&, ofstream&, vector<Lable>&);

int getType(string);

void Mips2Binary(ifstream&, ofstream&, vector<Lable>&);
