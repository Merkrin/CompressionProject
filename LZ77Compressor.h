#ifndef COMPRESSIONPROJECT_LZ77COMPRESSOR_H
#define COMPRESSIONPROJECT_LZ77COMPRESSOR_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Three
{
public:
    short offset;
    short length;
    char character;
};

class LZ77Compression
{
public:
    void getLZ77Encoding(string text, int searchBufferSize, int previewBufferSize);

private:
    void getMaximalCommonSubstring(const string& text, int bufferLength,
                                   Three* currentThree, int border,
                                   int searchWindowStartingIndex);

public:
    vector<Three> answer;

private:
    int SEARCH_BUFFER_SIZE;
    int PREVIEW_BUFFER_SIZE;
};

class LZ77Decompression{
public:
    static void buildString(string& answer, int offset, int length, unsigned char character);
};

#endif //COMPRESSIONPROJECT_LZ77COMPRESSOR_H
