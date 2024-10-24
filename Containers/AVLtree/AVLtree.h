#ifndef S21_AVL_TREE
#define S21_AVL_TREE
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <utility>

namespace s21 {

template <typename T>
struct Node_tree {
  T value_;
  Node_tree* leftNode_ = nullptr;
  Node_tree* rightNode_ = nullptr;
  Node_tree* parent_ = nullptr;
  int height_ = 0;

  Node_tree(T value = T(), Node_tree* leftNode = nullptr,
            Node_tree* rightNode = nullptr, Node_tree* parent = nullptr,
            int height = 0)
      : value_(value),
        leftNode_(leftNode),
        rightNode_(rightNode),
        parent_(parent),
        height_(height) {}
};

template <typename T>
class Iterator {
 public:
  using value_type = T;
  using reference = value_type&;
  using Node = Node_tree<value_type>;

  Iterator() : curent_node_(nullptr), end_node_(nullptr) {}
  Iterator(Node* cur, Node* end) : curent_node_(cur), end_node_(end) {}
  Iterator(const Iterator& other);
  Iterator(Iterator&& other);

  Iterator& operator=(const Iterator& other);

  bool operator==(Iterator& other) const;
  bool operator!=(Iterator& other) const;
  bool operator==(const Iterator& other) const;
  bool operator!=(const Iterator& other) const;
  value_type* operator->();
  Iterator& operator++();
  Iterator& operator--();
  Iterator operator++(int);
  Iterator operator--(int);
  reference operator*();

  Node* getCurNode();

 protected:
  Node* curent_node_;
  Node* end_node_;
};

template <typename T>
class ConstIterator : public Iterator<T> {
 public:
  using value_type = T;
  using const_reference = const value_type&;
  using Node = Node_tree<value_type>;

  ConstIterator() : Iterator<T>() {}
  ConstIterator(Node* cur, Node* end) : Iterator<T>(cur, end) {}
  ConstIterator(const Iterator<T>& other) : Iterator<T>(other) {}
  ConstIterator(const ConstIterator& other) : Iterator<T>(other) {}
  ConstIterator(ConstIterator&& other) : Iterator<T>(std::move(other)) {}

  ConstIterator& operator=(const ConstIterator& other) {
    this->curent_node_ = other.curent_node_;
    this->end_node_ = other.end_node_;
    return *this;
  }
  const_reference operator*() { return this->curent_node_->value_; }
};

template <typename T, typename Comporator = std::less<T>>
class Tree {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator<T>;
  using const_iterator = ConstIterator<T>;
  using size_type = std::size_t;
  using Node = Node_tree<T>;

  Tree() : root_(nullptr), endNode_(new Node()), size_(0), comp_() {}
  Tree(const Tree& other);
  Tree(Tree&& other);
  ~Tree();

  Tree& operator=(const Tree& other);
  Tree& operator=(Tree&& other);

  void updateHeight(Node* node);

  void printTree(Node* node);
  void deleteTree(Node* node);
  int heightTree(Node* node);

  int getTreeBalance(Node* node);

  void turnLeft(Node** node);
  void turnRight(Node** node);
  void turnRightLeft(Node** node);
  void turnLeftRight(Node** node);
  void balancingTree(Node** node);

  void printTree();

  Node* find_min(Node* root) const;
  Node* find_max(Node* root) const;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void clear();

  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insertNonUniq(const value_type& value);

  void erase(iterator pos);
  void swap(Tree& other);
  void merge(Tree& other);
  void mergeNonUniq(Tree& other);
  iterator find(const_reference key);
  iterator lower_bound(const_reference key);
  iterator upper_bound(const_reference key);
  bool contains(const_reference key);

 private:
  void SwapNode(Node* fNode, Node* sNode);

  Node* root_;
  Node* endNode_;
  size_type size_ = 0U;
  Comporator comp_;
};
}  // namespace s21

#include "AVLtree.tpp"

#endif