#include <fstream>
#include "LZW.hpp"

int main()
{
    LZW compressor;
    auto original = std::ifstream("enwik8");
    std::ofstream encoded("enwik8.bin", std::ios_base::binary | std::ios_base::out);
    compressor.encode(original, encoded);
}