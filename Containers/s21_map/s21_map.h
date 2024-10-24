#ifndef S21_map_H
#define S21_map_H

#include <utility>
#include <vector>

#include "../AVLtree/AVLtree.h"

namespace s21 {

template <typename T>
struct Comparatormap {
  bool operator()(T val1, T val2) { return val1.first < val2.first; }
};

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using avltree = Tree<value_type, Comparatormap<value_type>>;
  using iterator = typename avltree::iterator;
  using const_iterator = typename avltree::const_iterator;
  using size_type = size_t;

 private:
  avltree *tree_;

 public:
  // Constructors
  map() : tree_(new avltree) {}
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();

  // Operators
  map &operator=(map &&m);
  map &operator=(const map &m);

  mapped_type &operator[](const key_type &key);
  mapped_type &at(const key_type &key);

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void clear();

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  // Lookup
  bool contains(const key_type &key) const;

  // Iterators
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Part 3
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

// Implementation of methods

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : map() {
  for (auto &item : items) {
    insert(item);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map &m) : tree_(new avltree(*m.tree_)) {}

template <typename Key, typename T>
map<Key, T>::map(map &&m) : tree_(new avltree(std::move(*m.tree_))) {}

template <typename Key, typename T>
map<Key, T>::~map() {
  delete tree_;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&m) {
  if (this != &m) {
    *tree_ = std::move(*m.tree_);
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &m) {
  if (this != &m) {
    clear();
    for (auto it = m.begin(); it != m.end(); ++it) {
      insert(*it);
    }
  }
  return *this;
}

template <typename Key, typename T>
bool map<Key, T>::empty() const {
  return tree_->empty();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() const {
  return tree_->size();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() const {
  return tree_->max_size();
}

template <typename Key, typename T>
void map<Key, T>::clear() {
  tree_->clear();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  return tree_->insert(value);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const key_type &key, const mapped_type &obj) {
  return tree_->insert(std::make_pair(key, obj));
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  tree_->erase(pos);
}

template <typename Key, typename T>
void map<Key, T>::swap(map &other) {
  tree_->swap(*other.tree_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  tree_->merge(*other.tree_);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return tree_->begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return tree_->end();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::begin() const {
  return static_cast<const avltree &>(*tree_).begin();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::end() const {
  return static_cast<const avltree &>(*tree_).end();
}

template <typename Key, typename T>
bool map<Key, T>::contains(const key_type &key) const {
  return tree_->contains(std::make_pair(key, mapped_type()));
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> results;
  (results.push_back(this->insert(std::forward<Args>(args))), ...);
  return results;
}

// =---==-=-=-=-=-=-=-=-=-==-=-=-=

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::operator[](
    const key_type &key) {
  value_type temp_pair = std::make_pair(key, T{});
  auto it = tree_->find(temp_pair);

  if (it != tree_->end()) {
    return (*it).second;
  } else {
    auto new_it = insert(key, T{});
    return (*new_it.first).second;
  }
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::at(const key_type &key) {
  value_type temp_pair = std::make_pair(key, T{});
  auto it = tree_->find(temp_pair);
  if (it != tree_->end()) {
    return (*it).second;
  } else {
    throw std::out_of_range("Key not found");
  }
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  value_type val = std::make_pair(key, obj);
  std::pair<iterator, bool> res = tree_->insert(val);
  if (!res.second) {
    (*res.first).second = obj;
  }
  return res;
}

}  // namespace s21

#endif  // S21_map_H
