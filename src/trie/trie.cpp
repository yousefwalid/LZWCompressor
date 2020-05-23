#include "trie.hpp"

Trie::Trie()
{
    headNode = new TrieNode();
}

void Trie::insertWord(const std::string &word)
{
    auto currNode = Trie::headNode;
    for (int i = 0; i < word.size(); i++)
    {
        if (!currNode->children.count(word[i]))
        {
            auto newNode = new TrieNode(word[i]);
            if (i == word.size() - 1)
                newNode->word_idx = Trie::global_idx++;
        }
        else
        {
            if (i == word.size() - 1 && !currNode->isWord())
                currNode->word_idx = Trie::global_idx++;
            currNode = currNode->children[word[i]];
        }
    }
}

uint64_t Trie::getWordIdx(const std::string &word)
{
    auto currNode = Trie::headNode;
    for (auto &c : word)
    {
        if (!currNode->children.count(c))
            return -1;

        currNode = currNode->children[c];
    }
    return currNode->word_idx;
}

uint64_t Trie::getMaximumMatch(const std::string &buffer, uint64_t bufferIdx)
{
    auto curr = Trie::headNode;
    uint64_t wordIdx = 0;
    while (1)
    {
        char c = buffer[bufferIdx++];
        if (!curr->children.count(c))
            return wordIdx;

        if (curr->isWord())
            wordIdx = curr->word_idx;

        curr = curr->children[c];
    }
}