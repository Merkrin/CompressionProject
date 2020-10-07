cmake_minimum_required(VERSION 3.15)
project(CompressionProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompressionProject main.cpp fileManager.h fileManager.cpp huffmanCompressor.h huffmanCompressor.cpp
        binaryArithmetics.h binaryArithmetics.cpp LZ77Compressor.cpp LZ77Compressor.h)