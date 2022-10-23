#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

union longdouble
{
	long double ld;
	__int128_t ldint;
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


int main()
{
	longdouble data;
	data.ldint = 1;
	output(data.ldint << 75); cout << endl;
	__int128_t aa = data.ldint << 75;
	output(aa);
}