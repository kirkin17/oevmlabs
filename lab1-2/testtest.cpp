void output(short data)
{
	for (short i = sizeof(data); i != 0; i--)
	{
		tobinary(data >> (8 * (i - 1)));
	}
}

void output(__int128_t data)
{
	for (short i = sizeof(data) - 6; i != 0; i--)
	{
		tobinary(data >> (8 * (i - 1)));
	}
}

template <class typeOfData>
void output(typeOfData data)
{
    short size;
    if(sizeof(data) == 16) size = 10;
    if(sizeof(data) == 2) size = 2;
    
	for (short i = size; i != 0; i--)
	{
		tobinary(data >> (8 * (i - 1)));
	}
}