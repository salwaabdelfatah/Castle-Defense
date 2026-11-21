#include "Battle/Battle.h"
#include <iostream>
#include <string>
using namespace std;



int main()
{
	string fileName;

	cout << "Castle Battle - Phase 1" << endl;
	cout << "Enter the input file name (Default: Phase1_small.txt): ";
	getline(cin, fileName);

	if (fileName == "")
		fileName = "TestCases/Phase1_small.txt";

	Battle battle;
	if (!battle.Init(fileName.c_str()))
		return 1;

	battle.Run();
	return 0;
}
