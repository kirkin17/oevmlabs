union longdouble
{
	long double ld;
	__int128_t ldint;
};

int swap_bits(int data, int i, int j)
{
    bool biti = data & (1 << i);
    bool bitj = data & (1 << j);
    if (biti != bitj)
    {
        int bit_mask = (1 << i) | (1 << j);
        data ^= bit_mask;
        return data;
    }
    return data;
}

longdouble swap_bits(longdouble data, int i, int j)
{
	bool biti = data.ldint & ((__int128_t)1 << i);
    bool bitj = data.ldint & ((__int128_t)1 << j);
    if (biti != bitj)
    {
        __int128_t bit_mask = ((__int128_t)1 << i) | ((__int128_t)1 << j);
        data.ldint ^= bit_mask;
        return data;
    }
    return data;
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