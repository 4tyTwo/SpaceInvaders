#pragma once
#include "Enemy.h"
class BoolMatrix
{
public:
  BoolMatrix();
  BoolMatrix(int rows,int collumns);
  bool isemptybelow(int row,int collumn);
  bool isemptycollumn(int collumn);
  ~BoolMatrix();
private:
  std::vector<std::vector<bool>> matrix;
};

