#ifndef S21_VECTOR
#define S21_VECTOR

#include <stddef.h>

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <stdexcept>

using std::copy;
using std::fill;
using std::max;
using std::swap;

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type =
      T;  // обозначения типа элементов, которые хранятся в векторе
  using reference = T &;  //обозначения ссылки на элемент типа T
  using const_reference = const T &;
  using iterator = T
      *;  //обозначения итератора, который является указателем на элемент типа T
  using const_iterator = const T *;
  using size_type = size_t;  //обозначения типа, который хранит размер вектора
  //Тип данных size_t в используется для представления размеров объектов в
  //байтах и часто встречается в стандартной библиотеке для описания размеров и
  //счетчиков

 private:
  iterator m_data;   //указывает на начало массива,
  size_type m_size;  //хранит текущий размер вектора, то есть количество
                     //элементов, которые в настоящее время находятся в векторе
  size_type m_capacity;  //хранит текущую емкость вектора, то есть максимальное
                         //количество элементов

  void makeClean() {
    if (m_data != nullptr) {
      delete[] m_data;
      m_data = nullptr;
    }
    m_size = 0;
    m_capacity = 0;
  }

 public:
  vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

  // explicit в C++ используется для предотвращения неявного преобразования
  // типов при использовании конструкторов. Когда вы видите explicit перед
  // определением конструктора, это означает, что конструктор не может быть
  // использован для неявного преобразования типов.

  explicit vector(size_type n) : m_data(nullptr), m_size(n), m_capacity(n) {
    if (n <= 0) {
      m_data = nullptr;
      // throw std::invalid_argument("Размер вектора должен быть больше нуля");
    } else {
      m_data = new value_type[n];
      fill(begin(), end(), 0);
    }
  }

  ~vector() { makeClean(); }

  //Этот конструктор принимает список инициализаторов
  //(std::initializer_list<T>) в качестве аргумента и создает новый экземпляр
  // vector, заполняя его значениями из переданного списка.

  vector(std::initializer_list<value_type> const &items)
      : m_data(nullptr), m_size(0), m_capacity(0) {
    if (items.size() != 0) {
      m_size = items.size();
      m_capacity = items.size();
      m_data = new value_type[items.size()];
      copy(items.begin(), items.end(), m_data);
    }
  }

  vector(const vector &v)
      : m_data(new value_type[v.m_capacity]),  // Инициализация должна начаться
                                               // с m_data
        m_size(v.m_size),
        m_capacity(v.m_capacity) {
    copy(v.m_data, v.m_data + m_size, m_data);
  }

  vector(vector &&v)
      : m_data(v.m_data), m_size(v.m_size), m_capacity(v.m_capacity) {
    v.m_data = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
  }

  vector &operator=(vector &&v) {
    if (this != &v) {
      makeClean();
      m_size = v.m_size;
      m_capacity = v.m_capacity;
      m_data = v.m_data;
      v.m_size = 0;
      v.m_capacity = 0;
      v.m_data = nullptr;
    }
    return *this;
  }

  vector &operator=(const vector &v) {
    if (this != &v) {
      makeClean();
      m_size = v.m_size;
      m_capacity = v.m_capacity;
      m_data = nullptr;
      if (m_size > 0) {
        m_data = new value_type[m_capacity]{};
        copy(v.m_data, v.m_data + m_size, m_data);
      }
    }
    return *this;
  }

  // Методы at и операторы индексации operator[] предоставляют доступ к
  // элементам вектора по позиции.
  reference at(size_type pos) {
    if (pos >= m_size) {
      throw std::out_of_range("Accessing element at position ");
    }
    return m_data[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= m_size) {
      throw std::out_of_range("Accessing element at position ");
    }
    return m_data[pos];
  }

  // operator[] позволяет получить доступ к элементу
  //вектора по его позиции. Он возвращает ссылку на элемент, расположенный по
  //индексу pos в массиве m_data, который хранит данные вектора.

  reference operator[](size_type pos) {
    if (pos >= m_size) {
      throw std::out_of_range("Accessing element at position ");
    }
    return m_data[pos];
  }

  // operator[] возвращает константную ссылку на элемент
  //вектора по его позиции.
  const_reference operator[](size_type pos) const {
    if (pos >= m_size) {
      throw std::out_of_range("Accessing element at position ");
    }
    return m_data[pos];
  }

  // возвращает 1 ый элемент
  const_reference front() const {
    if (m_size == 0) {
      throw std::out_of_range(
          "Attempting to access the front of an empty vector");
    }
    return m_data[0];
  }

  // последний элемент
  const_reference back() const {
    if (m_size == 0) {
      throw std::out_of_range(
          "Attempting to access the back of an empty vector");
    }
    return m_data[m_size - 1];
  }

  reference front() {
    if (m_size == 0) {
      throw std::out_of_range(
          "Attempting to access the front of an empty vector");
    }
    return m_data[0];
  }

  reference back() {
    if (m_size == 0) {
      throw std::out_of_range(
          "Attempting to access the back of an empty vector");
    }
    return m_data[m_size - 1];
  }

  // Итераторы — это абстрактный тип, который позволяет программисту обходить
  // элементы контейнера (например, массива, списка, вектора) последовательно,
  // не заботясь о внутренней организации данных.

  iterator data() noexcept { return m_data; }
  iterator begin() noexcept { return m_data; }
  iterator end() noexcept { return m_data + m_size; }

  //пуст ли контейнер

  bool empty() const noexcept { return m_size == 0; }

  size_type size() const { return m_size; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }

  //предназначена для увеличения емкости вектора до заданного размера.
  // Автоматическое определение типа

  void reserve(size_type size) {
    if (size > m_capacity) {
      auto newSize = max(size, static_cast<size_type>(m_capacity) * 2);
      auto tmp = new value_type[newSize];
      copy(m_data, m_data + m_size, tmp);
      delete[] m_data;
      m_data = tmp;
      m_capacity = newSize;
    } 
  }

  size_type capacity() const noexcept { return m_capacity; }

  //предназначена для уменьшения емкости вектора до его текущего размера.
  void shrink_to_fit() {
    if (m_size < m_capacity) {
      auto tmp = new value_type[m_size];
      copy(m_data, m_data + m_size, tmp);
      delete[] m_data;
      m_data = tmp;
      m_capacity = m_size;
    }
  }

  //для удаления всех элементов из контейнера, оставляя его пустым.
  void clear() noexcept { m_size = 0; }

  //предназначен для вставки элемента в указанную позицию внутри контейнера.
  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::length_error("Position must be within vector bounds");
    }
    size_type index_pos = pos - begin();
    if (m_size == m_capacity) {
      reserve(m_capacity * 2);
    }
    if (m_size == 0) {
      reserve(1);
    }
    std::move_backward(begin() + index_pos, end(), end() + 1);
    m_data[index_pos] =
        value;  // Исправлено присваивание значения новому элементу
    m_size++;
    return begin() + index_pos;
  }

  // удаления элемента из вектора по указанной позиции.
  void erase(iterator pos) {
    if (pos < begin() || pos >= end()) {
      throw std::length_error("Position must be within vector bounds");
    }
    std::move(pos + 1, end(), pos);
    m_size--;
  }

  // Этот метод добавляет элемент в конец вектора

  void push_back(const_reference value) {
    if (m_size == m_capacity) {
      reserve(m_capacity * 2);
    }
    if (m_size == 0) {
      reserve(2);
    }
    m_data[m_size++] = value;
  }

  //удаляет последний элемент из вектора.
  void pop_back() {
    if (m_size == 0) {
      return;
    }
    m_size--;
  }

  //предназначен для обмена содержимым двух векторов.
  void swap(vector &other) {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_data, other.m_data);
  }

  template <typename... Args>  //позволяет вставить несколько элементов в
                               //указанную позицию вектора.
  iterator insert_many(const_iterator pos,
                       Args &&...args) {  //создаем список и
                                          //передаем туда аргументы
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    iterator tmp_pos = (iterator)pos;
    for (auto &i : args_v) {  //для каждого элемента вызывается метод insert,
                              //который вставляет элемент в вектор на позицию,
                              //указанную итератором tmp_pos.
      tmp_pos = insert(tmp_pos, i) + 1;
    }
    return tmp_pos - 1;
  }

  //предназначен для вставки нескольких элементов в конец вектора
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), std::forward<Args>(args)...);
  }
};
}  

#endif
