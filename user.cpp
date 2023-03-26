#include "user.h"
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include "SpecTools.h"

using namespace std;

string data_link = "users.txt";
HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);
SpecTools tools;

bool user::Login(std::string t, std::string pass, std::string lang[80])
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
			temp_index++;
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
			if (first_time == 1) 
			{
				Change_Password(lang);
			}
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
		string temp = temp_data[0 + (jump * selected_index)];
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
			if (temp_data[1 + (jump * selected_index)] != active_tag) 
			{
				Delete_User(int(temp[1] - '0'));
			}
		}
		else if (GetAsyncKeyState(VK_F4) || key == 13)
		{
			Update_User_Menu(int(temp[1] - '0') - 1, lang);
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
	Load_Data();
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
			Update_User(6, temp_index - 1, pass, true);
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

void user::Update_User(int id,int index,std::string x, bool current)
{
	
	if (current) 
	{
		switch (id)
		{
		case 1: temp_data[1 + (jump * index)] = x; tag = x; break;
		case 2: temp_data[2 + (jump * index)] = x; first_name = x; break;
		case 3: temp_data[3 + (jump * index)] = x; last_name = x; break;
		case 4: {
			temp_data[4 + (jump * index)] = "1234";
			temp_data[6 + (jump * index)] = "1";
			first_time = 1;
			break;
		}
		case 5: temp_data[5 + (jump * index)] = x; role = stoi(x);  break;
		case 6: {
			temp_data[4 + (jump * index)] = x; 
			temp_data[6 + (jump * index)] = "0";
			first_time = 0;
			break;
		}
		}
	}
	else
	{
		switch (id)
		{
		case 1: temp_data[1 + (jump * index)] = x; break;
		case 2: temp_data[2 + (jump * index)] = x; break;
		case 3: temp_data[3 + (jump * index)] = x; break;
		case 4: {
			temp_data[4 + (jump * index)] = "1234";
			temp_data[6 + (jump * index)] = "1";
			break;
		}
		case 5: temp_data[5 + (jump * index)] = x; break;
		}
	}


	ofstream MyFile(data_link);
	for (int i = 0; i < licznik; i++)
	{
		MyFile << temp_data[i] << endl;
	}

	MyFile.close();
}

void user::Update_User_Menu(int index, std::string lang[80])
{
	//out of loop
	int selected_index = 1;
	string temp = "";
	int limit = (jump - 1);
	while (true) 
	{
		system("CLS");
		int lang_index = 8;
		char c = ' ';
		bool current_user = false;
		//head
		cout << lang[28] << ": " << temp_data[2 + (jump * index)] << " " << temp_data[3 + (jump * index)] << endl;
		cout << lang[29] << ": ";

		SetConsoleTextAttribute(col, 10); //green
		cout << lang[29 + selected_index] << endl;
		SetConsoleTextAttribute(col, 7);
		//head END
		for (int i = 1; i < limit; i++)
		{
			if (i == 4)
			{
				cout << lang[9];
			}
			else
			{
				cout << lang[lang_index] << ": " << temp_data[i + (jump * index)];
			}

			if (i == selected_index)
			{
				SetConsoleTextAttribute(col, 12);
				cout << " <---" << endl;
				SetConsoleTextAttribute(col, 7);
			}
			else
			{
				printf("\n");
			}

			switch (lang_index)
			{
			case 8: lang_index = 20; break;
			case 20: lang_index++; break;
			case 21: lang_index = 23; break;
			//case 23: lang_index = 8; break;
			}
		}
		//system("pause");

		c = _getch();

		if (c == 72) //up
		{
			if(!(selected_index - 1 <= 0))
				selected_index--;
		}
		else if (c == 80) // down
		{
			if (!(selected_index + 1 >= limit))
				selected_index++;
		}
		else if (c == 13) //enter
		{
			if (tag == temp_data[1 + (jump * index)]) 
			{
				current_user = true;
			}
			
			if (selected_index == 4) 
			{
				system("CLS");
				cout << lang[35] << ": " << "1234" << endl;
				system("pause");
			}
			else 
			{
				bool isON = true;
				while (isON)
				{
					system("CLS");
					char key = ' ';
					cout << lang[28] << endl;
					cout << temp_data[selected_index + (jump * index)];
					temp = temp_data[selected_index + (jump * index)];


					while (key != 13)
					{
						key = _getch();
						if (key == 8)
						{
							if (!temp.empty())
							{
								temp.pop_back();
								printf("\b");
								cout << char(32);
								printf("\b");
							}
						}
						else if (key != 13)
						{
							temp += key;
							cout << key;
						}
						else
						{
							if (selected_index == 1 && hasBecome(temp) &&
								temp != temp_data[selected_index + (jump * index)])
							{
								key = ' ';
								break;
							}
							else if (selected_index == 5 && !(tools.isNumber(temp)))
							{
								key = ' ';
								break;
							}
							else if (temp.empty()) 
							{
								key = ' ';
								break;
							}
							else
							{
								isON = false;
							}

						}
					}

				}
			}
			Update_User(selected_index, index, temp, current_user);
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
	}
	
}
