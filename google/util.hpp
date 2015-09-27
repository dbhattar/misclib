#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include <string>

using namespace std;

vector<int> generateRandomVector(int numItems);
void printVector(const std::string & label, vector<int> & v);
int countNumOfOnes(int num);
void testParity();
void testSudoku();
#endif