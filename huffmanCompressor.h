#ifndef COMPRESSIONPROJECT_HUFFMANCOMPRESSOR_H
#define COMPRESSIONPROJECT_HUFFMANCOMPRESSOR_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Node structure for chances storing in a tree.
// There are such parameters as chance value,
// index in the chances (or -1 if there was no such value)
// and left and right children.
struct Node
{
public:
    int value;
    int index;
    Node* left;
    Node* right;
    unsigned char character;

    // Structure constructor with -1 as default value of an index.
    Node(int value, Node* left, Node* right, unsigned char character, int index = -1)
    {
        this->value = value;
        this->index = index;
        this->left = left;
        this->right = right;
        this->character=character;
    }
};

class HuffmanCompression{
public:
    void compress(map<unsigned char, int> frequencyMap);

    // I use char to string encoding table at this moment,
    // so i can make a byte from encoding number.
    map<unsigned char, string> encodingTable;

private:
    void build(vector<Node*> nodes, int alphabetSize);
    void createCodes(Node* currentNode, string res);

private:
    vector<Node*> createSortedAlphabet(map<unsigned char, int> frequencyMap, int alphabetSize);

public:
    Node* root;
};

class HuffmanDecompression{
public:
    static void deleteTree(Node* node);
};

#endif //COMPRESSIONPROJECT_HUFFMANCOMPRESSOR_H
