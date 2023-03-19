#include "SpecTools.h"
#include<string>
#include <iostream>

using namespace std;

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

void SpecTools::red_text(std::string x)
{
	cout << x << endl;
}
