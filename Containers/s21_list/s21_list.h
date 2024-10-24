#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = T const&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

 private:
  struct Node {
    value_type m_data;
    Node* m_back = nullptr;
    Node* m_next = nullptr;
  };

  Node* m_head;
  Node* m_tail;
  size_type list_size_ = 0;

 public:
  list() : m_head(new Node()), m_tail(new Node()) {
    m_head->m_next = m_tail;
    m_head->m_back = m_tail;
    m_tail->m_next = m_head;
    m_tail->m_back = m_head;
  }

  list(size_type n) : list() {
    if (n >= max_size() - 1) {
      throw std::invalid_argument(
          "The size of the list exceeds the memory limit or the number of "
          "elements is smaller than zero.");
    }
    for (size_type i = 0; i < n; ++i) {
      const_reference v{};
      push_front(v);
    }
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (auto const& i : items) push_back(i);
  }


  list(list const& l) : list() {
    Node* src = l.m_head->m_next;
    while (src != l.m_tail) {
      insert(end(), src->m_data);
      src = src->m_next;
    }
  }

  list& operator=(list const& l) {
    if (this != &l) {
      clear();  
      Node* src =
          l.m_head->m_next;  
      while (src != l.m_tail) {
        insert(end(), src->m_data);
        src = src->m_next; 
      }
    }
    return *this;
  }

  list(list&& l) noexcept : list() { swap(l); }

  list& operator=(list&& l) noexcept {
    if (this != &l) swap(l);
    return *this;
  }

  ~list() {
    clear();
    delete m_head;
    delete m_tail;
  }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / (sizeof(Node));
  }

  class ListIterator final {
   private:
    friend list;
    Node* m_ptr;
    ListIterator(Node* ptr) noexcept : m_ptr(ptr){};

   public:
    ListIterator() : m_ptr(nullptr){};
    ListIterator(iterator const& other) = default;
    ListIterator(iterator&& other) = default;
    ~ListIterator() = default;
    iterator& operator=(iterator const& other) = default;
    iterator& operator=(iterator&& other) = default;

    value_type& operator*() const { return const_cast<Node*>(m_ptr)->m_data; }

    iterator& operator++() {
      m_ptr = m_ptr->m_next;
      return *this;
    }

    iterator operator++(int) {
      iterator old(*this);
      ++*this;
      return old;
    }

    iterator& operator--() {
      m_ptr = m_ptr->m_back;
      return *this;
    }

    iterator operator--(int) {
      iterator old(*this);
      --*this;
      return old;
    }

    bool operator==(iterator const& other) const {
      return m_ptr == other.m_ptr;
    }

    bool operator!=(iterator const& other) const {
      return m_ptr != other.m_ptr;
    }
  };

  class ListConstIterator final {
   private:
    friend list;
    iterator c_m_ptr;

   public:
    ListConstIterator() : c_m_ptr(){};
    ListConstIterator(const_iterator const& other) = default;
    ListConstIterator(iterator const& other) { c_m_ptr = other; }
    ListConstIterator(const_iterator&& other) = default;
    ~ListConstIterator() = default;
    const_iterator& operator=(const_iterator const& other) = default;
    const_iterator& operator=(iterator const& other) {
      c_m_ptr = other;
      return *this;
    }
    const_iterator& operator=(const_iterator&& other) = default;
    value_type const& operator*() const { return *c_m_ptr; }

    const_iterator& operator++() {
      c_m_ptr++;
      return *this;
    }

    const_iterator operator++(int) { return c_m_ptr++; }

    const_iterator& operator--() {
      c_m_ptr--;
      return *this;
    }

    const_iterator operator--(int) { return c_m_ptr--; }

    bool operator==(const_iterator const& other) const {
      return (c_m_ptr == other.c_m_ptr) ? true : false;
    }

    bool operator!=(const_iterator const& other) const {
      return (c_m_ptr != other.c_m_ptr) ? true : false;
    }

    bool operator==(iterator const& other) const {
      return (c_m_ptr == other) ? true : false;
    }

    bool operator!=(iterator const& other) const {
      return (c_m_ptr != other) ? true : false;
    }
  };

  const_reference front() const { return m_head->m_next->m_data; }
  const_reference back() const { return m_tail->m_back->m_data; }
  bool empty() const { return list_size_ ? false : true; };
  size_type size() const { return list_size_; }
  iterator begin() { return iterator(m_head->m_next); }
  iterator end() { return iterator(m_tail); }
  const_iterator begin() const { return const_iterator(m_head->m_next); }
  const_iterator end() const { return const_iterator(m_tail); }
  void push_back(const_reference value) { insert(end(), value); }
  void push_front(const_reference value) { insert(begin(), value); }
  void pop_back() { erase(--end()); }
  void pop_front() { erase(begin()); }

  void swap(list& other) noexcept {
    Node* temp_head = other.m_head;
    Node* temp_tail = other.m_tail;
    size_type temp_size = other.list_size_;

    other.m_head = m_head;
    other.m_tail = m_tail;
    other.list_size_ = list_size_;

    m_head = temp_head;
    m_tail = temp_tail;
    list_size_ = temp_size;
  }

  iterator insert(iterator pos, const_reference value) {
    Node* newNode = new Node{value};
    newNode->m_next = pos.m_ptr;
    newNode->m_back = pos.m_ptr->m_back;
    pos.m_ptr->m_back->m_next = newNode;
    pos.m_ptr->m_back = newNode;
    ++list_size_;
    return iterator(newNode);
  }

  void reverse() {
    if (size() > 1) {
      Node* element = m_tail->m_back;
      while (element != m_head) {
        Node* temp = element->m_back;
        element->m_back = element->m_next;
        element->m_next = temp;
        element = element->m_next;
      }
      Node* temp = m_head->m_next;
      m_head->m_next = m_tail->m_back;
      m_tail->m_back = temp;
      m_head->m_back = m_tail;
      m_tail->m_next = m_head;
      m_head->m_next->m_back = m_head;
      m_tail->m_back->m_next = m_tail;
    }
  }

  void unique() {
    if (size() > 1) {
      Node* first = m_head->m_next;
      Node* second = first;
      while (second != m_tail) {
        second = first->m_next;
        while (first->m_data == second->m_data && second != m_tail) {
          erase(second);
          second = first->m_next;
        }
        first = first->m_next;
      }
    }
  }

  void splice(const_iterator pos, list& other) {
    if (!other.empty() && begin() != other.begin()) {
      Node* temp_second = other.m_head;
      Node* temp_first = pos.c_m_ptr.m_ptr;
      while (other.list_size_) {
        temp_second = other.m_head->m_next;
        other.m_head->m_next->m_next->m_back = other.m_head;
        other.m_head->m_next = other.m_head->m_next->m_next;
        temp_second->m_next = temp_first;
        temp_second->m_back = temp_first->m_back;
        temp_second->m_back->m_next = temp_second;
        temp_first->m_back = temp_second;
        --other.list_size_;
        ++list_size_;
      }
    }
  }

  void sort() {
    if (size() > 1) {
      Node* element_fisrt = m_head->m_next;
      Node* element_second = m_head->m_next->m_next;
      while (element_fisrt != m_tail->m_back) {
        Node* dummy = element_fisrt;
        Node* min = element_fisrt;
        while (element_second != m_tail) {
          if (dummy->m_data > element_second->m_data) {
            min = element_second;
          }
          element_second = element_second->m_next;
        }
        if (dummy != min) {
          if (dummy->m_next == min) {
            min->m_back = min->m_back->m_back;
            dummy->m_next = dummy->m_next->m_next;
            dummy->m_back = min;
            min->m_next = dummy;
          } else {
            Node* temp_next = dummy->m_next;
            dummy->m_next = min->m_next;
            min->m_next = temp_next;

            Node* temp_prev = dummy->m_back;
            dummy->m_back = min->m_back;
            min->m_back = temp_prev;

            min->m_next->m_back = min;
            dummy->m_back->m_next = dummy;
          }
          min->m_back->m_next = min;
          dummy->m_next->m_back = dummy;
          element_fisrt = min;
        } else {
          element_fisrt = element_fisrt->m_next;
        }
        element_second = element_fisrt->m_next;
      }
    }
  }

  void merge(list& other) {
    if (this != &other && !other.empty()) {
      if (empty()) {
        *this = std::move(other);
      } else {
        Node* temp_first = m_head->m_next;
        while (other.m_head->m_next != other.m_tail) {
          if ((temp_first->m_data <= other.m_head->m_next->m_data ||
               other.m_head->m_next == other.m_tail) &&
              temp_first != m_tail) {
            temp_first = temp_first->m_next;
          } else if (temp_first->m_data > other.m_head->m_next->m_data ||
                     temp_first == m_tail) {
            Node* temp_second = other.m_head->m_next;
            other.m_head->m_next->m_next->m_back = other.m_head;
            other.m_head->m_next = other.m_head->m_next->m_next;
            temp_second->m_next = temp_first;
            temp_second->m_back = temp_first->m_back;
            temp_second->m_back->m_next = temp_second;
            temp_first->m_back = temp_second;
            --other.list_size_;
            ++list_size_;
          }
        }
      }
    }
  }

  void erase(iterator pos) {
    if (pos == --begin() || pos == end() || size() == 0) {
      throw std::out_of_range(
          "Invalid pointer: cannot be erased or dereferenced.");
    }
    Node* element = pos.m_ptr;
    element->m_next->m_back = element->m_back;
    element->m_back->m_next = element->m_next;
    delete element;
    pos.m_ptr = nullptr;
    --list_size_;
  }

  void clear() {
    Node* element = m_head->m_next;
    while (element != m_tail) {
      pop_front();
      element = m_head->m_next;
    }
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    std::initializer_list<value_type> items = {std::forward<Args>(args)...};
    for (auto const& i : items) {
      insert(pos.c_m_ptr, i);
    }
    return pos.c_m_ptr;
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    insert_many(begin(), args...);
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    insert_many(end(), args...);
  }
};
} 

#endif
