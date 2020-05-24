#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

class LZW
{
private:
    bool isPowerOfTwo(int x)
    {
        return (x & (x - 1)) == 0;
    }

    void encodeValIntoString(const int &val, std::string &encodedString, const int &encodeBits)
    {
        for (int i = 0; i < encodeBits; i++)
            encodedString += (((val >> (encodeBits - i - 1)) & 1) + '0');
    }

public:
    void encode(std::ifstream &original, std::ofstream &encoded)
    {
        std::unordered_map<std::string, int> dict;

        for (int i = 'a'; i <= 'b'; i++)
            dict[std::string(1, (char)(i))] = dict.size();

        char inputSymbol;
        std::string encodedString = "";
        int encodeBits = 1;
        while (encodeBits < dict.size())
            encodeBits *= 2;
        std::string accum = "";

        while (original.get(inputSymbol))
        {
            std::string new_accum = accum + inputSymbol;
            if (dict.count(new_accum)) // element found in dict, expand match
                accum = new_accum;
            else // element not found in dict, push it in dict and flush accum
            {
                int encodeIdx = dict[accum];

                encodeValIntoString(encodeIdx, encodedString, encodeBits);

                dict[new_accum] = dict.size();

                if (dict.size() > ((1 << encodeBits) - 1))
                    encodeBits++;

                accum = inputSymbol;
            }
        }

        int encodeIdx = dict[accum];
        encodeValIntoString(encodeIdx, encodedString, encodeBits);
    }

    void decode(std::ifstream &encoded, std::ofstream &decoded)
    {
    }
};