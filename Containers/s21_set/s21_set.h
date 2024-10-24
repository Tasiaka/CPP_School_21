#ifndef S21_set_H
#define S21_set_H

#include "../AVLtree/AVLtree.h"

namespace s21 {

template <typename Key>
class set {
 public:
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using avltree = Tree<value_type>;
  using iterator = typename avltree::iterator;
  using const_iterator = typename avltree::const_iterator;
  using size_type = size_t;

  avltree* tree_;

 public:
  // Constructors
  set() : tree_(new avltree) {}
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();

  // Operators
  set& operator=(set&& s);
  set& operator=(const set& s);

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  // Lookup
  iterator find(const value_type& key);
  const_iterator find(const value_type& key) const;
  bool contains(const value_type& key) const;

  // Iterators
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

// Implementation of methods

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) : set() {
  for (auto& item : items) {
    insert(item);
  }
}

template <typename Key>
set<Key>::set(set&& s) : tree_(new avltree(std::move(*s.tree_))) {}

template <typename Key>
set<Key>::set(const set& s) : tree_(new avltree(*s.tree_)) {}

template <typename Key>
set<Key>::~set() {
  delete tree_;
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& s) {
  if (this != &s) {
    *tree_ = std::move(*s.tree_);
  }
  return *this;
}

template <typename Key>
set<Key>& set<Key>::operator=(const set& s) {
  if (this != &s) {
    clear();
    for (auto it = s.begin(); it != s.end(); ++it) {
      insert(*it);
    }
  }
  return *this;
}

template <typename Key>
bool set<Key>::empty() const {
  return tree_->empty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() const {
  return tree_->size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() const {
  return tree_->max_size();
}

template <typename Key>
void set<Key>::clear() {
  tree_->clear();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  return tree_->insert(value);
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  tree_->erase(pos);
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  return tree_->begin();
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return tree_->end();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::begin() const {
  return static_cast<const avltree&>(*tree_).begin();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::end() const {
  return static_cast<const avltree&>(*tree_).end();
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const value_type& key) {
  return tree_->find(key);
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::find(const value_type& key) const {
  return tree_->find(key);
}

template <typename Key>
bool set<Key>::contains(const value_type& key) const {
  return tree_->contains(key);
}

template <typename Key>
void set<Key>::swap(set& other) {
  std::swap(tree_, other.tree_);
}

template <typename Key>
void set<Key>::merge(set& other) {
  tree_->merge(*other.tree_);
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  std::vector<std::pair<iterator, bool>> results;
  (results.push_back(this->insert(std::forward<Args>(args))), ...);
  return results;
}

}  // namespace s21

#endif  // S21_set_H