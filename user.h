#pragma once
#include <string>
class user
{
public:
	std::string first_name;
	std::string last_name;
	std::string tag = "";
	int role;
	int first_time;
	bool Login(std::string t, std::string pass, std::string lang[80]);
	void User_Menu(std::string lang[80], std::string active_tag);
	void Add_User(std::string lang[80]);
	void Delete_User(int index);
	void Change_User();
	void Logout();
	void Change_Password(std::string lang[80]);
private:
	std::string password;
	void Load_Data();
	void Clear_Temp();
	int user_number = 0;
	int jump = 7;
	void Clear_file();
	void Update_User(int id, int index, std::string x, bool current);
	void Update_User_Menu(int index, std::string lang[80]);
	int line_amount = 0;
	int licznik = 0;
	int temp_index = 0;
	std::string temp_data[500];
	bool hasBecome(std::string x);
	bool password_restriction(std::string x);
};

