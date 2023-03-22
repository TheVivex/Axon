#include "SpecTools.h"
#include <string>
#include <Windows.h>
#include <iostream>

using namespace std;
//HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);


bool SpecTools::isNumber(std::string x)
{
	int test;
	try
	{
		test = stoi(x);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

void SpecTools::color_text(int col)
{
	//SetConsoleTextAttribute(color, col);
}
