#include "Queue.h"

#include <stdexcept>

namespace linkedqueue {

template <typename T>
Node<T>::Node(T c, Node* p, Node* n) : content(c), prev(p), next(n) {};

template <typename T>
Queue<T>::Queue() : size_(0), start_(nullptr), end_(nullptr) {}

template <typename T>
Queue<T>::~Queue() {
  if (!is_empty()) {
    Node<T> *current = start_, *next;
    do {
      next = current->next;
      delete current;
      current = next;
    } while (current != nullptr);
  }
}

template <typename T>
void Queue<T>::enqueue(T elem) {
  Node<T> *new_node = new Node<T>(elem, end_, nullptr);
  if (is_empty()) {
    start_ = new_node;
  } else {
    end_->next = new_node;
  }
  end_ = new_node;
  ++size_;
}

template <typename T>
void Queue<T>::verify_nonempty() const {
  if (is_empty())
    throw std::out_of_range("List is empty.");
}

template <typename T>
T Queue<T>::pop() {
  verify_nonempty();
  T elem = start_->content;
  start_ = start_->next;
  delete start_->prev;
  start_->prev = nullptr;
  --size_;
  return elem;
}

template <typename T>
T Queue<T>::peek() const {
  verify_nonempty();
  return start_->content;
}

template <typename T>
bool Queue<T>::is_empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename Queue<T>::size_type Queue<T>::size() const noexcept {
  return size_;
}

}
