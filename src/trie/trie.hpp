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
    void insertWord(const std::string &word);
    uint64_t getWordIdx(const std::string &word);
    uint64_t getMaximumMatch(const std::string &buffer, uint64_t bufferIdx);
};