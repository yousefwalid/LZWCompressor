#include "LZW.cpp"

int main()
{
    LZW compressor;
    std::ifstream original("enwik8");
    std::ofstream encoded;
    compressor.encode(original, encoded);
}