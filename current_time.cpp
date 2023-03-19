#include "current_time.h"
#include <cctype>
#include <string>

using namespace std;

void current_time::Update()
{
	int curr = 1;
	for (int i = 0; i < data.length(); i++)
	{
		
		if (i < 3)
		{
			month = month + data[i];
		}
		else if (i > 3 && i < 6)
		{
			
			if (data[i] == char(32)) 
			{
				day = day + "0";
			}
			else
			{
				day = day + data[i];
			}
		}
		else if (i > 6)
		{
			year = year + data[i];
		}
	}
}

void Convert() 
{

}
