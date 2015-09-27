#include "taxicab.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

void taxicab(const int maxVal)
{
  unordered_map<long, pair<int, int>> pairs;
  vector<long> cubes(maxVal);
  for(int i = 1; i <= maxVal; ++i)
  {
    cubes[i-1] = i * i * i;
  }

  for(int i = 1; i < maxVal; ++i)
  {
    for(int j = i+1; j <= maxVal; ++j)
    {
      long k = cubes[i-1] + cubes[j-1];
      auto it = pairs.find(k);
      if (it != pairs.end())
      {
        const pair<int, int> & p = it->second;
        cout << "(a, b, c, d): " << p.first << ", " << p.second << ", " << i << ", " << j << endl;
      }
      else
      {
        pairs[k] = make_pair(i, j);
      }
    }
  }
}

void testTaxicab()
{
  int maxVal = 100;
  taxicab(maxVal);
}