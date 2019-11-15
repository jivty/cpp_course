#ifndef DYNARRAYT_DYNARRAYT_H_112019
#define DYNARRAYT_DYNARRAYT_H_112019

#include <cstddef>

template <typename T>
class DynArrayT {
 public:
  DynArrayT() = default;
  DynArrayT(const DynArrayT& arr);
  DynArrayT(const std::ptrdiff_t size);
  DynArrayT& operator=(const DynArrayT& rhs);
  ~DynArrayT();

  std::ptrdiff_t size() const;
  std::ptrdiff_t capacity() const;
  T& operator[] (const std::ptrdiff_t index);
  const T& operator[] (const std::ptrdiff_t index) const;
  void resize(const std::ptrdiff_t nsize);

 private:
  std::ptrdiff_t size_ { 0 };
  std::ptrdiff_t capacity_ { 0 };
  T* data_ { nullptr };
};

template <typename T>
DynArrayT<T>::DynArrayT(const DynArrayT& arr)
  : size_(arr.size_)
  , capacity_(arr.capacity_)
  , data_(new T[capacity_]) {
  for (std::ptrdiff_t i = 0; i < size_; ++i) {
    data_[i] = arr.data_[i];
  }
}

template <typename T>
DynArrayT<T>::DynArrayT(const std::ptrdiff_t size) {
  if (size < 0) {
    throw std::invalid_argument("size < 0");
  }
  else {
    size_ = size;
    capacity_ = size;
    data_ = new T[size] {0};
  }
}

template <typename T>
DynArrayT<T>& DynArrayT<T>::operator=(const DynArrayT& rhs) {
  if (this != &rhs) {
    if (size_ >= rhs.size_) {
      for (std::ptrdiff_t i = 0; i < size_; ++i) {
        data_[i] = rhs.data_[i];
      }
      size_ = rhs.size_;
    }
    else {
      T* tmpdata_ = new T[rhs.size_];
      for (std::ptrdiff_t i = 0; i < rhs.size_; ++i) {
        tmpdata_[i] = rhs.data_[i];
      }
      size_ = rhs.size_;
      capacity_ = rhs.capacity_;
      delete[] data_;
      data_ = tmpdata_;
    }
  }
  return *this;
}

template <typename T>
DynArrayT<T>::~DynArrayT() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
std::ptrdiff_t DynArrayT<T>::size() const {
  return size_;
}

template <typename T>
std::ptrdiff_t DynArrayT<T>::capacity() const {
  return capacity_;
}

template <typename T>
T& DynArrayT<T>::operator[] (const std::ptrdiff_t index) {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("index is out of range");
  }
  return data_[index];
}

template <typename T>
const T& DynArrayT<T>::operator[] (const std::ptrdiff_t index) const {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("index is out of range");
  }
  return data_[index];
}

template <typename T>
void DynArrayT<T>::resize(const std::ptrdiff_t nsize) {
  if (nsize < 0) {
    throw std::invalid_argument("new size is < 0");
  }
  else {
    if (nsize <= capacity_) {
      size_ = nsize;
    }
    else {
      T* tmpdata = new T[nsize];
      for (std::ptrdiff_t i = 0; i < size_; ++i) {
        tmpdata[i] = data_[i];
      }
      for (std::ptrdiff_t i = size_; i < nsize; ++i) {
        tmpdata[i] = 0;
      }
      size_ = nsize;
      capacity_ = nsize;
      delete[] data_;
      data_ = tmpdata;
    }
  }
}

#endif
