#include "matrixa.h"
#include <iostream>

MatrixA::MatrixA(const MatrixA& mtrx)
  : col_(mtrx.col_)
  , row_(mtrx.row_)
  , data_(std::make_unique<float[]>(mtrx.col_*mtrx.row_)) {
  for (ptrdiff_t i = 0; i < col_ * row_; ++i) {
    data_[i] = mtrx.data_[i];
  }
}

MatrixA::MatrixA(const ptrdiff_t col, const ptrdiff_t row) {
  if (col <= 0 || row <= 0) {
    throw std::invalid_argument("size < 0");
  } else {
    col_ = col;
    row_ = row;
    data_ = std::make_unique<float[]>(col * row);
    for (ptrdiff_t i = 0; i < col_ * row_; ++i) {
      data_[i] = 0;
    }
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
      std::unique_ptr<float[]> tmpdata(std::make_unique<float[]>(col_ * row_));
      for (ptrdiff_t i = 0; i < col_ * row_; ++i) {
        tmpdata[i] = rhs.data_[i];
      }
      data_ = move(tmpdata);
    }
  }
  return *this;
}

std::ptrdiff_t MatrixA::col_count() const {
  return col_;
}

std::ptrdiff_t MatrixA::row_count() const {
  return row_;
}

float& MatrixA::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) {
  if (row_i < 0 || row_i >= row_ || col_i < 0 || col_i >= col_) {
    throw std::out_of_range("index out of range");
  }
  return data_[row_i * col_ + col_i];
}

const float& MatrixA::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const {
  if (row_i < 0 || row_i >= row_ || col_i < 0 || col_i >= col_) {
    throw std::out_of_range("index out of range");
  }
  return data_[row_i * col_ + col_i];
}
