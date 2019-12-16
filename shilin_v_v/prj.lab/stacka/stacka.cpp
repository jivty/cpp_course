#include "stacka.h"
#include <iostream>

bool StackA::is_empty() const {
  return (size_ == 0);
}

StackA::StackA(const StackA& obj)
  : size_(obj.size_)
  , data_(new float[obj.size_]) {
  if (!obj.is_empty()) {
    std::copy(obj.data_, obj.data_ + obj.size_, data_);
    head_ = &data_[obj.head_ - obj.data_];
  }
}

StackA& StackA::operator=(const StackA& obj) {
  if (this != &obj) {
    if (size_ >= obj.size_) {
      std::copy(obj.data_, obj.data_ + obj.size_, data_);
    } else {
      float* tmpdata_ = new float[obj.size_];
      std::copy(obj.data_, obj.data_ + obj.size_, data_);
      size_ = obj.size_;
      delete[] data_;
      data_ = tmpdata_;
    }
    head_ = &data_[obj.head_ - obj.data_];
  }
}

StackA::~StackA() {
  delete[] data_;
  head_ = nullptr;
  size_ = 0;
}

void StackA::push(const float val) {
  if (head_ - data_ + 1 > size_) {
    this->resize(2 * size_ + 1);
  }

}

void StackA::pop() {
  if (!this->is_empty()) {
    //head_ = &data_[head_ - data_ - 1];
    head_--;
  } else {
    throw std::logic_error("stack is empty");
  }
}
