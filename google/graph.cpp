#include <vector>

using namespace std;

class Graph
{
  class EdgeIterator {
    bool operator==(const EdgeIterator & rhs)
    {
      return m_curIndex == rhs.m_curIndex;
    }

    EdgeIterator & operator++()
    {
      ++m_curIndex;
      return *this;
    }
  private:
    vector<int>::size_type m_curIndex;
  };
public:
  typedef EdgeIterator eiterator;
public:
  int vertices();
  int edges();
  eiterator ebegin(const int v);
  eiterator eend(const int v);
private:
  vector<vector<int>> m_graph;

  friend EdgeIterator;
};