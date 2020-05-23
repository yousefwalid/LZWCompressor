#include <cstdint>
#include <string>
#include "trie_node.hpp"
class Trie
{
private:
    uint64_t global_idx = 0;
    TrieNode *headNode;

public:
    Trie();
    ~Trie();
    void insertWord(std::string);
    uint64_t getWordIdx(std::string);
};