#include <iostream>
#include <cmath>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

void tobinary(char value)
{
	unsigned char mask;
	for (mask = pow(2, 7); mask != 0; mask >>= 1)
	{
		bool a = (value & mask);
		std::cout << a;
	}
	std::cout << " ";
}

void tobinarycolor(char value, char colormask, short color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO start_attribute;
	GetConsoleScreenBufferInfo(hStdOut, &start_attribute);
	unsigned char mask;
	for (mask = pow(2, 7); mask != 0; mask >>= 1)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, start_attribute.wAttributes);
		bool a = (value & mask);
		if (colormask & mask)
		{
			SetConsoleTextAttribute(hStdOut, color);
		}
		std::cout << a;
		SetConsoleTextAttribute(hStdOut, start_attribute.wAttributes);
	}
	std::cout << " ";
}

void tobinary(char value, short first, short number)
{
	static short byte = 0;
	unsigned char mask;
	for (mask = pow(2, 7); mask != 0; mask >>= 1)
	{
		bool a = (value & mask);
		++byte;
		if (byte == first)
		{
			value ^= mask;
		}
		std::cout << a;
	}
	std::cout << " ";
}

void output(char value)
{
	tobinary(value);
}

void output(int value)
{
	for (short i = sizeof(value); i != 0; i--)
	{
		tobinary(value >> (8 * (i - 1)));
	}
}

void output(short value)
{
	for (short i = sizeof(value); i != 0; i--)
	{
		tobinary(value >> (8 * (i - 1)));
	}
}

void output(long value)
{
	for (short i = sizeof(value); i != 0; i--)
	{
		tobinary(value >> (8 * (i - 1)));
	}
}

void output(float value)
{
	int* val1;
	val1 = (int*)&value;
	output(*val1);
}

void output(float val, int colormask, short color)
{
	int *val2 = (int*)&val;
	output(*val2, colormask, color);
}

void output(int value, int colormask, short color)
{
	for (short i = sizeof(value); i != 0; i--)
	{
		tobinarycolor(value >> (8 * (i - 1)), colormask >> (8 * (i - 1)), color);
	}
}

bool range(short base, char s)
{
	if ((s >= '0' && s < '0' + base && s <= '9') || (s >= 'a' && s < 'a' + base - 10 && s <= 'z') || (s >= 'A' && s < 'A' + base - 36 && s <= 'Z')) return 1;
	else return 0;
}

int digit(char s)
{
	int result;
	if (s >= 'a' && s <= 'z') result = s - 'a' + 10;
	else if (s >= 'A' && s <= 'Z') result = s - 'A' + 'z' - 'a' + 11;
	else result = s - '0';
	return result;
}

int input(int base, string typeofdata)
{
	char s;
	string result;
	do
	{
		s = _getch();
		if (range(base, s))
		{
			std::cout << char(s);
			result.push_back(s);
		}
		else if (s == 8)
		{
			if (!result.empty())
			{
				result.pop_back();
				std::cout << "\b \b";
			}

		}
		else if (s == '-' && result.empty())
		{
			std::cout << char(s);
			result.push_back(s);
		}
		else if ((s == '.') && (typeofdata == "float"))
		{
			std::cout << char(s);
			result.push_back(s);
		}
	} while (s != 13);
	std::cout << endl;
	int ans = 0;
	float ans_f = 0;
	float temp_f = 0;
	short sign = 1;
	bool f = 0;
	for (int i = 0; i < result.size(); i++)
	{
		if (result[i] == '-') sign = -1;
		else if (result[i] == '.')
		{
			f = 1;
			break;
		}
		else
		{
			if (typeofdata == "int") ans = ans * base + digit(result[i]);
			else ans_f = ans_f * base + digit(result[i]);
		}
	}
	while (f && result.back() != '.')
	{
		temp_f = (temp_f + digit(result.back())) / base;
		result.pop_back();
	}
	if (typeofdata == "int")
	{
		return sign * ans;
	}
	else
	{
		ans_f = sign * (ans_f + temp_f);
		int* ret;
		ret = (int*)&ans_f;
		return *ret;
	}
}

float input(float b, string str)
{
	float* value;
	int data = input(int(b), str);
	value = (float*)&data;
	return *value;
}

int invert(int value, short first, short number)
{
	for (short j = 0; j < number; j++, first++)
	{
		short byte = 0;
		for (short i = sizeof(value); i != 0; i--)
		{
			char v = value >> (8 * (i - 1));
			unsigned char mask;
			for (mask = pow(2, 7); mask != 0; mask >>= 1)
			{
				byte++;
				if (byte == (sizeof(int)*8) - (first - number)-1)
				{
					value ^= (mask << 8 * (i - 1));
				}
			}
		}
	}
	return value;
}

float invert(float value, short first, short number)
{
	int* val1 = (int*)&value;
	int temp = invert(*val1, first, number);
	float* ans = (float*)&temp;
	return *ans;
}

void runningstring(int value)
{
	short speed;
	short direction;
	string str1 = "", str2 = "";
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "select direction:\n1. left -> right\n2. left <- right\n3. top -> down\n4. spiral\n";
	cin >> direction;
	std::cout << "select speed:\n1. slow\n2. medium\n3. fast\n";
	cin >> speed;
	std::cout << "to stop, press any key\n";
	Sleep(2000);

	if (speed == 1) speed = 50;
	else if (speed == 2) speed = 25;
	else speed == 10;

	for (int i = 32; i > 0; --i)
	{
		bool x = ((value >> i) & 1);
		str1 += to_string(x);
	}

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hStdOut, &consoleInfo);
	int width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;

	COORD pos;

	if (direction == 1)
	{
		while (!_kbhit())
		{
			str2 = "";
			pos.X = 0;
			pos.Y = 0;
			int i = str1.size();
			while (!_kbhit())
			{
				while (!_kbhit() && i > 0)
				{
					string temp = str2;
					str2 = "";
					str2 += str1[i];
					str2 += temp;
					std::cout << str2;
					Sleep(speed);
					system("cls");
					i--;
				}
				pos.X++;
				if (pos.X + str2.size() == width)
				{
					while (!_kbhit() && str2.size() != 0)
					{
						pos.X++;
						SetConsoleCursorPosition(hStdOut, pos);
						str2.pop_back();
						std::cout << str2;
						Sleep(speed);
						system("cls");
					}
					break;
				}
				SetConsoleCursorPosition(hStdOut, pos);
				std::cout << str1;
				Sleep(speed);
				system("cls");
			}
		}
	}
	else if (direction == 2)
	{
		while (!_kbhit())
		{
			str2 = "";
			pos.X = width - 1;
			pos.Y = 0;
			int i = 0;
			while (!_kbhit())
			{
				while (!_kbhit() && i < str1.size())
				{
					SetConsoleCursorPosition(hStdOut, pos);
					str2 += str1[i];
					std::cout << str2;
					Sleep(speed);
					system("cls");
					i++;
					pos.X--;
				}
				pos.X--;
				if (pos.X == 0)
				{
					while (!str2.empty())
					{
						string str3 = "";
						short j = 0;
						str3.push_back(str2[j]);
						string temp = "";
						for (short k = j + 1; k < str2.size(); k++)
						{
							temp += str2[k];
						}
						str2 = temp;
						system("cls");
						Sleep(speed);
						std::cout << str2;
					}
					break;
				}

				SetConsoleCursorPosition(hStdOut, pos);
				std::cout << str1;
				Sleep(speed);
				system("cls");
			}
		}
	}
	else if (direction == 3)
	{
		pos.X = 0;
		pos.Y = 0;
		while (!_kbhit())
		{
			SetConsoleCursorPosition(hStdOut, pos);
			cout << str1;
			Sleep(speed);
			system("cls");
			pos.Y++;
			if (pos.Y == height) pos.Y = 0;
		}
	}
	else if (direction == 4)
	{
		while (!_kbhit())
		{
			str2 = str1;
			pos.X = 0;
			pos.Y = 0;
			while (!_kbhit())
			{
				SetConsoleCursorPosition(hStdOut, pos);
				cout << str2;
				Sleep(speed);
				system("cls");
				pos.Y++;
				pos.X++;
				if (pos.Y == height) pos.Y = 0;
				if (pos.X + str2.size() == width)
				{
					if (!str2.empty()) str2.pop_back();
				}
				if (str2.empty()) break;
			}
		}
	}
}

void runningstring(float value)
{
	int* temp = (int*)&value;
	runningstring(*temp);
}

int main()
{
	int menu;
	do
	{
		std::cout << "1. int + IDZ\n";
		std::cout << "2. short\n";
		std::cout << "3. long\n";
		std::cout << "4. char\n";
		std::cout << "5. float + IDZ\n";
		std::cout << "0. exit\n";
		menu = _getch();
		if (menu == '1')
		{
			int data;
			std::cout << "base(2-62): ";
			cin >> data;
			std::cout << "input int number: ";
			data = input(data, "int");
			std::cout << "decimal: " << data << endl;
			std::cout << "binary: ";
			output(data);
			std::cout << endl;
			std::cout << "input first bit and number of bits to invert: ";
			short first, number;
			cin >> first >> number;
			int inverteddata = invert(data, first, number);
			std::cout << endl;
			std::cout << "do you want to colorize inverted bits? Y/N\n";
			menu = _getch();
			if (menu == 'Y' || menu == 'y' || menu == 'н' || menu == 'Н')
			{
				short color;
				std::cout << "1. blue\n2. green\n3. cyan\n4. red\n5. magenta\n6. yellow\n";
				cin >> color;
				std::cout << endl;
				int colormask = data ^ inverteddata;
				std::cout << "decimal: " << inverteddata << endl;
				std::cout << "binary: ";
				output(inverteddata, colormask, color);
				std::cout << endl << endl;
			}
			else
			{
				std::cout << "decimal: " << inverteddata << endl;
				std::cout << "binary: ";
				output(inverteddata);
				std::cout << endl << endl;
			}
			runningstring(inverteddata);
		}
		if (menu == '2')
		{
			short data;
			std::cout << "\ninput short number: ";
			cin >> data;
			std::cout << "binary: ";
			output(data);
			std::cout << endl;
			std::cout << endl;
		}
		if (menu == '3')
		{
			long data;
			std::cout << "\ninput long number: ";
			cin >> data;
			std::cout << "binary: ";
			output(data);
			std::cout << endl;
			std::cout << endl;
		}
		if (menu == '4')
		{
			char data;
			std::cout << "\ninput the symbol: ";
			cin >> data;
			std::cout << "binary: ";
			output(data);
			std::cout << endl;
			std::cout << endl;
		}
		if (menu == '5')
		{
			float data;
			std::cout << "\nbase (2-62): ";
			cin >> data;
			std::cout << "\ninput float number: ";
			data = input(data, "float");
			std::cout << "decimal: " << data << endl;
			std::cout << "binary: ";
			output(data);
			std::cout << endl;
			std::cout << "input first bit and number of bits to invert: ";
			short first, number;
			cin >> first >> number;
			float inverteddata = invert(data, first, number);

			std::cout << endl;
			std::cout << "do you want to colorize inverted bits? Y/N\n";
			menu = _getch();
			if (menu == 'Y' || menu == 'y')
			{
				short color;
				std::cout << "1. blue\n2. green\n3. cyan\n4. red\n5. magenta\n6. yellow\n";
				cin >> color;
				std::cout << endl;
				int* dataP = (int*)&data;
				int* invdataP = (int*)&inverteddata;
				int colormask = *dataP ^ *invdataP;
				std::cout << "decimal: " << inverteddata << endl;
				std::cout << "binary: ";
				output(*invdataP, colormask, color);
				std::cout << endl << endl;
			}
			else
			{
				std::cout << "decimal: " << inverteddata << endl;
				std::cout << "binary: ";
				output(inverteddata);
				std::cout << endl << endl;
			}
			runningstring(inverteddata);
		}
	} while (menu != '0');
}
