#include <iostream>
#include "trie.hpp"

using namespace std;

class TrieImpl
{
  struct TrieNode
  {
    bool isEnd;
    char ch;
    TrieNode *children;
    TrieNode *sibling;

    TrieNode (const char _ch): 
      isEnd(false),
      ch(_ch),
      children(nullptr),
      sibling(nullptr)
    {
    }
  };

  TrieNode *head;
public:
  TrieImpl() : head(new TrieNode('\0'))
  {}

  void insert(const string word)
  {
    TrieNode *node = head;
    for(size_t i = 0; i < word.size(); ++i)
    {
      TrieNode *tempNode = node->children;

      const auto & _ch = word[i];
      while(tempNode)
      {
        if (tempNode->ch == _ch)
        {
          node = tempNode;
          break;
        }
        tempNode = tempNode->sibling;
      }
      if(!tempNode)
      {
        TrieNode *newNode = new TrieNode(word[i]);
        newNode->sibling = node->children;
        node->children = newNode;
        node = node->children;
      }
    }
    node->isEnd = true;
  }

  bool hasWord(const string word) const
  {
    TrieNode *node = head;
    for(size_t i = 0; i < word.size(); ++i)
    {
      const auto & _ch = word[i];
      TrieNode *tempNode = node->children;
      while(tempNode)
      {
        if(tempNode->ch == _ch)
        {
          node = tempNode;
          break;
        }
        else
        {
          tempNode = tempNode->sibling;
        }
      }
      if (!tempNode)
      {
        return false;
      }
    }
    return node->isEnd;
  }
};

Trie::Trie() : m_pImpl(new TrieImpl)
{
}

void Trie::insert(const string & word)
{
  m_pImpl->insert(word);
}

bool Trie::hasWord(const string & word) const
{
  return m_pImpl->hasWord(word);
}

void insertWord(Trie * t, const std::string & word)
{
  cout << "insertWord('" << word << "')" << endl;
  t->insert(word);
}

void testWord(const Trie * t, const std::string & word)
{
  cout << "hasWord('" << word << "'): " << t->hasWord(word) << endl;
}

void testTrie()
{
  Trie *t = new Trie();

  insertWord(t, "dipesh");
  insertWord(t, "dipesh");
  insertWord(t, "shraddha");
  insertWord(t, "sanavi");

  testWord(t, "dipesh");
  testWord(t, "sanavi");
  testWord(t, "shraddha");
  testWord(t, "divyata");
}