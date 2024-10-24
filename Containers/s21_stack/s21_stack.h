#ifndef S21_STACK_H
#define S21_STACK_H

namespace s21 {

template <typename T>
class stack {
 public:
  stack();
  stack(const stack& other);
  stack(stack&& other);
  stack(std::initializer_list<T> init);
  ~stack();

  stack& operator=(const stack& other);
  stack& operator=(stack&& other);

  void push(const T& value);
  void pop();
  T& top();
  const T& top() const;
  bool empty() const;
  size_t size() const;
  void clear();
  void swap(stack& other);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  struct Node {
    T data;
    Node* next;

    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* topNode;
  size_t count;

  void copyFrom(const stack& other);
  void moveFrom(stack&& other);
  void deleteAllNodes();
};

template <typename T>
stack<T>::stack() {
  topNode = nullptr;
  count = 0;
}

template <typename T>
stack<T>::stack(const stack& other) {
  topNode = nullptr;
  count = 0;
  copyFrom(other);
}

template <typename T>
stack<T>::stack(stack&& other) {
  topNode = other.topNode;
  count = other.count;

  other.topNode = nullptr;
  other.count = 0;
}

template <typename T>
stack<T>::stack(std::initializer_list<T> init) : topNode(nullptr), count(0) {
  for (const T& value : init) {
    push(value);
  }
}

template <typename T>
stack<T>::~stack() {
  deleteAllNodes();
}

template <typename T>
stack<T>& stack<T>::operator=(const stack& other) {
  if (this != &other) {
    deleteAllNodes();
    copyFrom(other);
  }
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack&& other) {
  if (this != &other) {
    deleteAllNodes();
    moveFrom(std::move(other));
  }
  return *this;
}

template <typename T>
void stack<T>::push(const T& value) {
  Node* newNode = new Node(value);
  newNode->next = topNode;
  topNode = newNode;
  count++;
}

template <typename T>
void stack<T>::pop() {
  if (topNode) {
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
    count--;
  } else {
    throw std::out_of_range("Stack is empty");
  }
}

template <typename T>
T& stack<T>::top() {
  if (topNode) {
    return topNode->data;
  }
  throw std::out_of_range("Stack is empty");
}

template <typename T>
const T& stack<T>::top() const {
  if (topNode) {
    return topNode->data;
  }
  throw std::out_of_range("Stack is empty");
}

template <typename T>
bool stack<T>::empty() const {
  return count == 0;
}

template <typename T>
size_t stack<T>::size() const {
  return count;
}

template <typename T>
void stack<T>::clear() {
  deleteAllNodes();
}

template <typename T>
void stack<T>::swap(stack& other) {
  std::swap(topNode, other.topNode);
  std::swap(count, other.count);
}

template <typename T>
void stack<T>::copyFrom(const stack& other) {
  Node* current = other.topNode;
  Node* previous = nullptr;
  while (current) {
    Node* newNode = new Node(current->data);
    if (previous) {
      previous->next = newNode;
    } else {
      topNode = newNode;
    }
    previous = newNode;
    current = current->next;
  }
  count = other.count;
}

template <typename T>
void stack<T>::moveFrom(stack&& other) {
  topNode = other.topNode;
  count = other.count;
  other.topNode = nullptr;
  other.count = 0;
}

template <typename T>
void stack<T>::deleteAllNodes() {
  while (topNode) {
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
  }
  count = 0;
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_back(Args&&... args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif
