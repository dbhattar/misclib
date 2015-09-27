#ifndef SORT_HPP
#define SORT_HPP

#include <vector>

using namespace std;

class Sorter
{
protected:
  virtual ~Sorter() {}
private:
  Sorter(const Sorter &);
  Sorter & operator=(const Sorter &);

public:
  Sorter() {}
  virtual void sort(vector<int> & input) = 0;
};

class MergeSorter : public Sorter
{
  void _merge(vector<int> & input, int startIndex, int midIndex, int endIndex, vector<int> & scratch);
  void _sort(vector<int> & input, int startIndex, int endIndex, vector<int> & scratch);

public:
  MergeSorter() {}
  void sort(vector<int> & input) override;
};


class QuickSorter : public Sorter
{
private:
  int partition(vector<int> & input, int left, int right);
  void _sort(vector<int> & input, int left, int right);

public:
  QuickSorter() {}
  void sort(vector<int> & input) override;
};

void testSorting();

#endif