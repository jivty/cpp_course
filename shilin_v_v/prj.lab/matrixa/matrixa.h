#ifndef MATRIXA_MATRIXA_H_112019
#define MATRIXA_MATRIXA_H_112019

#include <cstddef>

class MatrixA {
public:
  MatrixA() = default;
  MatrixA(const ptrdiff_t col, const ptrdiff_t row);
  MatrixA(const MatrixA& mtrx);
  MatrixA& operator=(const MatrixA& rhs);
  ~MatrixA();

  std::ptrdiff_t capacity() const;
  std::ptrdiff_t col() const;
  std::ptrdiff_t row() const;
  void resize(const std::ptrdiff_t ncol, const std::ptrdiff_t nrow);

private:
  float* data_{ nullptr };
  std::ptrdiff_t col_{ 0 };
  std::ptrdiff_t row_{ 0 };
  std::ptrdiff_t capacity_{ 0 };
};

#endif
