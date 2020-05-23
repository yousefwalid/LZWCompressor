#include "trie_node.hpp"

TrieNode::TrieNode()
{
}

TrieNode::TrieNode(uint8_t symbol)
{
    this->symbol = symbol;
}

TrieNode::TrieNode(uint8_t symbol, uint64_t word_idx = -1)
{
    this->symbol = symbol;
    this->word_idx = word_idx;
}

bool TrieNode::isWord()
{
    return word_idx == (uint64_t)(-1);
}
