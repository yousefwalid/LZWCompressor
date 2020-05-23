#pragma once
#include <fstream>
#include <unordered_map>

class LZW
{
public:
    void encode(std::ifstream &original, std::ofstream &encoded);

    void decode(std::ifstream &encoded, std::ofstream &decoded);
};