#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "BitBuffer.cpp"

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

        for (int i = 0; i <= 255; i++)
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

        BitBuffer parsingBuffer;

        int numOfPaddingBits = (8 - (encodedString.size() + 3) % 8) % 8;
        std::string numOfPadding = "";
        for (int i = 0; i < 3; i++)
            numOfPadding += ((numOfPaddingBits >> (2 - i)) & 1) + '0';

        encodedString.insert(0, numOfPadding);

        for (auto &c : encodedString)
        {
            parsingBuffer.push(c);
            if (parsingBuffer.hasByte())
                encoded.put(parsingBuffer.pop());
        }

        char lastByte = parsingBuffer.pop();
        if (lastByte != 0)
            encoded.put(lastByte);

        original.close();
        encoded.close();
    }

    void decode(std::ifstream &encoded, std::ofstream &decoded)
    {
        std::string stream = "";
        char c;
        while (encoded.get(c))
        {
            for (int i = 0; i < 8; i++)
                stream += ((c >> (7 - i)) & 1) + '0';
        }

        std::string paddingLengthString = stream.substr(0, 3);
        stream.erase(0, 3);
        int paddingLength = 0;
        for (int i = 0; i < paddingLengthString.size(); i++)
        {
            paddingLength <<= 1;
            paddingLength |= (paddingLengthString[i] - '0');
        }

        stream.erase(stream.end() - paddingLength, stream.end());

        std::unordered_map<int, std::string> dict;

        for (int i = 0; i <= 255; i++)
            dict[i] = std::string(1, (char)(i));

        std::string decodedString = "";
        std::string new_accum = "";
        int encodeBits = 1;
        while (encodeBits < dict.size())
            encodeBits *= 2;

        int idx = 0;
        bool firstTime = true;
        while (idx < stream.length())
        {
            int accumIdx = 0;
            for (int i = 0; i < encodeBits; i++)
            {
                accumIdx <<= 1;
                accumIdx |= (stream[idx++] - '0');
            }

            if (!firstTime)
            {
                std::string s = dict[dict.size() - 1];
                s[s.length() - 1] = dict[accumIdx][0];
                dict[dict.size() - 1] = s;
            }
            else
                firstTime = false;

            decodedString.append(dict[accumIdx]);

            dict[dict.size()] = dict[accumIdx] + "?";

            if (dict.size() > ((1 << encodeBits) - 1))
                encodeBits++;
        }

        for (auto &c : decodedString)
        {
            decoded.put(c);
        }

        decoded.close();
    }
};