#include <unordered_map>

class TrieNode
{
public:
    uint8_t symbol = 0;
    uint64_t word_idx = -1;
    std::unordered_map<uint8_t, TrieNode *> children;

    TrieNode();
    TrieNode(uint8_t symbol);
    TrieNode(uint8_t symbol, uint64_t word_idx);

    bool isWord();
};