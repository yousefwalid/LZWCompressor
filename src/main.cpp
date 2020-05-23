#include <fstream>
#include "LZW.hpp"

int main()
{
    LZW compressor;
    std::ifstream original;
    std::ofstream encoded;
    original.open("enwik8");
    compressor.encode(original, encoded);
}