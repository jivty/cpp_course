#ifndef STACKL_STACKL_H_122019
#define STACKL_STACKL_H_122019

#include <memory>
#include <limits>

class StackL {
public:
  StackL() = default;
  StackL(const StackL& obj);
  StackL& operator=(const StackL& obj);
  ~StackL();
  
  void push(const float val);
  void pop();
  float& top();
  const float& top() const;
  bool is_empty() const;

private:
  struct Node {
    ~Node() = default;
    Node(float val, Node* next);
    Node(const Node& obj) = default;
    Node& operator=(const Node& obj) = default;
    float value_{ std::numeric_limits<float>::epsilon() };
    Node* next_{ nullptr };
  };
  Node* head_{ nullptr };
};

#endif
