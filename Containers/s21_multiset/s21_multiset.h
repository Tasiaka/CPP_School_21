#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <utility>

#include "../s21_set/s21_set.h"

namespace s21 {

template <typename Key>
class multiset : public set<Key> {
 public:
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using avltree = typename set<Key>::avltree;
  using iterator = typename avltree::iterator;
  using const_iterator = typename avltree::const_iterator;
  using size_type = size_t;

  multiset() : set<Key>() {}
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& m);
  multiset(multiset&& m);

  multiset& operator=(multiset&& m);
  multiset& operator=(const multiset& m);

  std::pair<iterator, bool> insert(const value_type& value);
  void merge(multiset& other);
  size_type count(const value_type& key);
  iterator lower_bound(const value_type& key);
  iterator upper_bound(const value_type& key);
  std::pair<iterator, iterator> equal_range(const value_type& key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

// Implementation of methods

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : multiset() {
  for (auto& item : items) {
    insert(item);
  }
}

template <typename Key>
multiset<Key>::multiset(multiset&& m) : set<Key>(std::move(m)) {}

template <typename Key>
multiset<Key>::multiset(const multiset& m) : set<Key>(m) {}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& m) {
  if (this != &m) {
    set<Key>::operator=(std::move(m));
  }
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset& m) {
  if (this != &m) {
    this->clear();
    set<Key>::operator=(m);
  }
  return *this;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, bool> multiset<Key>::insert(
    const value_type& value) {
  return this->tree_->insertNonUniq(value);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(
    const value_type& value) {
  return this->tree_->lower_bound(value);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(
    const value_type& value) {
  return this->tree_->upper_bound(value);
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const value_type& value) {
  return std::make_pair(lower_bound(value), upper_bound(value));
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(
    const value_type& value) {
  size_type result = 0;
  auto begin = lower_bound(value);
  auto end = upper_bound(value);
  while (begin != end) {
    ++result;
    ++begin;
  }
  return result;
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> results;
  (results.push_back(this->insert(std::forward<Args>(args))), ...);
  return results;
}

template <typename T>
void multiset<T>::merge(multiset& other) {
  this->tree_->mergeNonUniq(*other.tree_);
}

}  // namespace s21

#endif  // S21_MULTISET_H