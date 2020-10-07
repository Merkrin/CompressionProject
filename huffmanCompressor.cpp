#include "huffmanCompressor.h"

void HuffmanCompression::compress(map<unsigned char, int> frequencyMap)
{
    int alphabetSize = frequencyMap.size();

    vector<Node*> nodes = createSortedAlphabet(frequencyMap, alphabetSize);

    for (pair<unsigned char, int> element : frequencyMap)
        encodingTable[element.first] = "";

    build(nodes, alphabetSize);
}

void HuffmanCompression::build(vector<Node*> nodes, int alphabetSize)
{
    Node* newNode;
    Node* left;
    Node* right;

    while (alphabetSize > 1)
    {
        left = nodes[alphabetSize - 2];
        right = nodes[alphabetSize - 1];
        newNode =
                new Node(left->value + right->value, left, right, left->character + right->character);

        nodes.pop_back();
        nodes.pop_back();

        nodes.push_back(newNode);

        --alphabetSize;

        for (int i = alphabetSize - 1; i > 0; --i)
        {
            if (nodes[i]->value > nodes[i - 1]->value)
                swap(nodes[i], nodes[i - 1]);
            else
                break;
        }
    }

    root = nodes[0];
    createCodes(root, "");
}

vector<Node*> HuffmanCompression::createSortedAlphabet(map<unsigned char, int> frequencyMap, int alphabetSize)
{
    vector<Node*> sortedAlphabet;

    for (pair<unsigned char, int> element : frequencyMap)
        sortedAlphabet.push_back(new Node(element.second, nullptr, nullptr, element.first));

    bool swapped;

    for (int i = 0; i < alphabetSize; ++i)
    {
        swapped = false;

        for (int j = 0; j < alphabetSize - i - 1; ++j)
        {
            if (sortedAlphabet[j]->value < sortedAlphabet[j + 1]->value)
            {
                swap(sortedAlphabet[j], sortedAlphabet[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
    for (int i = 0; i < alphabetSize; ++i)
    {
        sortedAlphabet[i]->index = i;
    }

    return sortedAlphabet;
}

void HuffmanCompression::createCodes(Node* currentNode, string res)
{
    if (currentNode->left == nullptr && currentNode->right == nullptr)
    {
        encodingTable[currentNode->character] = res;
        return;
    }

    createCodes(currentNode->left, res + "1");
    createCodes(currentNode->right, res + "0");
}

void HuffmanDecompression::deleteTree(Node* node)
{
    if (node->index != -1)
    {
        deleteTree(node->left);
        deleteTree(node->right);
    } else
        delete node;
}
