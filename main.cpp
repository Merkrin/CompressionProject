#include <iostream>
#include "fileManager.h"

// КДЗ по дисциплине Алгоритмы и структуры данных, 2019-2020 уч.год
// Барчук Ирина Андреевна, группа БПИ-181, XX.XX.2020
// СLion for Mac,
// Состав проекта: main.cpp, fileManager.(cpp/h), huffmanCompression.(cpp/h),
// LZ77Compressor.(cpp/h), binaryArithmetics.(cpp/h).
// Что сделано: сжатие и распаковка методом Хаффмана / сжатие и распаковка
// методом Шеннона - Фано, сжатие и распаковка методом LZ77,
// проведен вычислительный эксперимент, построены
// таблицы и графики, для измерения времени выполнения использовалось ХХХ,
// оформлен отчет)
// Что не сделано: сжатие и распаковка методом Шеннона - Фано (др. вариант),
// сжатие и распаковка методом LZW.

int main()
{
    string fileNames[10] = {"../DATA/1.txt", "../DATA/2.docx", "../DATA/3.pptx",
                            "../DATA/4.pdf", "../DATA/5.dll", "../DATA/6.jpg",
                            "../DATA/7.jpg", "../DATA/8.bmp", "../DATA/9.bmp",
                            "../DATA/10.sav"};

    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds{};

    string compressedFileName;
    string decompressedFileName;

    map<unsigned char, int> frequencyMap;
    HuffmanCompression huffmanCompression;

    for (int i = 0; i < 10; ++i)
    {
        // LZ775 encoding and decoding.

        compressedFileName = "../DATA/" + to_string(i + 1) + ".lz775";
        decompressedFileName = "../DATA/" + to_string(i + 1) + ".unlz775";

        start = chrono::system_clock::now();
        createLZ77Compression(fileNames[i], compressedFileName, 4 * 1024, 1024);
        end = chrono::system_clock::now();

        elapsed_seconds = end - start;

        cout << "Encoding of " << fileNames[i] << " with LZ775: " << elapsed_seconds.count() << "s.\n";

        start = chrono::system_clock::now();
        createLZ77Decompression(compressedFileName, decompressedFileName);
        end = chrono::system_clock::now();

        elapsed_seconds = end - start;

        cout << "Decoding of " << compressedFileName << " with LZ775: " << elapsed_seconds.count() << "s.\n";

        // LZ7710 encoding and decoding.

        compressedFileName = "../DATA/" + to_string(i + 1) + ".lz7710";
        decompressedFileName = "../DATA/" + to_string(i + 1) + ".unlz7710";

        start = chrono::system_clock::now();
        createLZ77Compression(fileNames[i], compressedFileName, 8 * 1024, 2 * 1024);
        end = chrono::system_clock::now();

        elapsed_seconds = end - start;

        cout << "Encoding of " << fileNames[i] << " with LZ7710: " << elapsed_seconds.count() << "s.\n";

        start = chrono::system_clock::now();
        createLZ77Decompression(compressedFileName, decompressedFileName);
        end = chrono::system_clock::now();

        elapsed_seconds = end - start;

        cout << "Decoding of " << compressedFileName << " with LZ7710: " << elapsed_seconds.count() << "s.\n";

        // LZ7720 encoding and decoding.

        compressedFileName = "../DATA/" + to_string(i + 1) + ".lz7720";
        decompressedFileName = "../DATA/" + to_string(i + 1) + ".unlz7720";

        start = chrono::system_clock::now();
        createLZ77Compression(fileNames[i], compressedFileName, 16 * 1024, 4 * 1024);
        end = chrono::system_clock::now();

        elapsed_seconds = end - start;

        cout << "Encoding of " << fileNames[i] << " with LZ7720: " << elapsed_seconds.count() << "s.\n";

        start = chrono::system_clock::now();
        createLZ77Decompression(compressedFileName, decompressedFileName);
        end = chrono::system_clock::now();

        elapsed_seconds = end - start;

        cout << "Decoding of " << compressedFileName << " with LZ7720: " << elapsed_seconds.count() << "s.\n";

        // Huffman encoding and decoding.

        compressedFileName = "../DATA/" + to_string(i + 1) + ".huff";
        decompressedFileName = "../DATA/" + to_string(i + 1) + ".unhuff";

        start = chrono::system_clock::now();
        frequencyMap = readFileForHuffman(fileNames[i]);
        huffmanCompression.compress(frequencyMap);
        writeHuffmanCompression(huffmanCompression, frequencyMap, compressedFileName, fileNames[i]);
        end = chrono::system_clock::now();

        elapsed_seconds = end - start;

        cout << "Encoding of " << fileNames[i] << " with Huffman: " << elapsed_seconds.count() << "s.\n";

        start = chrono::system_clock::now();
        readHuffmanCompression(compressedFileName, decompressedFileName);
        end = chrono::system_clock::now();

        elapsed_seconds = end - start;

        cout << "Decoding of " << compressedFileName << " with LZ7720: " << elapsed_seconds.count() << "s.\n";
    }

    return 0;
}
