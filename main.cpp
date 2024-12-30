#include "FileHandle.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Lable.h"
#include <vector>


using namespace std;



int main() {
	string fileName = "testcase1.mips";
	string tempPath = "tempFile.txt";
	string outPath = "out.txt";
	vector<Lable> lables;

	ifstream inFile(fileName);
	ofstream outFile(tempPath);
	deleteCommentAndSaveLable(inFile, outFile, lables);
	inFile.close();
	outFile.close();
	ifstream tempFile(tempPath);
	ofstream out(outPath);
	Mips2Binary(tempFile, out, lables);
	tempFile.close();
	out.close();
	return 0;
}
