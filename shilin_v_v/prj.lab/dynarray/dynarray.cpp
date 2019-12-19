#include <dynarray/dynarray.h>
#include <iostream>

DynArray::DynArray(const DynArray& arr)
  : size_(arr.size_)
  , capacity_(arr.capacity_)
  , data_(new float[arr.capacity_] {0.0f}) {
  std::copy(arr.data_, arr.data_ + arr.size_, data_);
}

DynArray::DynArray(const std::ptrdiff_t size) {
  if (size < 0) {
    throw std::invalid_argument("size < 0");
  } else {
    size_ = size;
    capacity_ = size;
    data_ = new float[size];
    std::fill(data_, data_ + size, 0.0f);
  }
}

DynArray& DynArray::operator=(const DynArray& rhs) {
  if (this != &rhs) {
    if (capacity_ >= rhs.size_) {
      std::copy(rhs.data_, rhs.data_ + rhs.size_, data_);
      size_ = rhs.size_;
    } else {
      float* tmpdata_ = new float[rhs.size_];
      std::copy(rhs.data_, rhs.data_ + rhs.size_, tmpdata_);
      delete[] data_;
      data_ = tmpdata_;
      size_ = rhs.size_;
      capacity_ = rhs.capacity_;
    }
  }
  return *this;
}

DynArray::~DynArray() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

std::ptrdiff_t DynArray::size() const{
  return size_;
}

std::ptrdiff_t DynArray::capacity() const{
  return capacity_;
}

float& DynArray::operator[] (const std::ptrdiff_t index) {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("DynArray::operator[] index is out of range");
  }
  return data_[index];
}

const float& DynArray::operator[] (const std::ptrdiff_t index) const {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("DynArray::operator[] index is out of range");
  }
  return data_[index];
}

void DynArray::resize(const std::ptrdiff_t nsize) {
  if (nsize < 0) {
    throw std::invalid_argument("DynArray::resize - new size is < 0");
  } else {
    if (nsize <= capacity_) {
      size_ = nsize;
    } else {
      float* tmpdata(new float[nsize]);
      std::copy(data_, data_ + size_, tmpdata);
      std::fill(tmpdata + size_, tmpdata + nsize, 0.0f);
      delete[] data_;
      data_ = tmpdata;
      size_ = nsize;
      capacity_ = nsize;
    }
  }
}
