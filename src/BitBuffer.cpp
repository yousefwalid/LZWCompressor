#include <queue>
#include <string>

class BitBuffer
{
private:
    std::queue<char> buffer;

public:
    void push(char bit) // Pushes a bit char into the buffer
    {
        buffer.push(bit);
    }

    void push(std::string bits) // Pushes a string of bit chars into the buffer
    {
        for (int i = 0; i < bits.length(); i++)
            buffer.push(bits[i]);
    }

    int hasByte() // Returns the number of bytes in the buffer
    {
        return buffer.size() / 8;
    }

    char pop() // Pops a single byte from the buffer
    {
        char Byte = 0;
        for (int i = 0; i < 8; i++)
        {
            if (!buffer.empty())
            {
                bool bit = buffer.front() - '0';
                buffer.pop();
                Byte = Byte | (bit << (7 - i));
            }
        }
        return Byte;
    }
};