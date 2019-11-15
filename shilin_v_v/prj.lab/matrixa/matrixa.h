#ifndef MATRIXA_MATRIXA_H_112019
#define MATRIXA_MATRIXA_H_112019

#include <cstddef>

class MatrixA {
 public:
  MatrixA() = default;
  MatrixA(const MatrixA& mtrx);
  MatrixA(const ptrdiff_t col, const ptrdiff_t row);
  MatrixA& operator=(const MatrixA& rhs);
  ~MatrixA() = default;

  std::ptrdiff_t col_count() const;
  std::ptrdiff_t row_count() const;
  float& at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i);
  const float& at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const;
  void resize(const std::ptrdiff_t row_i, const std ::ptrdiff_t col_i);

 private:
  std::unique_ptr<float[]> data_ { nullptr };
  std::ptrdiff_t col_ { 0 };
  std::ptrdiff_t row_ { 0 };
};

#endif
