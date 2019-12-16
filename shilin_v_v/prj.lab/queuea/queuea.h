#ifndef QUEUEA_QUEUEA_H_122019
#define QUEUEA_QUEUEA_H_122019

#include <cstddef>

class QueueA {
public:
  QueueA() = default;
  QueueA(const QueueA& obj);
  QueueA& operator=(const QueueA& obj);
  ~QueueA();

  void push(const float value);
  void pop();
  float& top();
  const float& top() const;
  bool is_empty() const;

private:
  void resize(const std::ptrdiff_t nsize);
  float* data_{ nullptr };
  float* iTail{ nullptr }; //first free
  float* iHead{ nullptr };
  std::ptrdiff_t capacity{ 0 };
};

#endif
