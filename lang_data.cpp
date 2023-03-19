#include "lang_data.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void lang_data::load_lang(int language)
{
	string line;
	ifstream MyReadFile;
	int i = 0;

	if (language == 1) 
	{
		MyReadFile.open("[EN].dat");
	}
	else if (language == 2) 
	{
		MyReadFile.open("[PL].dat");
	}

	while (getline(MyReadFile, line)) 
	{
		lang_line[i] = line;
		i = i + 1;
	}
	MyReadFile.close();
}
