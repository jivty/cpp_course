#include "matrixl.h"
#include <iostream>

MatrixL::MatrixL(const MatrixL& mtrx)
  : col_(mtrx.col_)
  , row_(mtrx.row_)
  , data_(std::make_unique<float[]>(mtrx.col_* mtrx.row_))
  , dataptr_(std::make_unique<float*[]>(mtrx.row_))
{
  for (std::ptrdiff_t i(0); i < row_ * col_; ++i) {
    data_[i] = mtrx.data_[i];
  }
  for (std::ptrdiff_t i(0); i < col_; ++i) {
    dataptr_[i] = &data_[mtrx.dataptr_[i] - mtrx.data_.get()];
  }
}

MatrixL::MatrixL(const std::ptrdiff_t col, const std::ptrdiff_t row) {
  if (col <= 0 || row <= 0) {
    throw std::invalid_argument("size <= 0");
  }
  else {
    col_ = col;
    row_ = row;
    data_ = std::make_unique<float[]>(col_ * row_);
    for (std::ptrdiff_t i(0); i < col_ * row_; i++) {
      data_[i] = 0;
    }
    dataptr_ = std::make_unique< float*[]>(row_);
    for (std::ptrdiff_t j(0); j < row_; j++) {
      dataptr_[j] = &data_[j * col_];
    }
  }
}

MatrixL& MatrixL::operator=(const MatrixL& rhs) {
  if (&rhs != this) {
    if (col_ == rhs.col_ && row_ == rhs.row_) {
      col_ = rhs.col_;
      row_ = rhs.row_;
      for (std::ptrdiff_t i(0); i < col_ * row_; ++i) {
        data_[i] = rhs.data_[i];
      }
      for (std::ptrdiff_t i = 0; i < col_; ++i) {
        dataptr_[i] = &data_[rhs.dataptr_[i] - rhs.data_.get()];
      }
    }
    else {
      std::unique_ptr<float[]> tmpdata(std::make_unique<float[]>(rhs.col_ * rhs.row_));
      std::unique_ptr<float*[]> tmpdataptr(std::make_unique<float*[]>(row_));
      col_ = rhs.col_;
      row_ = rhs.row_;
      for (std::ptrdiff_t i(0); i < col_ * row_; ++i) {
        tmpdata[i] = rhs.data_[i];
      }
      for (std::ptrdiff_t i(0); i < col_; ++i) {
        tmpdataptr[i] = &tmpdata[rhs.dataptr_[i]-rhs.data_.get()];
      }
      data_ = move(tmpdata);
      dataptr_ = move(tmpdataptr);
    }
  }
  return *this;
}

std::ptrdiff_t MatrixL::col_count() const {
  return col_;
}

std::ptrdiff_t MatrixL::row_count() const {
  return row_;
}

float& MatrixL::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) {
  if (row_i < 0 || row_i >= row_ || col_i < 0 || col_i >= col_) {
    throw std::out_of_range("index out of range");
  }
  return data_[dataptr_[row_i] - data_.get() + col_i];
}

const float& MatrixL::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const {
  if (row_i < 0 || row_i >= row_ || col_i < 0 || col_i >= col_) {
    throw std::out_of_range("index out of range");
  }
  return data_[dataptr_[row_i] - data_.get() + col_i];
}