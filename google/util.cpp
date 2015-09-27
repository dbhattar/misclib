#include "util.hpp"

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> generateRandomVector(int numItems)
{
  srand(time(nullptr));

  vector<int> output(numItems);
  for(int i = 0; i < numItems; ++i)
  {
    output[i] = rand();
  }
  return output;
}

void printVector(const std::string & label, vector<int> & v)
{
  cout << label << endl;
  for(size_t i = 0; i < v.size(); ++i)
  {
    if (i > 0)
    {
      cout << ", ";
    }

    cout << v[i];
  }
  cout << endl << endl;
}

int countNumOfOnes(int num)
{
  int count = 0;
  while(num > 0)
  {
    ++count;
    num &= num-1;
  }
  return count;
}

void testParity()
{
  int num = 1234;
  cout << "Number of ones in " << num << " is " << countNumOfOnes(num) << endl;
}

string normalize(const string & path)
{
  string n_path;

  n_path.resize(path.size());

  for(size_t i = 0; i < path.size(); ++i)
  {

  }

  return n_path;
}