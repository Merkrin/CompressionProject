#include "LZ77Compressor.h"

void LZ77Compression::getLZ77Encoding(string text, int searchBufferSize, int previewBufferSize)
{
    SEARCH_BUFFER_SIZE = searchBufferSize;
    PREVIEW_BUFFER_SIZE = previewBufferSize;

    int bufferLength;
    Three currentThree;
    int searchWindowStartingIndex;

    int border = 0;
    int textLength = text.length();

    while (border < textLength)
    {
        searchWindowStartingIndex = max(border - SEARCH_BUFFER_SIZE, 0);
        bufferLength = min(textLength - border, PREVIEW_BUFFER_SIZE + 1);

        getMaximalCommonSubstring(text, bufferLength, &currentThree, border, searchWindowStartingIndex);

        currentThree.character = text[border + currentThree.length];

        answer.push_back(currentThree);

        border += currentThree.length + 1;
    }
}

void LZ77Compression::getMaximalCommonSubstring(const string& text, int bufferLength, Three* currentThree, int border,
                                                int searchWindowStartingIndex)
{
    currentThree->offset = 0;
    currentThree->length = 0;

    bool equalSubstringFound = false;

    for (int i = 1; i < bufferLength; ++i)
    {
        for (int j = searchWindowStartingIndex; j < border; ++j)
        {
            equalSubstringFound = false;

            for (int k = 0; k < i; ++k)
            {
                if (j + k - border >= bufferLength ||
                    text[j + k] != text[border + k])
                    break;

                if (k == i - 1 &&
                    text[j + k] == text[border + k])
                {
                    equalSubstringFound = true;
                    currentThree->offset = border - j;
                    currentThree->length = i;
                }
            }
            if (equalSubstringFound)
                break;
        }
        if (!equalSubstringFound)
            return;
    }
}

void LZ77Decompression::buildString(string& answer, int offset, int length, unsigned char character)
{
    if (offset == -1)
        return;
    int answerLength = answer.length();
    for (int i = 0; i < length; ++i)
    {
        answer += answer[answerLength - offset + i];
    }
    answer += character;
}
