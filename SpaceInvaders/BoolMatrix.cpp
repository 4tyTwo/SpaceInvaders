#include "BoolMatrix.h"



BoolMatrix::BoolMatrix()
{
}

BoolMatrix::BoolMatrix(int rows, int collumns) {
std::vector<std::vector<bool>> item(rows, std::vector<bool>(collumns,true));
matrix = item;
}

bool BoolMatrix::isemptybelow(int row, int collumn) {
  bool ans = true;
    for (int j = row; j < matrix.size(); j++) {
      ans = ans && matrix[j][collumn];
    }
return ans;
}


BoolMatrix::~BoolMatrix()
{
}
