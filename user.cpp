#include "user.h"
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

string data_link = "users.txt";
HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);

bool user::Login(std::string t, std::string pass)
{
	string database;
	ifstream MyReadFile(data_link);
	int licz = 0;
	bool write = false;
	
	while (getline(MyReadFile, database))
	{
		licz++;

		if (database[0] == '[')
		{
			licz = 0;
			user_number++;
			write = false;
		}
	

		if (licz == 1)
		{
			if (database == t)
			{
				write = true;
				tag = database;
			}
			else
			{
				continue;
			}
		}

		if (write)
		{
			if (licz == 2)
			{
				first_name = database;
			}
			else if (licz == 3)
			{
				last_name = database;
			}
			else if (licz == 4)
			{
				password = database;
			}
			else if (licz == 5)
			{
				role = stoi(database);
			}
			else if (licz == 6)
			{
				first_time = stoi(database);
				break;
			}
		}
	}
	MyReadFile.close();

	if (tag == "") 
	{
		return false;
	}
	else
	{
		if (pass == password) 
		{
			password = "";
			return true;
		}
		else
		{
			Clear_Temp();
			return false;
		}
	}
}

void user::User_Menu(std::string lang[80], std::string active_tag)
{
	int selected_index = 0;
	while (true)
	{
		system("cls");
		char key = ' ';
		SetConsoleTextAttribute(col, 11);
		//cout << setw(50);
		cout << lang[19] << endl; //Users Menu
		SetConsoleTextAttribute(col, 8);
		cout << "[F3] " << lang[17] << " | " << "[F4] " << lang[24] << " | " << "[F5] " << lang[18] << endl;
		SetConsoleTextAttribute(col, 7);
		Load_Data();
		int i = 0;


		while (i < user_number)
		{
			if (i == selected_index) 
			{
				cout << i + 1 << ") " << temp_data[2 + (jump * i)] << " " << temp_data[3 + (jump * i)] << " <--" << endl;
			}
			else
			{
				cout << i + 1 << ") " << temp_data[2 + (jump * i)] << " " << temp_data[3 + (jump * i)] << endl;
			}

			i++;
		}

		key = _getch();

		//keys
		if (GetAsyncKeyState(VK_ESCAPE)) 
		{
			break;
		}
		else if (GetAsyncKeyState(VK_F3)) 
		{
			Add_User(lang);
		}
		else if (GetAsyncKeyState(VK_F5))
		{
			string temp = temp_data[0 + (jump * selected_index)];
			if (temp_data[1 + (jump * selected_index)] != active_tag) 
			{
				Delete_User(int(temp[1] - '0'));
			}
		}
		else if (key == 72) // UP arrow
		{
			if (selected_index > 0) 
			{
				selected_index--;
			}
		}
		else if (key == 80) // Down Arrow
		{
			if (selected_index < user_number - 1)
			{
				selected_index++;
			}
		} 
	}
}

bool isNumber(std::string x) 
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

bool user::hasBecome(std::string x)
{
	for (int i = 0; i < 500; i++) 
	{
		if (temp_data[i] == "")
			break;

		if (temp_data[i] == x)
			return true;
	}
	return false;
}

bool user::password_restriction(std::string x)
{
	if (x.empty() || x == " ") 
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

void user::Add_User(string lang[80])
{
	Load_Data();
	system("CLS");
	cout << lang[17] << endl;
	struct newUsr
	{
		string firstName;
		string lastName;
		string tag;
		string password;
		int role;
	};
	newUsr client;
	cout << lang[20] << ": ";
	cin >> client.firstName;
	cout << lang[21] << ": ";
	cin >> client.lastName;
	cout << lang[8] << ": ";
	cin >> client.tag;
	while (hasBecome(client.tag))
	{
		cout << lang[22] << endl;
		cout << lang[8] << ": ";
		cin >> client.tag;
	}
	cout << lang[23] << " (1-3)" << endl;
	string ans;
	bool letter = true;
	do
	{
		cin >> ans;
	} while (!isNumber(ans));
	client.role = stoi(ans);



	fstream file;
	file.open(data_link, fstream::app);
	file << endl;
	file << "[" << user_number + 1 << "]" << endl;
	file << client.tag << endl;
	file << client.firstName << endl;
	file << client.lastName << endl;
	file << "1234" << endl;
	file << client.role << endl;
	file << "1" << endl;
	file.close();
	Load_Data();
}

void user::Delete_User(int index)
{
	string database;
	ifstream MyReadFile(data_link);
	int i = 0;
	std::string after_remove[500];
	int licznik = 0;
	bool write = true;
	while (getline(MyReadFile, database))
	{
		if (database[0] == '[' && int(database[1] - '0') == index)
		{
			write = false;
		}
		else if (write)
		{
			
			if (database[0] == '[') {

				write = true;
				if (int(database[1] - '0') < index)
				{
					after_remove[licznik] = database;
					licznik++;
				}
				else
				{
					int temp = int(database[1] - '0') - 1;
					char buffer[50];
					string temp2 = "[" + to_string(temp) + "]";
					after_remove[licznik] = temp2;
					licznik++;
				}
			}
			else
			{
				after_remove[licznik] = database;
				licznik++;

			}
		}
		else if (!write)
		{
			if (database[0] == '[') {
				
				write = true;
				if (int(database[1] - '0') < index)
				{
					after_remove[licznik] = database;
					licznik++;
				}
				else
				{
					int temp = int(database[1] - '0') - 1;
					char buffer[50];
					string temp2 = "[" + to_string(temp) + "]";
					after_remove[licznik] = temp2;
					licznik++;
				}
			}
		}
	}
	MyReadFile.close();

	ofstream MyFile(data_link);
	for (int i = 0; i < licznik; i++)
	{
		MyFile << after_remove[i] << endl;
	}

	MyFile.close();
}

void user::Logout()
{
	Clear_Temp();
}

void user::Change_Password(std::string lang[80])
{
	system("CLS");
	while (true) 
	{
		cout << lang[26] << ": ";
		char c = ' ';
		string pass = "";
		while (c != 13)
		{
			c = _getch();
			if (c == 8)
			{
				if (!pass.empty())
				{
					pass.pop_back();
					printf("\b");
					cout << char(32);
					printf("\b");
				}
			}
			else if (c != 13)
			{
				pass += c;
				cout << "*";
			}
		}

		if (password_restriction(pass))
		{
			break;
		}
		system("CLS");
		cout << lang[27] << endl;;
	}


}

void user::Load_Data()
{
	string database;
	ifstream MyReadFile(data_link);
	int i = 0;
	licznik = 0;
	user_number = 0;

	while (getline(MyReadFile, database)) 
	{
		if (database != "") 
		{
			temp_data[licznik] = database;
			licznik++;
			if (database[0] == '[')
				user_number++;
		}
	}
	MyReadFile.close();

	ofstream MyFile(data_link);
	for (int i = 0; i < licznik; i++) 
	{
		MyFile << temp_data[i] << endl;
	}

	MyFile.close();
}

void user::Clear_Temp()
{
	first_name = "";
	last_name = "";
	tag = "";
	role = 0;
	password = "";
}

void user::Clear_file()
{

}

void user::Update_User(int id, std::string x)
{
	switch (id)
	{
	case 1: temp_data[];
	}
	
	ofstream MyFile(data_link);
	for (int i = 0; i < licznik; i++)
	{
		MyFile << temp_data[i] << endl;
	}

	MyFile.close();
}
