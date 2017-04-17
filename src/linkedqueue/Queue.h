#ifndef TINYGREP_LINKEDQUEUE_QUEUE_
#define TINYGREP_LINKEDQUEUE_QUEUE_

#include <type_traits>

namespace linkedqueue {

template <typename T>
struct Node {
  T content;
  Node *prev, *next;

  Node(T c, Node* p, Node* n);
};

template <typename T> 
class Queue {
 public:
  typedef std::size_t size_type;
  Queue();
  ~Queue();

  void enqueue(T elem);
  T pop();
  T peek() const;
  bool is_empty() const noexcept;
  size_type size() const noexcept;

 private:
  size_type size_;
  Node<T> *start_, *end_;

  void verify_nonempty() const;
};

}

#include "Queue.inc"

#endif //  TINYGREP_LINKEDQUEUE_QUEUE_
