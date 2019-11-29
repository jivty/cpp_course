#include "matrixl.h"

MatrixL::MatrixL(const MatrixL& mtrx) 
  : col_(mtrx.col_)
  , row_(mtrx.row_)
  , data_(std::make_unique<float[]>(mtrx.col_*mtrx.row_))
  , dataptr_(std::make_unique<std::unique_ptr<float>[]>(mtrx.row_))
{
  for (ptrdiff_t i = 0; i < row_*col_; ++i) {
    data_[i] = mtrx.data_[i];
  }
  for (ptrdiff_t i = 0; i < col_; ++i) {
    dataptr_[i] = 
  }
}