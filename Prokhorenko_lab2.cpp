#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

union longdouble
{
	long double ld;
	__int128_t ldint;
};

inline void clearbuffer()
{
	while(kbhit()) getch();
}

void tobinary(char data)
{
	unsigned char mask;
	for (mask = 128; mask != 0; mask >>= 1)
	{
		bool a = (data & mask);
		std::cout << a;
	}
	std::cout << " ";
}

template <class typeOfData>
void output(typeOfData data)
{
    short size = 0;
    if(sizeof(data) == 16) size = 10;
    if(sizeof(data) == 2) size = 2;
	for (short i = size; i != 0; i--)
	{
		tobinary(data >> (8 * (i - 1)));
	}
}

bool range(char s)
{
	if ((s >= '0' && s <= '9') ) return 1;
	else return 0;
}

long double input(long double data)
{
	char s;
	string result;
	do
	{
		clearbuffer();
		s = _getch();
		if (range(s))
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
		else if (s == '.')
		{
			std::cout << char(s);
			result.push_back(s);
		}
	} while (s != 13);
	std::cout << endl;

	long double ans = 0;
	long double ans_f = 0;
	short sign = 1;

	if (result[0] == '-') 
	{
		sign = -1;
		result.erase(0,1);
	}
	for(int i = 0; i < result.size(); i++)
	{
		if (result[i] == 0) result.erase(0,1);
		else break;
	}

	for(int i = 0; i < result.size(); i++)
	{
		if(result[i] == '.') break;
		ans = ans * 10 + result[i] - '0';
	}
	while (result.back() != '.')
	{
		ans_f = (ans_f + (result.back())- '0') / 10;
		result.pop_back();
	}
	ans = sign * (ans + ans_f);
	return ans;
}

short input(short data)
{
	char s;
	string result;
	do
	{
		while(kbhit()) getch();
		s = _getch();
		if (range(s))
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
	} while (s != 13);
	std::cout << endl;

	short ans = 0;
	short sign = 1;

	if (result[0] == '-') 
	{
		sign = -1;
		result.erase(0,1);
	}

	for(int i = 0; i < result.size(); i++)
	{
		if (result[i] == 0) result.erase(0,1);
		else break;
	}
	for(int i = 0; i < result.size(); i++)
	{
		ans = ans * 10 + result[i] - '0';
	}
	return ans*sign;
}

template <class typeOfData>
typeOfData swap_bits(typeOfData data, int i, int j)
{
    bool biti = data & ((typeOfData)1 << i);
    bool bitj = data & ((typeOfData)1 << j);
    if (biti != bitj)
    {
        typeOfData bit_mask = ((typeOfData)1 << i) | ((typeOfData)1 << j);
        data ^= bit_mask;
        return data;
    }
    return data;
}

template <class typeOfData>
typeOfData reversepairs(typeOfData data)
{
	char s;
	string result;
	do
	{
		while(kbhit()) getch();
		s = _getch();
		if (s >= '0' && s <= '9')
		{
			std::cout << s;
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
		else if (s == 32)
		{
			if(!result.empty())
			{
				result.push_back(s);
				std::cout << " ";
			}
		}
	} while (s != 13);

	vector <int> vresult;
	int value = 0;
	for(int i = 0; i < result.size(); i++)
	{
		if(result[i] != char(32))
		{
			value = value * 10 + (result[i] - '0');
		}
		if(result[i] == char(32) || i == result.size() - 1)
		{
			vresult.push_back(value);
			value = 0;
		}
	}

	for(int i = 0; i < result.size(); i+=2)
	{
		data = swap_bits(data, vresult[i], vresult[i+1]);
	}
	return data;
}

void setWindow(short x1, short y1, short x2, short y2) 
{
	short width = x2 - x1;
	short height = y2 - y1;
    COORD bufferSize = {width, height};
	SMALL_RECT windowRS = {0, 0, 1, 1};
    SMALL_RECT windowSize = {0, 0, width - 1, height - 1};
	
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hStdOut, TRUE, &windowRS);
	SetConsoleScreenBufferSize(hStdOut, bufferSize);
	SetConsoleWindowInfo(hStdOut, TRUE, &windowSize);
}

inline void resetWindow(CONSOLE_SCREEN_BUFFER_INFO consoleInfo)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(hStdOut, consoleInfo.dwSize);
	SetConsoleWindowInfo(hStdOut, TRUE, &consoleInfo.srWindow);
	SetConsoleTextAttribute(hStdOut, consoleInfo.wAttributes);
}

void scroll(int x = 1)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &csbiInfo);
    SMALL_RECT srctScrollRect, srctClipRect;
    CHAR_INFO chiFill;
    COORD coordDest;
    srctScrollRect.Left = 0;
    srctScrollRect.Top = 1;
    srctScrollRect.Right = csbiInfo.dwSize.X - x;
    srctScrollRect.Bottom = csbiInfo.dwSize.Y - x;
    coordDest.X = 0;
    coordDest.Y = 0;
    srctClipRect = srctScrollRect;
	srctClipRect.Top = 0;
    chiFill.Attributes = FOREGROUND_RED|FOREGROUND_INTENSITY;
    chiFill.Char.AsciiChar = ' ';
    ScrollConsoleScreenBuffer
	(
        h,               
        &srctScrollRect, 
        &srctClipRect,
        coordDest,
        &chiFill
	);
}

void printColor(char color)
{
	unsigned char bg = color >> 4;
	unsigned char text = color & 15;
	std::cout << (int)bg << ' ';
	switch(text)
	{
		case 0: std::cout << "BLACK "; break;
		case 1: std::cout << "BLUE "; break;
		case 2: std::cout << "GREEN "; break;
		case 3: std::cout << "CYAN "; break;
		case 4: std::cout << "RED "; break;
		case 5: std::cout << "MAGENTA "; break;
		case 6: std::cout << "BROWN "; break;
		case 7: std::cout << "LIGHTGRAY "; break;
		case 8: std::cout << "DARKGRAY "; break;
		case 9: std::cout << "LIGHTBLUE "; break;
		case 10: std::cout << "LIGHTGREEN "; break;
		case 11: std::cout << "LIGHTCYAN "; break;
		case 12: std::cout << "LIGHTRED "; break;
		case 13: std::cout << "LIGHTMAGENTA "; break;
		case 14: std::cout << "YELLOW "; break;
		case 15: std::cout << "WHITE "; break;
    }
}

template <class typeOfData>
void colorizedOutput(typeOfData changedData)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO startConsoleInfo;
	GetConsoleScreenBufferInfo(hStdOut, &startConsoleInfo);
	for(int i = 0; i < 128; i++)
	{
		scroll();
		SetConsoleTextAttribute(hStdOut, i);
		printColor(i);
		output(changedData);
		Sleep(900);
		COORD cursor = {0, 4};
		SetConsoleCursorPosition(hStdOut, cursor);
		if(_kbhit()) {clearbuffer(); break;}
	}
}

template <class typeOfData>
void lab2(typeOfData changedData)
{
	setlocale(LC_ALL, "Russian");
	std::cout << "lab2? Y/N";
	char choice = _getch();
	if(choice == 'Y' || choice == 'y')
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hStdOut, &consoleInfo);
		setWindow(20, 15, 60, 20);
		colorizedOutput(changedData);
		resetWindow(consoleInfo);
	}
}

int main()
{
	int menu;
	do
	{
		system("cls");
		std::cout << "1. short\n";
		std::cout << "2. long double\n";
		std::cout << "0. exit\n";
		menu = _getch();
		if(menu == '1')
		{
			short data = 0;
			std::cout << "input short int number: ";
			data = input(data);
			std::cout << "decimal: " << data << std::endl;
			std::cout << "binary: ";
			output(data);
			std::cout << std::endl;
			std::cout << "enter the number of bit pairs to be changed: ";
			short reversedBits = reversepairs(data);
			std::cout << "\n\ndecimal: " << reversedBits << std::endl;
			std::cout << "binary: ";
			output(reversedBits); std::cout << std::endl << std::endl;
			lab2(reversedBits);
		}
		if(menu == '2')
		{
			longdouble data;
			std::cout << "\ninput float number: ";
			data.ld = input(data.ld);
			std::cout << "decimal: " << data.ld << endl;
			std::cout << "binary: ";
			output(data.ldint);
			std::cout << endl;
			std::cout << "enter the number of bit pairs to be changed: ";
			longdouble reversedBits;
			reversedBits.ldint = reversepairs(data.ldint);
			std::cout << "\n\ndecimal: " << reversedBits.ld << std::endl;
			std::cout << "binary: ";
			output(reversedBits.ldint); std::cout << std::endl << std::endl;
			lab2(reversedBits.ldint);
		}
	}
	while (menu != '0');
}