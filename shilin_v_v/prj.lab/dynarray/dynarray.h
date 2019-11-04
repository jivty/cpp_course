#ifndef DYNARRAY_DYNARRAY_H_112019
#define DYNARRAY_DYNARRAY_H_112019

#include <iosfwd>

class DynArray {
public:
  DynArray() = default;
  DynArray(const DynArray& arr);
  DynArray(const ptrdiff_t size);
  DynArray& operator=(const DynArray& rhs);
  ~DynArray();

  ptrdiff_t size() const;
  ptrdiff_t capacity() const;
  float& operator[] (const ptrdiff_t index);
  const float& operator[] (const ptrdiff_t index) const;

  //std::istream& readFrom(std::istream& istrtm);
  //std::ostream& writeTo(std::ostream& ostrm) const;

private:
  ptrdiff_t size_ { 0 };
  ptrdiff_t capacity_ { 0 };
  float* data_ { nullptr };
};

#endif
