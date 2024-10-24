#include <gtest/gtest.h>

#include <list>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

TEST(DoublyLinkedList, DefaultConstructor) {
  s21::list<char> test_custom;
  std::list<char> test_original;
  test_custom.size();
  EXPECT_EQ(test_original.size(), test_custom.size());
}

TEST(DoublyLinkedList, DefaultParameterized) {
  s21::list<char> test_custom(10);
  std::list<char> test_original(10);
  test_custom.size();
  auto test_original_it = test_original.begin();
  auto test_custom_it = test_custom.begin();
  EXPECT_EQ(test_original.size(), test_custom.size());
  EXPECT_EQ(*test_original_it, *test_custom_it);
}

TEST(DoublyLinkedList, DefaultParameterized_2) {
  ASSERT_THROW(s21::list<int> test_custom(-5), std::invalid_argument);
}

TEST(DoublyLinkedList, InitializerList) {
  s21::list<int> test_custom{1, 2, 3, 4, 5};
  std::list<int> test_original{1, 2, 3, 4, 5};
  auto test_original_it = test_original.begin();
  auto test_custom_it = test_custom.begin();
  ++test_original_it;
  ++test_custom_it;
  EXPECT_EQ(test_original.size(), test_custom.size());
  EXPECT_EQ(2, *test_custom_it);
  EXPECT_EQ(5, *--test_custom.end());
}

TEST(DoublyLinkedList, CopyConstructorAndOperator) {
  s21::list<char> test_original{'a', 'b', 'c'};
  s21::list<char> test_custom(test_original);
  EXPECT_EQ(3U, test_custom.size());
  auto test_original_it = test_original.begin();
  auto test_custom_it = test_custom.begin();

  for (; test_original_it != test_original.end(); ++test_original_it) {
    EXPECT_EQ(*test_original_it, *test_custom_it);
    ++test_custom_it;
  }
  s21::list<char> test_original_2(15);
  test_custom = test_original_2;
  EXPECT_EQ(15U, test_custom.size());
}

TEST(DoublyLinkedList, MoveConstructorAndOperator) {
  s21::list<char> test_original{'a', 'b', 'c'};
  s21::list<char> test_custom = std::move(test_original);
  EXPECT_NE(test_original.size(), test_custom.size());
  EXPECT_EQ(3U, test_custom.size());
  EXPECT_EQ(0U, test_original.size());
  test_custom = {'c', 'c', 'c', 'c'};
  for (auto test_custom_it = test_custom.begin();
       test_custom_it != test_custom.end(); ++test_custom_it) {
    EXPECT_EQ('c', *test_custom_it);
  }
  EXPECT_EQ(4U, test_custom.size());
}

TEST(DoublyLinkedList, CheckingElements) {
  s21::list<int> test_custom{1, 2, 3, 4, 5};
  std::list<int> test_original{1, 2, 3, 4, 5};
  EXPECT_EQ(test_original.front(), test_custom.front());
  EXPECT_EQ(test_original.back(), test_custom.back());
  test_custom = {};
  test_original = {};
  EXPECT_EQ(test_original.empty(), test_custom.empty());
  test_custom = {1};
  EXPECT_NE(test_original.empty(), test_custom.empty());
}

TEST(DoublyLinkedList, AlteringList) {
  s21::list<int> test_custom{};
  test_custom.push_back(10);
  test_custom.push_back(11);
  test_custom.push_front(9);
  test_custom.push_front(8);

  std::list<int> test_original{};
  test_original.push_back(10);
  test_original.push_back(11);
  test_original.push_front(9);
  test_original.push_front(8);

  std::list<int>::const_iterator test_original_it = test_original.begin();
  s21::list<int>::const_iterator test_custom_it = test_custom.begin();
  for (; test_original_it != test_original.end(); ++test_original_it) {
    EXPECT_EQ(*test_original_it, *test_custom_it);
    test_custom_it++;
  }

  test_custom.pop_back();
  test_custom.pop_front();
  test_original.pop_back();
  test_original.pop_front();
  EXPECT_EQ(test_original.front(), test_custom.front());
  EXPECT_EQ(test_original.back(), test_custom.back());

  s21::list<int>::iterator temp = test_custom.end();
  EXPECT_THROW(test_custom.erase(temp), std::out_of_range);
}

TEST(DoublyLinkedList, Reverse) {
  s21::list<int> list1 = {2, 6, 8, 3, -9, 0, 3, 3, 4, 7, 9, 100};
  s21::list<int> list2 = {-1, -2, 2, 3, 4, 4, 5, 10, 15};
  std::list<int> list1_original = {2, 6, 8, 3, -9, 0, 3, 3, 4, 7, 9, 100};
  std::list<int> list2_original = {-1, -2, 2, 3, 4, 4, 5, 10, 15};

  list1.reverse();
  list2.reverse();
  list1_original.reverse();
  list2_original.reverse();

  std::list<int>::const_iterator list1_original_it = list1_original.end();
  s21::list<int>::const_iterator list1_it = list1.end();
  list1_original_it--;
  list1_it--;
  for (; list1_original_it != --list1_original.begin(); --list1_original_it) {
    EXPECT_EQ(*list1_original_it, *list1_it);
    --list1_it;
  }

  std::list<int>::iterator list2_original_it = list2_original.end();
  s21::list<int>::iterator list2_it = list2.end();
  list2_original_it--;
  list2_it--;
  for (; list2_original_it != --list2_original.begin(); --list2_original_it) {
    EXPECT_EQ(*list2_original_it, *list2_it);
    --list2_it;
  }
}

TEST(DoublyLinkedList, Unique) {
  s21::list<int> list1 = {2, 2, 2, 6, 8, 3,   2, -9, 0,
                          3, 3, 4, 7, 9, 100, 0, 0,  0};
  std::list<int> list1_original = {2, 2, 2, 6, 8, 3,   2, -9, 0,
                                   3, 3, 4, 7, 9, 100, 0, 0,  0};
  auto size_before = list1.size();
  EXPECT_EQ(list1_original.size(), list1.size());

  list1.unique();
  list1_original.unique();
  EXPECT_LT(list1.size(), size_before);
  EXPECT_EQ(list1_original.size(), list1.size());

  std::list<int>::const_iterator list1_original_it = list1_original.end();
  s21::list<int>::const_iterator list1_it = list1.end();
  list1_original_it--;
  list1_it--;
  for (; list1_original_it != --list1_original.begin(); --list1_original_it) {
    EXPECT_EQ(*list1_original_it, *list1_it);
    --list1_it;
  }
}

TEST(DoublyLinkedList, Splice) {
  s21::list<int> list1 = {2, 6, 8, 3, -9, 0, 3, 3, 4, 7, 9, 100};
  s21::list<int> list2 = {-1, -2, 2, 3, 4, 4, 5, 10, 15};
  std::list<int> list1_original = {2, 6, 8, 3, -9, 0, 3, 3, 4, 7, 9, 100};
  std::list<int> list2_original = {-1, -2, 2, 3, 4, 4, 5, 10, 15};

  auto it_custom = ++list1.begin();
  auto it_original = ++list1_original.begin();
  list1.splice(it_custom, list2);
  list1_original.splice(it_original, list2_original);

  EXPECT_EQ(0U, list2.size());
  EXPECT_EQ(0U, list2_original.size());

  it_custom--;
  it_original--;

  for (; it_original != list1_original.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it_custom);
    ++it_custom;
  }
}

TEST(DoublyLinkedList, Sort_1) {
  s21::list<int> list1 = {-1, -2, 2, 3, 4, 4, 5, 10, 15};
  std::list<int> list1_original = {-1, -2, 2, 3, 4, 4, 5, 10, 15};
  list1.sort();
  list1_original.sort();

  auto it_custom = list1.begin();
  auto it_original = list1_original.begin();
  for (; it_original != list1_original.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it_custom);
    ++it_custom;
  }
  EXPECT_EQ(list1_original.size(), list1.size());
}

TEST(DoublyLinkedList, Sort_2) {
  s21::list<char> list1 = {'a', 'b', 'c'};
  std::list<char> list1_original = {'a', 'b', 'c'};
  list1.sort();
  list1_original.sort();

  auto it_custom = list1.begin();
  auto it_original = list1_original.begin();
  for (; it_original != list1_original.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it_custom);
    ++it_custom;
  }
  EXPECT_EQ(list1_original.size(), list1.size());
}

TEST(DoublyLinkedList, Sort_3) {
  s21::list<char> list1 = {2, 6, 8, 3, -9, 0, 3, 3, 4, 7, 9, 100};
  std::list<char> list1_original = {2, 6, 8, 3, -9, 0, 3, 3, 4, 7, 9, 100};
  list1.sort();
  list1_original.sort();

  auto it_custom = list1.begin();
  auto it_original = list1_original.begin();
  for (; it_original != list1_original.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it_custom);
    ++it_custom;
  }
  EXPECT_EQ(list1_original.size(), list1.size());
}

TEST(DoublyLinkedList, Merge_1) {
  s21::list<int> list1 = {2, 6, 8, 3, -9, 0, 3, 3, 4, 7, 9, 100};
  s21::list<int> list2 = {-1, -2, 2, 3, 4, 4, 5, 10, 15};
  std::list<int> list1_original = {2, 6, 8, 3, -9, 0, 3, 3, 4, 7, 9, 100};
  std::list<int> list2_original = {-1, -2, 2, 3, 4, 4, 5, 10, 15};

  auto it_custom = list1.begin();
  auto it_original = list1_original.begin();
  list1.merge(list2);
  list1_original.merge(list2_original);

  EXPECT_EQ(0U, list2.size());
  EXPECT_EQ(0U, list2_original.size());
  EXPECT_EQ(list1_original.size(), list1.size());

  for (; it_original != list1_original.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it_custom);
    ++it_custom;
  }
}

TEST(DoublyLinkedList, Merge_2) {
  s21::list<int> list1 = {};
  s21::list<int> list2 = {-1, -2, 2, 3, 4, 4, 5, 10, 15};
  std::list<int> list1_original = {};
  std::list<int> list2_original = {-1, -2, 2, 3, 4, 4, 5, 10, 15};

  auto it_custom = list1.begin();
  auto it_original = list1_original.begin();
  list1.merge(list2);
  list1_original.merge(list2_original);

  EXPECT_EQ(0U, list2.size());
  EXPECT_EQ(0U, list2_original.size());
  EXPECT_EQ(list1_original.size(), list1.size());

  for (; it_original != list1_original.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it_custom);
    ++it_custom;
  }
}

TEST(DoublyLinkedList, Merge_3) {
  s21::list<int> list1 = {-5};
  s21::list<int> list2 = {-1, -2, 2, 3, 4, 4, 5, 10, 15};
  std::list<int> list1_original = {-5};
  std::list<int> list2_original = {-1, -2, 2, 3, 4, 4, 5, 10, 15};

  auto it_custom = list1.begin();
  auto it_original = list1_original.begin();
  list1.merge(list2);
  list1_original.merge(list2_original);

  EXPECT_EQ(0U, list2.size());
  EXPECT_EQ(0U, list2_original.size());
  EXPECT_EQ(list1_original.size(), list1.size());

  for (; it_original != list1_original.end(); ++it_original) {
    EXPECT_EQ(*it_original, *it_custom);
    ++it_custom;
  }
}

TEST(DoublyLinkedList, ConstIterator) {
  s21::list<int> list1 = {2, 6, 8, 3, -9, 0, 3, 3, 4, 7, 9, 100};
  s21::list<int>::iterator list1_it = list1.begin();
  s21::list<int>::const_iterator list1_c_it = list1_it;

  ++list1_it;
  ++list1_c_it;
  bool result = (list1_c_it == list1_it) ? 1 : 0;
  EXPECT_EQ(1, result);
  EXPECT_EQ(6, *list1_c_it);

  list1_c_it--;
  result = (list1_c_it != list1_it) ? 1 : 0;
  EXPECT_EQ(1, result);

  ++list1_it;
  list1_c_it = list1_it;
  EXPECT_EQ(*list1_it, *list1_c_it);

  s21::list<int>::const_iterator list_c_it2 = list1.begin();
  s21::list<int>::const_iterator list_c_it3 = list1.end();
  result = (list_c_it2 == list_c_it3) ? 1 : 0;
  EXPECT_EQ(0, result);
  result = (list_c_it2 != list_c_it3) ? 1 : 0;
  EXPECT_EQ(1, result);
}

TEST(DoublyLinkedList, InsertMany) {
  s21::list<int> list1 = {1, 5, 6};
  auto it = ++list1.begin();
  list1.insert_many(it, 2, 3, 4);
  int check = 1;
  for (auto it_temp = list1.begin(); it_temp != list1.end(); ++it_temp) {
    EXPECT_EQ(check++, *it_temp);
  }
  EXPECT_EQ(7, check);
  EXPECT_EQ(6U, list1.size());
  EXPECT_EQ(5, *it);
}

TEST(DoublyLinkedList, InsertManyFront) {
  s21::list<int> list1 = {3, 4, 5};
  list1.insert_many_front(0, 1, 2);
  int check = 0;
  for (auto it_temp = list1.begin(); it_temp != list1.end(); ++it_temp) {
    EXPECT_EQ(check++, *it_temp);
  }
  EXPECT_EQ(6, check);
  EXPECT_EQ(6U, list1.size());
}

TEST(DoublyLinkedList, InsertManyBack) {
  s21::list<int> list1 = {0, 1, 2};
  list1.insert_many_back(3, 4, 5, 6);
  int check = 0;
  for (auto it_temp = list1.begin(); it_temp != list1.end(); ++it_temp) {
    EXPECT_EQ(check++, *it_temp);
  }
  EXPECT_EQ(7, check);
  EXPECT_EQ(7U, list1.size());
}

TEST(List_Access, front) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ(a.front(), 1);
}

TEST(List_Access, back) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ(a.back(), 3);
}

TEST(List_Capacity, empty_True) {
  s21::list<int> a = s21::list<int>();

  EXPECT_EQ(a.empty(), 1);
}

TEST(List_Capacity, empty_False) {
  s21::list<int> a = {1, 2};

  EXPECT_EQ(a.empty(), 0);
}

TEST(List_Capacity, size) {
  s21::list<int> a = {1, 2};

  EXPECT_EQ(a.size(), 2U);
}

TEST(List_Iinitialize, Default) {
  s21::list<int> a = s21::list<int>();
  EXPECT_EQ(a.size(), 0U);
}

TEST(List_Iinitialize, Initializer_List) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ(a.front(), 1);
}

TEST(List_Iinitialize, Copy) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = a;
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(b.front(), 1);
}

TEST(List_Iinitialize, Move) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = s21::list<int>((s21::list<int> &&) a);
  EXPECT_EQ(a.size(), 0U);
  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ(b.front(), 1);
}

TEST(List_Iterators, begin) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ(*a.begin(), 1);
}

TEST(List_Modifiers, clear) {
  s21::list<int> a = {1, 2, 3};
  a.clear();
  EXPECT_EQ(a.size(), 0U);
}

TEST(List_Modifiers, erase) {
  s21::list<int> a = {1, 2, 3};
  a.erase(a.begin());
  EXPECT_EQ(a.size(), 2U);
  EXPECT_EQ(*a.begin(), 2);
}

TEST(List_Modifiers, push_back) {
  s21::list<int> a = {1, 2, 3};
  a.push_back(4);
  EXPECT_EQ(a.size(), 4U);
  EXPECT_EQ(a.back(), 4);
}

TEST(List_Modifiers, pop_back) {
  s21::list<int> a = {1, 2, 3};
  a.pop_back();
  EXPECT_EQ(a.size(), 2U);
  EXPECT_EQ(a.back(), 2);
}

TEST(List_Modifiers, push_front) {
  s21::list<int> a = {1, 2, 3};
  a.push_front(0);
  EXPECT_EQ(a.size(), 4U);
  EXPECT_EQ(a.front(), 0);
}

TEST(List_Modifiers, pop_front) {
  s21::list<int> a = {1, 2, 3};
  a.pop_front();
  EXPECT_EQ(a.size(), 2U);
  EXPECT_EQ(a.front(), 2);
}

TEST(List_Modifiers, swap) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = {4, 5, 6, 7};
  a.swap(b);
  EXPECT_EQ(a.size(), 4U);
  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ(a.front(), 4);
  EXPECT_EQ(b.front(), 1);
}

TEST(List_Modifiers, reverse) {
  s21::list<int> a = {1, 2, 3};
  a.reverse();
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ(a.front(), 3);
  EXPECT_EQ(a.back(), 1);
}

TEST(List_Modifiers, unique) {
  s21::list<int> a = {1, 2, 3, 3, 4, 5, 6, 4};
  a.unique();
  EXPECT_EQ(a.size(), 7U);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 4);
}

TEST(List_Modifiers, sort) {
  s21::list<int> a = {1, 3, 0, 7, -5};
  a.sort();
  EXPECT_EQ(a.size(), 5U);
  EXPECT_EQ(a.front(), -5);
  EXPECT_EQ(a.back(), 7);
}

TEST(List_Modifiers, insert_many_back) {
  s21::list<int> a = {1};
  a.insert_many_back(2, 3, 4, 5);
  EXPECT_EQ(a.size(), 5U);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 5);
}

TEST(List_Modifiers, insert_many_front) {
  s21::list<int> a = {1};
  a.insert_many_front(-5, -4, -3, -2, -1, 0);
  EXPECT_EQ(a.size(), 7U);
  EXPECT_EQ(a.front(), -5);
  EXPECT_EQ(a.back(), 1);
}
