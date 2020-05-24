#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "BitBuffer.cpp"

class LZW
{
private:
    std::string encodeValToString(const long long &val, const long long &encodeBits)
    {
        std::string encodedString = "";
        for (long long i = 0; i < encodeBits; i++)
            encodedString += (((val >> (encodeBits - i - 1)) & 1) + '0');
        return encodedString;
    }

public:
    void encode(std::ifstream &original, std::ofstream &encoded)
    {
        std::unordered_map<std::string, long long> dict;

        for (int i = 0; i <= 255; i++)
            dict[std::string(1, (char)(i))] = dict.size();

        char inputSymbol;

        long long encodedStringLength = 0;

        long long encodeBits = 1;
        while ((1 << (encodeBits - 1)) < dict.size())
            encodeBits++;
        std::string accum = "";

        BitBuffer parsingBuffer;

        encoded.put(55); // push initial character to be replaced later

        while (original.get(inputSymbol))
        {
            std::string new_accum = accum + inputSymbol;
            if (dict.count(new_accum)) // element found in dict, expand match
                accum = new_accum;
            else // element not found in dict, push it in dict and flush accum
            {
                long long encodeIdx = dict[accum];

                auto temps = encodeValToString(encodeIdx, encodeBits);
                encodedStringLength += temps.size();
                parsingBuffer.push(temps);

                while (parsingBuffer.hasByte())
                    encoded.put(parsingBuffer.pop());

                dict[new_accum] = dict.size();

                if (dict.size() > ((1 << encodeBits) - 1))
                    encodeBits++;

                accum = inputSymbol;
            }
        }

        long long encodeIdx = dict[accum];
        auto temps = encodeValToString(encodeIdx, encodeBits);
        encodedStringLength += temps.size();
        parsingBuffer.push(temps);

        while (parsingBuffer.hasByte())
            encoded.put(parsingBuffer.pop());

        if (!parsingBuffer.isEmpty())
            encoded.put(parsingBuffer.pop());

        int numOfPaddingBits = (8 - (encodedStringLength % 8) % 8);

        char numOfPadding = 0;
        for (int i = 0; i < 3; i++)
        {
            numOfPadding <<= 1;
            numOfPadding |= (numOfPaddingBits >> (2 - i));
        }

        encoded.seekp(0, std::ios::beg);
        encoded.put(numOfPadding);

        original.close();
        encoded.close();
    }

    void decode(std::ifstream &encoded, std::ofstream &decoded)
    {
        char paddingLengthC;
        encoded.get(paddingLengthC);

        int paddingLength = 0;
        for (int i = 0; i < 3; i++)
        {
            paddingLength <<= 1;
            paddingLength |= ((paddingLengthC >> (2 - i)) & 1);
        }

        std::unordered_map<long long, std::string> dict;

        for (int i = 0; i <= 255; i++)
            dict[i] = std::string(1, (char)(i));

        std::string new_accum = "";
        long long encodeBits = 1;
        while ((1 << (encodeBits - 1)) < dict.size())
            encodeBits++;

        long long idx = 0;
        bool firstTime = true;

        char c;
        std::string stream = "";
        while (!encoded.eof() || !stream.empty())
        {
            int counter = 0;

            while (stream.length() < encodeBits)
            {
                encoded.get(c);
                if (encoded.peek() == EOF)
                {
                    for (int i = 0; i < 8 - paddingLength; i++)
                        stream += ((c >> (7 - i)) & 1) + '0';
                }
                else
                {
                    for (int i = 0; i < 8; i++)
                        stream += ((c >> (7 - i)) & 1) + '0';
                }
            }

            long long accumIdx = 0;
            for (long long i = 0; i < encodeBits; i++)
            {
                accumIdx <<= 1;
                accumIdx |= (stream[i] - '0');
            }

            stream.erase(0, encodeBits);

            if (!firstTime)
            {
                std::string s = dict[dict.size() - 1];
                s[s.length() - 1] = dict[accumIdx][0];
                dict[dict.size() - 1] = s;
            }
            else
                firstTime = false;

            std::string word = dict[accumIdx];
            for (auto &c : word)
                decoded.put(c);

            dict[dict.size()] = dict[accumIdx] + "?";

            if (dict.size() > ((1 << encodeBits) - 1))
                encodeBits++;
        }

        decoded.close();
    }
};