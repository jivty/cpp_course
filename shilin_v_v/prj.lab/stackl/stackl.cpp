#include "stackl.h"
#include <iostream>

StackL::Node::Node(float val, Node* next)
  : value_(val)
  , next_(next) {
}

bool StackL::is_empty() const {
  return head_ == nullptr;
}

StackL::StackL(const StackL& obj) {
  if (!obj.is_empty()) {
    Node* objHead = obj.head_;
    head_ = new Node{ objHead->value_, nullptr };
    Node* mainHead = head_;
    while (objHead->next_ != nullptr) {
      head_->next_ = new Node{ objHead->next_->value_, nullptr };
      head_ = head_->next_;
      objHead = objHead->next_;
    }
    head_ = mainHead;
  } else {
    head_ = nullptr;
  }
} 

StackL::~StackL() {
  if (!this->is_empty()) {
    while (head_->next_ != nullptr) {
      Node* prevHead_ = head_;
      head_ = head_->next_;
      delete prevHead_;
    }
  }
  delete head_;
}

StackL& StackL::operator=(const StackL& obj) {
  if (this != &obj) {
    if (!this->is_empty())
    {
      while (head_->next_ != nullptr) {
        Node* prevHead_ = head_;
        head_ = head_->next_;
        delete prevHead_;
      }
      delete head_;
      head_ = nullptr;
    }
    if (!obj.is_empty()) {
      Node* objHead = obj.head_;
      head_ = new Node{ objHead->value_, nullptr };
      Node* mainHead = head_;
      while (objHead->next_ != nullptr) {
        head_->next_ = new Node{ objHead->next_->value_, nullptr };
        head_ = head_->next_;
        objHead = objHead->next_;
      }
      head_ = mainHead;
    }
  }
  return *this;
}

void StackL::push(const float val) {
  head_ = new Node{ val, head_ };
}

void StackL::pop() {
  if (!this->is_empty()) {
    Node* delHead = head_;
    head_ = head_->next_;
    delete delHead;
  }
}

float& StackL::top() {
  if (this->is_empty()) {
    throw std::logic_error("stack is empty");
  }
  return head_->value_;
}

const float& StackL::top() const {
  if (this->is_empty()) {
    throw std::logic_error("stack is empty");
  }
  return head_->value_;
}
