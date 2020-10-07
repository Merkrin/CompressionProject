#ifndef COMPRESSIONPROJECT_FILEMANAGER_H
#define COMPRESSIONPROJECT_FILEMANAGER_H

#include <iostream>
#include <map>
#include <sstream>
#include "huffmanCompressor.h"
#include "LZ77Compressor.h"
#include "binaryArithmetics.h"

using namespace std;

static const int BITS_IN_BYTE = 8;

map<unsigned char, int> readFileForHuffman(const string& path);

void writeHuffmanCompression(HuffmanCompression huffmanCompression,
                             const map<unsigned char, int>& frequencyMap,
                             const string& resultPath, const string& originalPath);

void readHuffmanCompression(const string& originalPath, const string& resultPath);

int countLinesInFile(const string& path);

void createLZ77Compression(const string& originalPath, const string& resultPath,
                           int searchBufferSize, int previewBufferSize);

void writeLZ77Compression(LZ77Compression lz77Compression, const string& resultPath);

void createLZ77Decompression(const string& originalPath, const string& resultPath);

#endif //COMPRESSIONPROJECT_FILEMANAGER_H
