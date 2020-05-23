#include "LZW.hpp"
#include "./trie/trie.hpp"

void LZW::encode(std::istream &original, std::ostream &encoded)
{
    Trie wordsDict;
    for (uint8_t i = 0; i < -1; i++) // initialize dictionary with all symbols
        wordsDict.insertWord(std::string(1, (char)i));

    char inputChar;

    while (original.get(inputChar))
    {
    }
}

void LZW::decode(std::istream &encoded, std::ostream &decoded)
{
}