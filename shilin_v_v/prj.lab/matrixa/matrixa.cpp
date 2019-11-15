#include "matrixa.h"
#include <iostream>

MatrixA::MatrixA(const MatrixA& mtrx)
  : col_(mtrx.col_)
  , row_(mtrx.row_)
  , data_(new float[mtrx.col_ * mtrx.row_]) {
  for (ptrdiff_t i = 0; i < col_ * row_; ++i) {
    data_[i] = mtrx.data_[i];
  }
}

MatrixA::MatrixA(const ptrdiff_t col, const ptrdiff_t row) {
  if (col < 0 || row < 0) {
    throw std::invalid_argument("size < 0");
  } else {
    col_ = col;
    row_ = row;
    data_ = new float[col * row];
  }
}

MatrixA& MatrixA::operator=(const MatrixA& rhs) {
  if (this != &rhs) {
    if (col_ * row_ == rhs.col_ * rhs.row_) {
      col_ = rhs.col_;
      row_ = rhs.row_;
      for (ptrdiff_t i = 0; i < col_ * row_; ++i) {
        data_[i] = rhs.data_[i];
      }
    } else {
      col_ = rhs.col_;
      row_ = rhs.row_;
      float* tmpdata = new float[col_ * row_];
      for (ptrdiff_t i = 0; i < col_ * row_; ++i) {
        tmpdata[i] = rhs.data_[i];
      }
      delete[] data_;
      data_ = tmpdata;
    }
  }
}

std::ptrdiff_t MatrixA::col_count() const {
  return col_;
}

std::ptrdiff_t MatrixA::row_count() const {
  return row_;
}

float& MatrixA::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) {

}
