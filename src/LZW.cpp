#include "LZW.hpp"
#include "./trie/trie.hpp"
#include <iostream>

void LZW::encode(std::ifstream &original, std::ofstream &encoded)
{
    Trie wordsDict;
    for (uint8_t i = 0; i < -1; i++) // initialize dictionary with all symbols
        wordsDict.insertWord(std::string(1, (char)i));

    char inputChar;
    std::string inputBuffer = "";

    while (original.get(inputChar))
        inputBuffer += inputChar;

    unsigned long long inputIdx = 0;

    while (inputIdx < inputBuffer.size())
    {
        uint64_t idx = wordsDict.getMaximumMatch(inputBuffer, inputIdx);
        std::cout << idx << " ";
    }
}

void LZW::decode(std::ifstream &encoded, std::ofstream &decoded)
{
}