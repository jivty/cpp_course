#ifndef DYNARRAY_DYNARRAY_H_112019
#define DYNARRAY_DYNARRAY_H_112019

#include <cstddef>

class DynArray {
public:
  DynArray() = default;
  DynArray(const DynArray& arr);
  DynArray(const std::ptrdiff_t size);
  DynArray& operator=(const DynArray& rhs);
  ~DynArray();

  std::ptrdiff_t size() const;
  std::ptrdiff_t capacity() const;
  float& operator[] (const std::ptrdiff_t index);
  const float& operator[] (const std::ptrdiff_t index) const;
  void resize(const std::ptrdiff_t nsize);

private:
  std::ptrdiff_t size_ { 0 };
  std::ptrdiff_t capacity_ { 0 };
  float* data_ { nullptr };
};

#endif
