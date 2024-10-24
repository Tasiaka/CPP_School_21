#ifndef S21_QUEUE_H
#define S21_QUEUE_H

namespace s21 {

template <typename T>
class queue {
 public:
  queue();
  queue(const queue& other);
  queue(queue&& other);
  queue(std::initializer_list<T> init);
  ~queue();

  queue& operator=(const queue& other);
  queue& operator=(queue&& other);

  void push(const T& value);
  void pop();
  T& front();
  const T& front() const;
  T& back();
  const T& back() const;
  bool empty() const;
  size_t size() const;
  void swap(queue& other);
  void clear();
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head;
  Node* tail;
  size_t count;

  void copyFrom(const queue& other);
};

template <typename T>
queue<T>::queue() {
  head = nullptr;
  tail = nullptr;
  count = 0;
}

template <typename T>
queue<T>::queue(const queue& other) {
  head = nullptr;
  tail = nullptr;
  count = 0;
  copyFrom(other);
}

template <typename T>
queue<T>::queue(queue&& other) {
  head = other.head;
  tail = other.tail;
  count = other.count;

  other.head = nullptr;
  other.tail = nullptr;
  other.count = 0;
}

template <typename T>
queue<T>::queue(std::initializer_list<T> init) {
  head = nullptr;
  tail = nullptr;
  count = 0;

  for (const T& item : init) {
    push(item);
  }
}

template <typename T>
queue<T>::~queue() {
  clear();
}

template <typename T>
queue<T>& queue<T>::operator=(const queue& other) {
  if (this != &other) {
    clear();
    copyFrom(other);
    count = other.count;
  }
  return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue&& other) {
  if (this != &other) {
    clear();
    head = other.head;
    tail = other.tail;
    count = other.count;
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
  }
  return *this;
}

template <typename T>
void queue<T>::push(const T& value) {
  Node* newNode = new Node(value);
  if (tail) {
    tail->next = newNode;
    tail = newNode;
  } else {
    head = tail = newNode;
  }
  count++;
}

template <typename T>
void queue<T>::pop() {
  if (empty()) {
    throw std::logic_error("Cannot pop from an empty queue");
  }
  Node* temp = head;
  head = head->next;
  delete temp;
  count--;

  if (count == 0) {
    tail = nullptr;
  }
}

template <typename T>
T& queue<T>::front() {
  if (head) {
    return head->data;
  }
  throw std::out_of_range("Queue is empty");
}

template <typename T>
const T& queue<T>::front() const {
  if (head) {
    return head->data;
  }
  throw std::out_of_range("Queue is empty");
}

template <typename T>
T& queue<T>::back() {
  if (tail) {
    return tail->data;
  }
  throw std::out_of_range("Queue is empty");
}

template <typename T>
const T& queue<T>::back() const {
  if (tail) {
    return tail->data;
  }
  throw std::out_of_range("Queue is empty");
}

template <typename T>
bool queue<T>::empty() const {
  return count == 0;
}

template <typename T>
size_t queue<T>::size() const {
  return count;
}

template <typename T>
void queue<T>::swap(queue& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(count, other.count);
}

template <typename T>
void queue<T>::clear() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
void queue<T>::copyFrom(const queue& other) {
  Node* current = other.head;
  while (current) {
    push(current->data);
    current = current->next;
  }
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args&&... args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif
