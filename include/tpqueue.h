// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template <typename T>
class TPQueue {
 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head) {
      pop();
    }
  }

  void push(const T& value) {
    Node* newNode = new Node(value);

    if (!head || value.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      return;
    }

    Node* current = head;
    while (current->next && current->next->data.prior >= value.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
  }

  T pop() {
    if (!head) {
      throw std::underflow_error("Queue is empty");
    }
    Node* temp = head;
    T result = temp->data;
    head = head->next;
    delete temp;
    return result;
  }

  bool isEmpty() const {
    return head == nullptr;
  }

 private:
  struct Node {
    explicit Node(const T& d, Node* n = nullptr)
        : data(d), next(n) {}

    T data;
    Node* next;
  };

  Node* head;
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
