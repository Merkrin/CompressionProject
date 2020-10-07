#include "fileManager.h"
#include <fstream>

// Read file for Huffman encoding and return frequency table.
map<unsigned char, int> readFileForHuffman(const string& path)
{
    map<unsigned char, int> frequencyMap;
    unsigned char chr;

    ifstream ifstr;
    ifstr.open(path, ios::binary);

    if (ifstr.is_open())
    {
        chr = ifstr.get();

        while (!ifstr.eof())
        {
            if (frequencyMap.find(chr) == frequencyMap.end())
                frequencyMap[chr] = 1;
            else
                frequencyMap[chr] += 1;

            chr = ifstr.get();
        }
    }

    ifstr.close();

    return frequencyMap;
}

void writeHuffmanCompression(HuffmanCompression huffmanCompression,
                             const map<unsigned char, int>& frequencyMap,
                             const string& resultPath, const string& originalPath)
{
    unsigned char chr;

    string buffer;

    ifstream ifstr;
    ifstr.open(originalPath, ios::binary);

    if (ifstr.is_open())
    {
        fstream fstr;
        fstr.open(resultPath, ios::out | ios::binary);

        fstr << frequencyMap.size() << '\n';

        // Write frequency table in the file.
        for (pair<unsigned char, int> element :  frequencyMap)
            fstr << element.first << ' ' << element.second << ' ';
        fstr << '\n';

        // Write encoding for every for every character of the original file.
        while (!ifstr.eof())
        {
            chr = ifstr.get();

            // We need 8 characters in a string to write it as byte.
            if (buffer.length() < BITS_IN_BYTE)
                buffer += huffmanCompression.encodingTable[chr];
            else
            {
                fstr << getByteFromString(buffer.substr(0, BITS_IN_BYTE));

                if (buffer.length() == BITS_IN_BYTE)
                    buffer = huffmanCompression.encodingTable[chr];
                else
                {
                    string temp = buffer;
                    buffer = "";

                    for (int i = BITS_IN_BYTE; i < temp.length(); ++i)
                        buffer += temp[i];

                    buffer += huffmanCompression.encodingTable[chr];
                }
            }
        }

        // Add '0's to fill last byte.
        int zeros = 0;

        if (buffer.length() >= BITS_IN_BYTE)
        {
            while (buffer.length() >= 8)
            {
                fstr << getByteFromString(buffer.substr(0, BITS_IN_BYTE));
                buffer = buffer.substr(BITS_IN_BYTE, buffer.length() - BITS_IN_BYTE);
            }
        }

        if (buffer.length() != 0)
        {
            while (buffer.length() < 8)
            {
                buffer += "0";
                ++zeros;
            }
            fstr << getByteFromString(buffer);
        }

        fstr << '\n' << zeros;

        fstr.close();
    }

    ifstr.close();

    HuffmanDecompression::deleteTree(huffmanCompression.root);
}

void readHuffmanCompression(const string& originalPath, const string& resultPath)
{
    map<unsigned char, int> frequencyMap;
    unsigned char bufferCharacter;
    unsigned char currentCharacter;
    int bufferInt;
    int mapSize;
    string bufferLine;

    int amountOfLines = countLinesInFile(originalPath) - 2; // minus first and last lines.

    ifstream ifstr;
    ifstr.open(originalPath, ios::in | ios::binary);

    if (ifstr.is_open())
    {
        // Read size of frequency map.
        bufferCharacter = ifstr.get();
        while (bufferCharacter != '\n')
        {
            bufferLine += bufferCharacter;

            bufferCharacter = ifstr.get();
        }

        mapSize = stoi(bufferLine);
        bufferLine = "";

        // Read frequency map.
        for (int i = 0; i < mapSize; ++i)
        {
            currentCharacter = ifstr.get();
            if (currentCharacter == '\n')
                --amountOfLines;
            ifstr.get();

            bufferCharacter = ifstr.get();
            while (bufferCharacter != ' ')
            {
                if (bufferCharacter == '\n')
                    --amountOfLines;

                bufferLine += bufferCharacter;

                bufferCharacter = ifstr.get();
            }

            bufferInt = stoi(bufferLine);

            frequencyMap[currentCharacter] = bufferInt;

            bufferLine = "";
        }

        HuffmanCompression huffmanCompression;
        huffmanCompression.compress(frequencyMap);

        --amountOfLines;
        ifstr.get();

        int temp = 0;
        while (amountOfLines > 0)
        {
            currentCharacter = ifstr.get();

            if (currentCharacter == '\n')
                --amountOfLines;
            if (amountOfLines == 0)
                break;

            bufferLine += getStringFromByte(currentCharacter);

            ++temp;
        }

        string zerosString;

        while (!ifstr.eof())
            zerosString += ifstr.get();

        bufferInt = stoi(zerosString);
        bufferLine = bufferLine.substr(0, bufferLine.length() - bufferInt);

        std::fstream fstr;
        fstr.open(resultPath, ios::out);

        Node* node = huffmanCompression.root;
        int count = 0;
        for (int i = 0; count < bufferLine.length(); ++i)
        {
            if (i > bufferLine.length())
                break;
            if (node->index != -1)
            {
                fstr << node->character;
                node = huffmanCompression.root;
                ++count;
            }
            if (bufferLine[i] == '1')
                node = node->left;
            else
                node = node->right;
        }

        delete node;
        HuffmanDecompression::deleteTree(huffmanCompression.root);

        fstr.close();
    }

    ifstr.close();
}

int countLinesInFile(const string& path)
{
    int amountOfLines = 0;

    string line;
    ifstream file(path);

    while (getline(file, line))
    {
        ++amountOfLines;
    }

    return amountOfLines;
}

void createLZ77Compression(const string& originalPath, const string& resultPath,
                           int searchBufferSize, int previewBufferSize)
{
    string text;
    unsigned char character;
    LZ77Compression lz77Compression;

    ifstream ifstr;
    ifstr.open(originalPath, ios::binary);

    if (ifstr.is_open())
    {
        character = ifstr.get();

        while (!ifstr.eof())
        {
            text += character;
            character = ifstr.get();
        }

        lz77Compression.getLZ77Encoding(text, searchBufferSize, previewBufferSize);
    }

    ifstr.close();

    writeLZ77Compression(lz77Compression, resultPath);
}

void writeLZ77Compression(LZ77Compression lz77Compression, const string& resultPath)
{
    union element
    {
        short value;

        unsigned char bytes[2];
    };

    union element temporaryElement;

    fstream fstr;
    fstr.open(resultPath, ios::out | ios::binary);

    for (Three three : lz77Compression.answer)
    {
        temporaryElement.value = three.offset;
        fstr << temporaryElement.bytes[0] << temporaryElement.bytes[1];

        temporaryElement.value = three.length;
        fstr << temporaryElement.bytes[0] << temporaryElement.bytes[1];

        fstr << three.character;
    }

    fstr.close();
}

void createLZ77Decompression(const string& originalPath, const string& resultPath)
{
    union element
    {
        short value;

        unsigned char bytes[2];
    };

    union element temporaryElement;

    short offset;
    short length;
    unsigned char character;

    string answer;

    ifstream ifstr;
    ifstr.open(originalPath, ios::binary);

    if (ifstr.is_open())
    {

        while (!ifstr.eof())
        {
            temporaryElement.bytes[0] = ifstr.get();
            temporaryElement.bytes[1] = ifstr.get();
            offset = temporaryElement.value;

            temporaryElement.bytes[0] = ifstr.get();
            temporaryElement.bytes[1] = ifstr.get();
            length = temporaryElement.value;

            character = ifstr.get();

            LZ77Decompression::buildString(answer, offset, length, character);
        }

        fstream fstr;
        fstr.open(resultPath, ios::out);
        fstr << answer;
    }

    ifstr.close();
}
