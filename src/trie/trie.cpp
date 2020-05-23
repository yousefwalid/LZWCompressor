#include "trie.hpp"

Trie::Trie()
{
    headNode = new TrieNode();
}

void Trie::insertWord(std::string word)
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

uint64_t Trie::getWordIdx(std::string word)
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