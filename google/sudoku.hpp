#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <memory>

class SudokuImpl;

class Sudoku
{
public:
  explicit Sudoku(const int board[9][9]);
  bool solve();
  void print();
private:
  std::unique_ptr<SudokuImpl> m_pImpl;
};

void testSudoku();

#endif