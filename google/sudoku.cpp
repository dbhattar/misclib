#include "sudoku.hpp"

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class SudokuImpl
{
  bool checkRow()
  {
      for(int i = 0; i < 9; ++i)
      {
          vector<bool> state(9);
          for(int j = 0; j < 9; ++j)
          {
              int curVal = m_board[i][j];
              if (curVal == 0 || state[curVal-1])
                  return false;
              state[curVal-1] = true;
          }
      }
      return true;
  }

  bool checkColumn()
  {
      for(int i = 0; i < 9; ++i)
      {
          vector<bool> state(9);
          for(int j = 0; j < 9; ++j)
          {
              int curVal = m_board[j][i];
              if (curVal == 0 || state[curVal-1])
                  return false;
              state[curVal-1] = true;
          }
      }
      return true;
  }

  bool checkSquares()
  {
      for(int i = 0; i < 3; ++i)
      {
          for(int j = 0; j < 3; ++j)
          {
              vector<bool> state(9);
              for(int k = 3*i; k < 3*(i+1); ++k)
              {
                  for(int l = 3*j; l < 3*(j+1); ++l)
                  {
                      int curVal = m_board[k][l];
                      if (curVal == 0 || state[curVal-1])
                          return false;
                      state[curVal-1] = true;
                  }
              }
          }
      }
      return true;
  }

  bool isSolved()
  {
      return checkRow() && checkColumn() && checkSquares();
  }

  void findFirstEmptyIndex(int & _1, int & _2)
  {
      for(int i = 0; i < 9; ++i)
      {
          for(int j = 0; j < 9; ++j)
          {
              if (m_board[i][j] == 0) {
                  _1 = i;
                  _2 = j;
                  return;
              }
          }
      }
      _1 = 9;
      _2 = 9;
  }

  vector<int> getPotentialCandidates(int i, int j)
  {
    vector<bool> state(9);
    for(int col = 0; col < 9; ++col)
    {
      int val = m_board[i][col];
      if(val != 0)
      {
        state[val-1] = true;
      }
    }

    for(int row = 0; row < 9; ++row)
    {
      int val = m_board[row][j];
      if(val != 0)
      {
        state[val-1] = true;
      }
    }

    int sr = i/3, sc = j/3;
    for(int row = 3*sr; row < 3*(sr+1); ++row)
    {
      for(int col = 3*sc; col < 3 * ( sc+1); ++col)
      {
        int val = m_board[row][col];
        if(val != 0)
        {
          state[val-1] = true;
        }
      }
    }

    int n = count(begin(state), end(state), false);
    vector<int> candidates(n);
    int cidx = 0;
    for(int idx = 0; idx < state.size(); ++idx)
    {
      if(!state[idx])
      {
        candidates[cidx++] = idx+1;
      }
    }
    return candidates;
  }

  unordered_map<int, vector<int>> populateCandidatesMap()
  {
      unordered_map<int, vector<int>> candidatesMap;
      for(int i = 0; i < 9; ++i)
      {
        for(int j = 0; j < 9; ++j)
        {
          if(m_board[i][j] == 0) {
            auto candidates = getPotentialCandidates(i, j);
            auto idx = i*10+j;
            candidatesMap.insert(make_pair(idx, candidates));
          }
        }
      }
      return candidatesMap;
  }

  bool isValid(int i, int j, int val)
  {
    for(int col = 0; col < 9; ++col)
    {
      if(m_board[i][col] == val)
      {
        return false;
      }
    }

    for(int row = 0; row < 9; ++row)
    {
      if(m_board[row][j] == val)
      {
        return false;;
      }
    }

    int sr = i/3, sc = j/3;
    for(int row = 3*sr; row < 3*(sr+1); ++row)
    {
      for(int col = 3*sc; col < 3 * ( sc+1); ++col)
      {
        if(m_board[row][col] == val)
        {
          return false;
        }
      }
    }
    return true;
  }

  bool _solve(const unordered_map<int, vector<int>> & candidatesMap)
  {
      if (isSolved())
      {
          return true;
      }

      bool solved = false;
      int _1, _2;

      findFirstEmptyIndex(_1, _2);
      if (_1 < 9 && _2 < 9) {
        int idx = 10*_1 + _2;
        const auto cit = candidatesMap.find(idx);

        vector<int> candidates = cit->second;
    
        for(int i = 0; i < candidates.size(); ++i)
        {
            if(isValid(_1, _2, candidates[i]))
            {
              m_board[_1][_2] = candidates[i];
              auto _candidatesMap = populateCandidatesMap();
              print();
              solved = _solve(_candidatesMap);
              if (solved)
                  break;
              else
                m_board[_1][_2] = 0;
            }
        }
      }    
      return solved;
  }

public:
  SudokuImpl(const int s[9][9]) : m_board()
  {
    m_board.resize(9);
    for(size_t i = 0; i < 9; ++i)
    {
      m_board[i].resize(9);
      for(size_t j = 0; j < 9; ++j)
      {
        m_board[i][j] = s[i][j];
      }
    }
  }

  void print()
  {
      for(int i = 0; i < 9; ++i) 
      {
        for(int j = 0; j < 9; ++j)
        {
          if (j > 0)
          {
            cout << ", ";
          }
          cout << m_board[i][j];
        }
        cout << endl;
      }
      cout << endl;
  }

  bool solve()
  {
      auto candidatesMap = populateCandidatesMap();
      int mapSize;
      do
      {
        mapSize = candidatesMap.size();
        for(auto it = candidatesMap.begin(); it != candidatesMap.end();)
        {
          auto idx = it->first;
          auto candidates = it->second;
          if(candidates.size() == 1)
          {
            int i = idx/10;
            int j = idx%10;
            m_board[i][j] = candidates[0];
            it = candidatesMap.erase(it);
          } else
          {
            ++it;
          }
        }
        candidatesMap = populateCandidatesMap();
      } while(mapSize != candidatesMap.size());
      if (candidatesMap.size() == 0)
        return true;
      return _solve(candidatesMap);
  }

  private:
    vector<vector<int>> m_board;
};


Sudoku::Sudoku(const int s[9][9]) : m_pImpl(new SudokuImpl(s))
{}

bool Sudoku::solve()
{
  return m_pImpl->solve();
}

void Sudoku::print()
{
  m_pImpl->print();
}

void testSudoku()
{
  //Easy
  //int s[9][9] = {
  //  {0, 0, 0, 2, 6, 0, 7, 0, 1},
  //  {6, 8, 0, 0, 7, 0, 0, 9, 0},
  //  {1, 9, 0, 0, 0, 4, 5, 0, 0},
  //  {8, 2, 0, 1, 0, 0, 0, 4, 0},
  //  {0, 0, 4, 6, 0, 2, 9, 0, 0},
  //  {0, 5, 0, 0, 0, 3, 0, 2, 8},
  //  {0, 0, 9, 3, 0, 0, 0, 7, 4},
  //  {0, 4, 0, 0, 5, 0, 0, 3, 6},
  //  {7, 0, 3, 0, 1, 8, 0, 0, 0}
  //};

  //intermediate
  int s[9][9] = {
    {0, 2, 0, 6, 0, 8, 0, 0, 0},
    {5, 8, 0, 0, 0, 9, 7, 0, 0},
    {0, 0, 0, 0, 4, 0, 0, 0, 0},
    {3, 7, 0, 0, 0, 0, 5, 0, 0},
    {6, 0, 0, 0, 0, 0, 0, 0, 4},
    {0, 0, 8, 0, 0, 0, 0, 1, 3},
    {0, 0, 0, 0, 2, 0, 0, 0, 0},
    {0, 0, 9, 8, 0, 0, 0, 3, 6},
    {0, 0, 0, 3, 0, 6, 0, 9, 0}
  };

  //Very HARD
  //int s[9][9] = {
  //  {0, 0, 0, 6, 0, 0, 4, 0, 0},
  //  {7, 0, 0, 0, 0, 3, 6, 0, 0},
  //  {0, 0, 0, 0, 9, 1, 0, 8, 0},
  //  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  //  {0, 5, 0, 1, 8, 0, 0, 0, 3},
  //  {0, 0, 0, 3, 0, 6, 0, 4, 5},
  //  {0, 4, 0, 2, 0, 0, 0, 6, 0},
  //  {9, 0, 3, 0, 0, 0, 0, 0, 0},
  //  {0, 2, 0, 0, 0, 0, 1, 0, 0}
  //};

  Sudoku sudoku(s);
  sudoku.print();
  sudoku.solve();
  sudoku.print();
}
