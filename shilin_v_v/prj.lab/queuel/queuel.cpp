#include <queuel/queuel.h>
#include <stdexcept>

QueueL::Node::Node(const float val, Node* obj)
  : value_(val)
  , next_(obj) {
}

bool QueueL::is_empty() const {
  return head_ == nullptr;
}

float& QueueL::top() {
  if (this->is_empty()) {
    throw std::logic_error("Queue is empty");
  } else {
    return head_->value_;
  }
}

const float& QueueL::top() const {
  if (this->is_empty()) {
    throw std::logic_error("Queue is empty");
  } else {
    return head_->value_;
  }
}

void QueueL::pop() {
  if (!this->is_empty()) {
    Node* nextHead(head_->next_);
    delete head_;
    head_ = nextHead;
    if (this->is_empty()) {
      tail_ = nullptr;
    }
  }
}

QueueL::~QueueL() {
  while (!this->is_empty()) {
    pop();
  }
}

void QueueL::push(const float val) {
  Node* newTail = new Node{ val, nullptr };
  if (this->is_empty()) {
    head_ = newTail;
    tail_ = newTail;
  } else {
    tail_->next_ = newTail;
    tail_ = newTail;
  }
}

QueueL::QueueL(const QueueL& obj) {
  Node* objHead(obj.head_);
  while (objHead != nullptr) {
    this->push(objHead->value_);
    objHead = objHead->next_;
  }
}

QueueL& QueueL::operator=(const QueueL& obj) {
  if (this != &obj) {
    while (!this->is_empty()) {
      this->pop();
    }
    Node* objHead(obj.head_);
    while (objHead != nullptr) {
      this->push(objHead->value_);
      objHead = objHead->next_;
    }
  }
  return *this;
}
