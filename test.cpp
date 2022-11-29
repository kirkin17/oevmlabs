#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <math.h>
#include <windows.h>

union longdouble
{
	long double ld;
	unsigned long long int ldint;
};

void tobinary(char data)
{
	unsigned char mask;
	for (mask = pow(2, 7); mask != 0; mask >>= 1)
	{
		bool a = (data & mask);
		std::cout << a;
	}
	std::cout << " ";
}

void output(__int128_t value)
{
	for (short i = sizeof(value) - 6; i != 0; i--)
	{
		tobinary(value >> (8 * (i - 1)));
	}
}

void SetWindow(short x1, short y1, short x2, short y2) 
{
	short width = x2 - x1;
	short height = y2 - y1;
    COORD bufferSize = {width, height};
    SMALL_RECT windowSize = {0, 0, width - 1, height - 1};

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hStdOut, TRUE, &windowSize);
	SetConsoleScreenBufferSize(hStdOut, bufferSize);
}


int main()
{
	longdouble data;
	SetWindow(20, 15, 60, 20);
	std::cout << "1";
}