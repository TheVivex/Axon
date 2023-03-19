#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include "lang_data.h"
#include <format>
#include "current_time.h"
#include "user.h"
#define _WIN32_WINNT 0x500

using namespace std;
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };
HANDLE hcsb = CreateFileA("CONOUT$", GENERIC_WRITE | GENERIC_READ,
	FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
lang_data lang_text;
current_time calendar;
user usr;

void Windows_Settings()
{
	GetCurrentConsoleFontEx(hcsb, FALSE, &cfi);
	cfi.dwFontSize.X = 20;
	cfi.dwFontSize.Y = 20;
	SetCurrentConsoleFontEx(hcsb, FALSE, &cfi);
	CloseHandle(hcsb);
}

void set_lang(int x) 
{
	if (x == 1) 
	{
		setlocale(LC_CTYPE, "Polish");
		lang_text.load_lang(x);
	}
	else if (x == 2) 
	{
		lang_text.load_lang(x);
	}
}

void Fst_line()
{
	SetConsoleTextAttribute(color, 14);
	cout << lang_text.lang_line[0] << char(32) << "[" << usr.tag << "]" << char(32) << lang_text.lang_line[1] << char(32) << "[" << calendar.year << "] ";
	SetConsoleTextAttribute(color, 12);
	cout << "[Local]" << endl;
	SetConsoleTextAttribute(color, 7);
	SetConsoleTitleA("Alp 1.3");
}

bool Exit_Alert(int x) 
{
	system("CLS");
	if (x == 1) 
	{
		bool a = false;
		char c = ' ';

		while (true)
		{
			system("CLS");

			cout << lang_text.lang_line[14] << endl;
			if (a == true)
			{
				cout << lang_text.lang_line[12] << " <--" << endl;
				cout << lang_text.lang_line[13] << endl;
			}
			else if (a == false)
			{
				cout << lang_text.lang_line[12] << endl;
				cout << lang_text.lang_line[13] << " <--" << endl;
			}

			while (true)
			{
				c = _getch();
				if (c == 72) // UP arrow
				{
					if (a == false)
					{
						a = true;
						break;
					}
				}
				else if (c == 80) // Down Arrow
				{
					if (a == true)
					{
						a = false;
						break;
					}
				}
				else if (c == 13)
				{
					if (a == true) 
					{
						return true;
					}
					else if (a == false) 
					{
						return false;
					}
				}
			}
		}
	}
	else if (x == 2) 
	{
		bool a = false;
		char c = ' ';

		while (true)
		{
			system("CLS");

			cout << lang_text.lang_line[11] << endl;
			if (a == true)
			{
				cout << lang_text.lang_line[12] << " <--" << endl;
				cout << lang_text.lang_line[13] << endl;
			}
			else if (a == false)
			{
				cout << lang_text.lang_line[12] << endl;
				cout << lang_text.lang_line[13] << " <--" << endl;
			}

			while (true)
			{
				c = _getch();
				if (c == 72) // UP arrow
				{
					if (a == false)
					{
						a = true;
						break;
					}
				}
				else if (c == 80) // Down Arrow
				{
					if (a == true)
					{
						a = false;
						break;
					}
				}
				else if (c == 13)
				{
					if (a == true)
					{
						return true;
					}
					else if (a == false)
					{
						return false;
					}
				}
			}
		}
	}
}

void Admin_Menu() 
{
	

	while (true)
	{
		char key = ' ';
		system("CLS");
		Fst_line();
		cout << lang_text.lang_line[2] << "->" << lang_text.lang_line[16] << endl;
		cout << "1) " << lang_text.lang_line[19] << endl;

		key = _getch();

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		else if (key == '1') 
		{
			usr.User_Menu(lang_text.lang_line, usr.tag);
		}
	}
}

void Lang_Menu() 
{
	system("CLS");
	int a = 1;
	char c = ' ';
	bool isON = true;

	while (isON)
	{
		system("CLS");

		string langs[12] = {"English", "Polski"};

		cout << lang_text.lang_line[15] << endl;
		if (a == 1)
		{
			cout << langs[0] << " <--" << endl;
			cout << langs[1] << endl;
		}
		else if (a == 2)
		{
			cout << langs[0] << endl;
			cout << langs[1] << " <--" << endl;
		}

		while (true)
		{
			c = _getch();
			if (c == 72) // UP arrow
			{
				if (a == 2)
				{
					a = 1;
					break;
				}
			}
			else if (c == 80) // Down Arrow
			{
				if (a == 1)
				{
					a = 2;
					break;
				}
			}
			else if (c == 13)
			{
				if (a == 1)
				{
					set_lang(a);
					isON = false;
					break;
				}
				else if (a == 2)
				{
					set_lang(a);
					isON = false;
					break;
				}
			}
		}
	}
}

void Menu_Load()
{
	bool on = true;
	char key;
	while (on) 
	{
		system("CLS");
		key = ' ';
		Fst_line();
		for (int i = 1; i < 7; i++) 
		{
			string line = lang_text.lang_line[i + 1];
			cout << i << ") " << line << endl;
		}

		while (true)
		{
			key = _getch();

			if (GetAsyncKeyState(VK_ESCAPE))
			{
				if (Exit_Alert(1))
				{
					system("CLS");
					usr.Logout();
					on = false;
					break;
				}
				else
				{
					break;
				}
			}
			else if (key == '6') 
			{
				Lang_Menu();
				break;
			}
			else if (key == '5') 
			{
				Admin_Menu();
				break;
			}
		}
	}
}

void Login_Process() 
{
	bool on = true;
	string login, pass = "";
	bool reload = false;
	char c = ' ';
	cout << lang_text.lang_line[8] << ": ";
	while (c != 13)
	{
		c = _getch();
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			if (Exit_Alert(2))
			{
				exit(3);
			}
			else
			{
				reload = true;
				break;
			}
		}
		else if (c == 8)
		{
			if (!login.empty())
			{
				login.pop_back();
				printf("\b");
				cout << char(32);
				printf("\b");
			}
		}
		else if (c != 13)
		{
			login += c;
			cout << c;
		}
	}
	printf("\n");
	c = ' ';
	if (!reload) 
	{
		cout << lang_text.lang_line[9] << ": ";
		while (c != 13)
		{
			c = _getch();
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				if (Exit_Alert(2))
				{
					exit(3);
				}
				else
				{
					reload = true;
					break;
				}
			}
			else if (c == 8)
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
	}
	
	

	
	if (reload) 
	{
		system("CLS");
	}
	else if (usr.Login(login, pass))
	{
		system("CLS");
		pass = "";
		Menu_Load();
	}
	else 
	{
		system("CLS");
		cout << lang_text.lang_line[10] << endl;
	}
}

int main()
{
	SetConsoleTextAttribute(color, 7);
	Windows_Settings();
	system("CLS");
	set_lang(1);
	calendar.Update();

	while (true) 
	{
		Fst_line();
		Login_Process();
	}
	return 0;
}