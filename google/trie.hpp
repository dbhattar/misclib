#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>

using namespace std;

class TrieImpl;

class Trie
{
  TrieImpl *m_pImpl;

public:
  Trie();

  void insert(const string & word);

  bool hasWord(const string & word) const;
};

void insertWord(Trie * t, const std::string & word);
void testWord(const Trie * t, const std::string & word);
void testTrie();

#endif