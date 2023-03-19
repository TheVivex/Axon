#pragma once
#include <string>

class current_time
{
public:
		std::string month = "";
		std::string year = "";
		std::string day = "";
		std::string full_date = "";
		void Update();
private:
		std::string data = __DATE__;
};

