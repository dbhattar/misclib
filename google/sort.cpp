#include <vector>
#include "sort.hpp"
#include "util.hpp"

void MergeSorter::_merge(vector<int> & input, int startIndex, int midIndex, int endIndex, vector<int> & scratch)
{
  int i = startIndex, j = midIndex+1;
  int k = 0;
  while(i <= midIndex && j <= endIndex)
  {
    if(input[i] < input[j])
    {
      scratch[k++] = input[i];
      ++i;
    } else if(input[i] > input[j])
    {
      scratch[k++] = input[j];
      ++j;
    }
    else
    {
      scratch[k++] = input[i];
      scratch[k++] = input[j];
      ++i;
      ++j;
    }
  }

  while(i <= midIndex)
  {
    scratch[k++] = input[i++];
  }

  while(j <= endIndex)
  {
    scratch[k++] = input[j++];
  }

  for(int index = 0; index < k; ++index)
  {
    input[startIndex+index] = scratch[index];
  }
}

void MergeSorter::_sort(vector<int> & input, int startIndex, int endIndex, vector<int> & scratch)
{
  if(startIndex == endIndex)
  {
    return;
  }
  else
  {
    int midIndex = (startIndex + endIndex)/2;
    _sort(input, startIndex, midIndex, scratch);
    _sort(input, midIndex+1, endIndex, scratch);
    _merge(input, startIndex, midIndex, endIndex, scratch);
  }
}

void MergeSorter::sort(vector<int> & input)
{
  int size = input.size();
  if (size <= 1)
  {
    return;
  }
  vector<int> scratch(input.size());
  _sort(input, 0, size-1, scratch);
}

int QuickSorter::partition(vector<int> & input, int left, int right)
{
  int pivotValue = input[right];
  int idx = left;
  for(int i = left; i <= right-1; ++i)
  {
    if(input[i] <= pivotValue)
    {
      int temp = input[i];
      input[i] = input[idx];
      input[idx] = temp;
      ++idx;
    }
  }
  int temp = input[idx];
  input[idx] = pivotValue;
  input[right] = temp;
  return idx;
}

void QuickSorter::_sort(vector<int> & input, int left, int right)
{
  if (left < right)
  {
    int pivot = partition(input, left, right);
    _sort(input, left, pivot-1);
    _sort(input, pivot+1, right);
  }
}

void QuickSorter::sort(vector<int> & input)
{
  int size = input.size();
  if (size == 0)
  {
    return;
  }

  _sort(input, 0, size-1);
}

void testSorting()
{
  vector<int> input = generateRandomVector(40);
  printVector("Input for Merge Sort", input);
  MergeSorter ms;
  ms.sort(input);
  printVector("Merge Sort", input);

  input = generateRandomVector(20);
  printVector("Input for Quick Sort", input);
  QuickSorter qs;
  qs.sort(input);
  printVector("Quick Sort", input);
}