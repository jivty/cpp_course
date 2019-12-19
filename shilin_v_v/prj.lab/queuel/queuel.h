#ifndef QUEUEL_QUEUEL_H_122019
#define QUEUEL_QUEUEL_H_122019

#include <cstddef>
#include <limits>

class QueueL {
 public:
  QueueL() = default;
  QueueL(const QueueL& obj);
  QueueL& operator=(const QueueL& obj);
  ~QueueL();

  void push(const float value);
  void pop();
  float& top();
  const float& top() const;
  bool is_empty() const;

 private:
  struct Node{
    ~Node() = default;
    Node(const float val, Node* next);
    Node(const Node& obj) = default;
    Node& operator=(const Node& obj) = default;
    float value_{ std::numeric_limits<float>::epsilon() };
    Node* next_{ nullptr };
  };
  Node* head_{ nullptr };
  Node* tail_{ nullptr };
};


#endif
