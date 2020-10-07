#include "binaryArithmetics.h"

/*
 * IDEA TIME!
 *
 * If I want to convert a char to int as '2' -> 2 I need to do something like
 * toInt(toString('2')). But this is too complicated.
 * What is a char? It is a number. If I look at the ASCII table I will see
 * that '0' is 48 and so on. So if I have a char _a_
 * I can get it's integer equivalent as _a_ - 48.
 * */
unsigned char getByteFromString(string byteString)
{
    unsigned char byte = 0;

    for (int i = (int) (byteString.length() - 1); i >= 0; --i)
    {
        byte += (byteString[i] - charDifference) * pow(2, byteString.length() - i - 1);
    }

    return byte;
}

string getStringFromByte(unsigned char byte)
{
    string byteString;

    while (byte > 0)
    {
        byteString += to_string(byte % 2);

        byte /= 2;
    }

    if (byteString.length() < 8)
    {
        int counter = 8 - byteString.length();
        for (int i = 0; i < counter; ++i)
            byteString += "0";
    }

    reverse(byteString.begin(), byteString.end());

    return byteString;
}