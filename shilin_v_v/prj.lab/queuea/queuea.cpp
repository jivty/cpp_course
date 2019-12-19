#include "queuea.h"
#include <iostream>

bool QueueA::is_empty() const {
  return iTail == iHead;
}

QueueA::QueueA(const QueueA& obj)
  : capacity(obj.capacity)
  , data_(new float[obj.capacity]) {
  std::copy(obj.data_, obj.data_ + obj.capacity, data_);
  iTail = &data_[obj.iTail - obj.data_];
  iHead = &data_[obj.iHead - obj.data_];
}

QueueA& QueueA::operator=(const QueueA& obj) {
  if (this != &obj) {
    if (capacity >= obj.capacity) {
      std::copy(obj.data_, obj.data_ + obj.capacity, data_);
    } else {
      float* tmpdata_ = new float[obj.capacity];
      std::copy(obj.data_, obj.data_ + obj.capacity, tmpdata_);
      capacity = obj.capacity;
      delete[] data_;
      data_ = tmpdata_;
    }
    iTail = &data_[obj.iTail - obj.data_];
    iHead = &data_[obj.iHead - obj.data_];
  }
  return *this;
}

QueueA::~QueueA() {
  delete[] data_;
  iTail = nullptr;
  iHead = nullptr;
  capacity = 0;
}

void QueueA::resize(const std::ptrdiff_t nsize) {
  float* tmpdata(new float[nsize]);
  if (iTail - iHead >= 0) {
    std::copy(data_, data_ + capacity, tmpdata);
    //std::fill(tmpdata + capacity, tmpdata + nsize, 0.0f);
    iHead = &tmpdata[iHead - data_];
  } else {
    std::copy(data_, data_ + (iTail - data_), tmpdata);
    //std::fill(tmpdata + (iTail - data_), tmpdata + nsize - capacity + (iHead - data_), 0.0f);
    std::copy(data_ + (iHead - data_), data_ + capacity, tmpdata + nsize - capacity + (iHead - data_));
    iHead = &tmpdata[nsize - capacity + (iHead - data_)];
  }
  iTail = &tmpdata[iTail - data_];
  delete[] data_;
  data_ = tmpdata;
  capacity = nsize;
}

float& QueueA::top() {
  if (this->is_empty()) {
    throw std::logic_error("queue is empty");
  }
  return *iHead;
}

const float& QueueA::top() const {
  if (this->is_empty()) {
    throw std::logic_error("queue is empty");
  }
  return *iHead;
}

void QueueA::pop() {
  if (!this->is_empty()) {
    iHead = &data_[(iHead - data_ + 1) % capacity];
  }
}

void QueueA::push(const float value) {
  if ((abs(iTail - iHead) + 2) > capacity) {
    this->resize(2 * (capacity + 1));
  }
  *iTail = value;
  iTail = &data_[(iTail - data_ + 1) % capacity];
}