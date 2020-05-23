#include <fstream>
#include <unordered_map>
#include <string>

class LZW
{
    void encode(std::istream &original, std::ostream &encoded);

    void decode(std::istream &encoded, std::ostream &decoded);
};