#include "stacka.h"
#include <iostream>

bool StackA::is_empty() const {
  return (size_ == 0 || head_ == data_);
}

StackA::StackA(const StackA& obj)
  : size_(obj.size_)
  , data_(new float[obj.size_]) {
  if (!obj.is_empty()) {
    std::copy(obj.data_, obj.head_, data_);
    head_ = &data_[obj.head_ - obj.data_];
  }
}

StackA& StackA::operator=(const StackA& obj) {
  if (this != &obj) {
    if (size_ >= obj.size_) {
      std::copy(obj.data_, obj.data_ + obj.size_, data_);
    } else {
      float* tmpdata_ = new float[obj.size_];
      std::copy(obj.data_, obj.data_ + obj.size_, tmpdata_);
      size_ = obj.size_;
      delete[] data_;
      data_ = tmpdata_;
    }
    head_ = &data_[obj.head_ - obj.data_];
  }
  return *this;
}

StackA::~StackA() {
  delete[] data_;
  data_ = nullptr;
  head_ = nullptr;
  size_ = 0;
}

void StackA::resize(const std::ptrdiff_t nsize) {
  float* tmpdata_(new float[nsize]);
  std::copy(data_, head_, tmpdata_);
  head_ = &tmpdata_[head_ - data_];
  delete[] data_;
  data_ = tmpdata_;
  size_ = nsize;
}

float& StackA::top() {
  if (this->is_empty()) {
    throw std::logic_error("stack is empty");
  }
  return data_[head_ - data_ - 1];
}

const float& StackA::top() const {
  if (this->is_empty()) {
    throw std::logic_error("stack is empty");
  }
  return data_[head_ - data_ - 1];
}

void StackA::push(const float val) { 
  if (head_ - data_ + 2 > size_) {
    this->resize(2 * (size_ + 1));
  }
  *head_ = val;
  head_ = &data_[head_ - data_ + 1];
}

void StackA::pop() {
  if (!this->is_empty()) {
    head_ = &data_[head_ - data_ - 1];
  }
}
