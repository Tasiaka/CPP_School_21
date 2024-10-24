#ifndef S21_ARRAY
#define S21_ARRAY

#include <cstring>
#include <iostream>
#include <string>

namespace s21 {
template <typename T, size_t R>
class array {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef size_t size_type;

  array() { fill_by_zero(); }

  array(std::initializer_list<value_type> const& items) {
    if (items.size() > R)
      throw std::out_of_range("excess elements in struct initializer");

    if (R != 0) fill_by_zero();

    size_type counter = 0;
    for (auto n : items) {
      stat_array[counter++] = n;
    }
  }

  array(const array& a) {
    std::copy(a.stat_array, a.stat_array + R, stat_array);
  }

  array(array&& a) noexcept : stat_array{} {
    std::copy(a.stat_array, a.stat_array + R, stat_array);
  }

  ~array() = default;

  array& operator=(array&& a) noexcept {
    if (this != &a) {
      std::copy(a.stat_array, a.stat_array + R,
                stat_array);  // Correct way to copy elements
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= R) throw std::out_of_range("array element is out_of_range");
    return stat_array[pos];
  }

  reference operator[](size_type pos) noexcept { return stat_array[pos]; }
  const_reference front() noexcept { return stat_array[0]; }
  const_reference back() {
    if (empty()) throw std::runtime_error("accessing back of empty array");
    return this->operator[](R - 1);
  }

  iterator data() noexcept { return &stat_array[0]; }

  iterator begin() noexcept { return &stat_array[0]; }
  iterator end() noexcept { return &stat_array[R]; }

  bool empty() noexcept { return size() == 0; }
  size_type size() noexcept { return R; }
  size_type max_size() noexcept { return R; }

  void swap(array& other) noexcept {
    if (size() == other.size()) {
      value_type temp;
      for (size_type i = 0; i < R; i++) {
        temp = stat_array[i];
        stat_array[i] = other.stat_array[i];
        other.stat_array[i] = temp;
      }
    }
  }

  void fill(const_reference value) noexcept {
    std::fill_n(stat_array, R, value);
  }

 private:
  value_type stat_array[R];

  void fill_by_zero() noexcept { std::fill(stat_array, stat_array + R, T()); }
};

}  // namespace s21

#endif
