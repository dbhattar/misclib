#include <vector>

using namespace std;

/*Problem 5.1 : How would you go about computing the parity of a very large number
of 64-bit nonnegative integers?

Comment: The current implementation uses O(1) additional space to compute parity in
O(N) time complexity

This can be sped up by using a look up table to store parity information for 
precalculated set of numbers.
*/
long p51(vector<long> nums)
{
  long parity = 0;

  auto calculateParity = [](long n) -> int
  {
    int parity = 0;
    while(n > 0)
    {
      n &= n-1;
      ++parity;
    }
    return parity;
  };

  for (auto i : nums)
  {
    parity += calculateParity(i);
  }

  return parity;
}

/*
Problem 5.2 : Given two positive integers x and y, how would you compute x/y if
the only operators you can use are addition, subtraction, and shifting?
*/

void p52(int x, int y)
{
}

/*

Problem 6.1 : Write a function that takes an array A of length n and an index i into
A, and rearranges the elements such that all elements less than A[i] appear first,
followed by elements equal to A[i], followed by elements greater than A[i]. Your
algorithm should have O(1) space complexity and O(n) time complexity.

*/

void p61(vector<int> input, int idx)
{
  int pivot = input[idx];
  int n_lt = 0, n_eq = 0, n_gt = 0;

  //calculate the band sizes
  for(int i = 0; i < input.size(); ++i)
  {
    if(input[i] < pivot)
    {
      ++n_lt;
    }
    else if(input[i] > pivot)
    {
      ++n_gt;
    }
    else
    {
      ++n_eq;
    }
  }

  int j, i = n_lt, k;
  for(j = 0; j < n_lt; ++j)
  {
    if(input[j] == pivot)
    {
      while(input[i] == pivot)
        ++i;
      input[j] = input[i];
      input[i] = pivot;
    }
  }

  for(k = n_lt+n_eq; k < input.size(); ++k)
  {
    if(input[k] == pivot)
    {
      while(input[i] == pivot)
        ++i;
      input[k] = input[i];
      input[i] = pivot;
    }
  }

  j = 0;
  k = n_lt + n_eq;

  do
  {
    while(j < n_lt && input[j] < pivot)
      ++j;
    while(j < n_lt && k < input.size() && input[k] > pivot)
      ++k;
    if(j < n_lt && k < input.size())
    {
      int temp = input[j];
      input[j] = temp;
      input[k] = temp;
      ++j; ++k;
    }
  } while(j < n_lt && k < input.size());
}

void max_diff(vector<float> s)
{
  float diff = std::numeric_limits<float>::min();
  int buyDay = 0, sellDay = 0;
  for(int i = 0; i < s.size(); ++i)
  {
    for(int j = i + 1; j < s.size(); ++j)
    {
      if(diff < s[i] - s[j])
      {
        diff = s[i] - s[j];
        buyDay = i;
        sellDay = j;
      }
    }
  }
}