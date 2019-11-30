#ifndef MATRIXL_MATRIXL_H_112019
#define MATRIXL_MATRIXL_H_112019

#include <cstddef>
#include <memory>

class MatrixL {
public:
  MatrixL() = default;
  MatrixL(const MatrixL& mtrx);
  MatrixL(const std::ptrdiff_t col_, const std::ptrdiff_t row);
  MatrixL& operator=(const MatrixL& rhs);
  ~MatrixL() = default;

  std::ptrdiff_t col_count() const;
  std::ptrdiff_t row_count() const;
  float& at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i);
  const float& at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const;

private:
  std::shared_ptr<float[]> data_{ nullptr };
  std::unique_ptr<std::shared_ptr<float>[]> dataptr_{ nullptr };
  std::ptrdiff_t col_{ 0 };
  std::ptrdiff_t row_{ 0 };
};

#endif
