#ifndef STACKA_STACKA_H_122019
#define STACKA_STACKA_H_122019

class StackA {
public:
  StackA() = default;
  StackA(const StackA& obj);
  StackA& operator=(const StackA& obj);
  ~StackA();

  void push(const float val);
  void pop();
  float& top();
  const float& top() const;
  bool is_empty() const;

private:
  float* head_{ nullptr };
  float* data_{ nullptr };
  std::ptrdiff_t size_{ 0 };
  void resize(const std::ptrdiff_t nsize);
};

#endif
