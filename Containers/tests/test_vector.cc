#include <iostream>
#include <vector>

#include "../s21_containers.h"
#include "../s21_containersplus.h"
#include "gtest/gtest.h"

template <typename value_type>
bool compare_vectors(s21::vector<value_type> &v1, std::vector<value_type> &v2) {
  if (v1.size() != v2.size()) {
    std::cout << "v1.size = " << v1.size() << " v2.size = " << v2.size()
              << '\n';
    return false;
  }
  if (v1.capacity() != v2.capacity()) {
    std::cout << "v1.capacity = " << v1.capacity()
              << " v2.capacity = " << v2.capacity() << '\n';
    return false;
  }
  for (size_t i = 0; i < v1.size(); i++) {
    if (v1[i] != v2[i]) {
      std::cout << "v1[" << i << "] = " << v1[i] << " v2[" << i
                << "] = " << v2[i] << '\n';
      return false;
    }
  }
  return true;
}

TEST(TestVector, Constructor_1) {
  s21::vector<int> vector1;
  std::vector<int> vector2;
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Constructor_2) {
  s21::vector<long double> vector1;
  std::vector<long double> vector2;
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Constructor_3) {
  s21::vector<char> vector1;
  std::vector<char> vector2;
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Constructor_4) {
  s21::vector<int> vector1(1);
  std::vector<int> vector2(1);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Constructor_5) {
  s21::vector<long double> vector1(35);
  std::vector<long double> vector2(35);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Constructor_6) {
  s21::vector<char> vector1(0);
  std::vector<char> vector2(0);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Constructor_7) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Constructor_8) {
  s21::vector<long double> vector1 = {1.1, -222.22, 0.123};
  std::vector<long double> vector2 = {1.1, -222.22, 0.123};
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Constructor_9) {
  s21::vector<char> vector1 = {'A', ' ', '(', 'r'};
  std::vector<char> vector2 = {'A', ' ', '(', 'r'};
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Constructor_10) {
  s21::vector<int> vector1{1, 2, 3, 4, 5, 6};
  s21::vector<int> vector2(vector1);
  std::vector<int> vector3{1, 2, 3, 4, 5, 6};
  std::vector<int> vector4(vector3);
  EXPECT_TRUE(compare_vectors(vector2, vector4));
}

TEST(TestVector, Constructor_11) {
  s21::vector<int> vector1(0);
  s21::vector<int> vector2(vector1);
  std::vector<int> vector3(0);
  std::vector<int> vector4(vector3);
  EXPECT_TRUE(compare_vectors(vector2, vector4));
}

TEST(TestVector, Constructor_12) {
  s21::vector<int> vector1{1, 2, 3, 4, 5, 6};
  s21::vector<int> vector2(std::move(vector1));
  std::vector<int> vector3{1, 2, 3, 4, 5, 6};
  std::vector<int> vector4(std::move(vector3));
  EXPECT_TRUE(compare_vectors(vector2, vector4));
}

TEST(TestVector, Constructor_13) {
  s21::vector<int> vector1(0);
  s21::vector<int> vector2(std::move(vector1));
  std::vector<int> vector3(0);
  std::vector<int> vector4(std::move(vector3));
  EXPECT_TRUE(compare_vectors(vector2, vector4));
}

TEST(TestVector, Assignment_1) {
  s21::vector<long double> vector1 = {1.1, -222.22, 0.123};
  s21::vector<long double> vector2;
  std::vector<long double> vector3 = {1.1, -222.22, 0.123};
  std::vector<long double> vector4;
  vector2 = std::move(vector1);
  vector4 = std::move(vector3);
  EXPECT_TRUE(compare_vectors(vector2, vector4));
}

TEST(TestVector, Assignment_2) {
  s21::vector<long double> vector1 = {1.1, -222.22, 0.123};
  std::vector<long double> vector2 = {1.1, -222.22, 0.123};
  vector1 = *&vector1;
  vector2 = *&vector2;
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Assignment_3) {
  const s21::vector<long double> vector1 = {1.1, -222.22, 0.123};
  const std::vector<long double> vector2 = {1.1, -222.22, 0.123};
  s21::vector<long double> vector3;
  std::vector<long double> vector4;
  vector3 = vector1;
  vector4 = vector2;
  EXPECT_TRUE(compare_vectors(vector3, vector4));
}

TEST(TestVector, At_1) {
  s21::vector<int> vector1{1, 2, 3, 4, 5, 6};
  EXPECT_THROW(vector1[6], std::out_of_range);
}

TEST(TestVector, At_2) {
  const s21::vector<int> vector1{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(vector1[5], 6);
}

TEST(TestVector, Front_1) {
  s21::vector<int> vector1;
  EXPECT_THROW(vector1.front(), std::logic_error);
}

TEST(TestVector, Front_2) {
  s21::vector<long double> vector1 = {1.1, -222.22, 0.123};
  std::vector<long double> vector2 = {1.1, -222.22, 0.123};
  EXPECT_EQ(vector1.front(), vector2.front());
}

TEST(TestVector, Back_1) {
  s21::vector<int> vector1;
  EXPECT_THROW(vector1.back(), std::logic_error);
}

TEST(TestVector, Back_2) {
  s21::vector<long double> vector1 = {1.1, -222.22, 0.123};
  std::vector<long double> vector2 = {1.1, -222.22, 0.123};
  EXPECT_EQ(vector1.back(), vector2.back());
}

TEST(TestVector, Data_1) {
  s21::vector<long double> vector1 = {1.1, -222.22, 0.123};
  std::vector<long double> vector2 = {1.1, -222.22, 0.123};
  EXPECT_EQ(*vector1.data(), *vector2.data());
}

TEST(TestVector, Empty_1) {
  s21::vector<long double> vector1 = {1.1, -222.22, 0.123};
  EXPECT_FALSE(vector1.empty());
}

TEST(TestVector, Empty_2) {
  s21::vector<long double> vector1;
  EXPECT_TRUE(vector1.empty());
}

TEST(TestVector, MaxSize_1) {
  s21::vector<int> vector1 = {1, 2, 3};
  std::vector<int> vector2 = {1, 2, 3};
#ifdef MACOS
  EXPECT_EQ(vector1.max_size(), vector2.max_size());
#endif
}

TEST(TestVector, Reserve_1) {
  s21::vector<int> vector1 = {1, 2, 3};
  std::vector<int> vector2 = {1, 2, 3};
  vector1.reserve(50);
  vector2.reserve(50);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Reserve_2) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.reserve(1);
  vector2.reserve(1);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Shrink_1) {
  s21::vector<int> vector1 = {1, 2, 3};
  std::vector<int> vector2 = {1, 2, 3};
  vector1.reserve(50);
  vector2.reserve(50);
  vector1.shrink_to_fit();
  vector2.shrink_to_fit();
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Shrink_2) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.reserve(1);
  vector2.reserve(1);
  vector1.shrink_to_fit();
  vector2.shrink_to_fit();
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Clear_1) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.clear();
  vector2.clear();
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Insert_1) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  EXPECT_THROW(vector1.insert(vector1.begin() - 1, 7), std::length_error);
}

TEST(TestVector, Insert_2) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  EXPECT_THROW(vector1.insert(vector1.end() + 1, 7), std::length_error);
}

TEST(TestVector, Insert_3) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.insert(vector1.end(), 7);
  vector2.insert(vector2.end(), 7);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Insert_4) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.insert(vector1.begin(), 7);
  vector2.insert(vector2.begin(), 7);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Insert_5) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.reserve(1);
  vector2.reserve(1);
  vector1.insert(vector1.begin(), 777);
  vector2.insert(vector2.begin(), 777);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Erase_1) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  EXPECT_THROW(vector1.erase(vector1.begin() - 1), std::length_error);
}

TEST(TestVector, Erase_2) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  EXPECT_THROW(vector1.erase(vector1.end() + 1), std::length_error);
}

TEST(TestVector, Erase_3) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.erase(vector1.end() - 1);
  vector2.erase(vector2.end() - 1);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Erase_4) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.erase(vector1.begin());
  vector2.erase(vector2.begin());
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, PushBack_1) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.push_back(777);
  vector2.push_back(777);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, PopBack_1) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.pop_back();
  vector2.pop_back();
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Swap_1) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  s21::vector<int> vector2 = {1, 2, 3};
  std::vector<int> vector3 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector4 = {1, 2, 3};
  vector1.swap(vector2);
  vector3.swap(vector4);
  EXPECT_TRUE(compare_vectors(vector1, vector3));
  EXPECT_TRUE(compare_vectors(vector2, vector4));
}

TEST(TestVector, Swap_2) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  s21::vector<int> vector2 = {1, 2, 3};
  std::vector<int> vector3 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector4 = {1, 2, 3};
  vector2.swap(vector1);
  vector4.swap(vector3);
  EXPECT_TRUE(compare_vectors(vector1, vector3));
  EXPECT_TRUE(compare_vectors(vector2, vector4));
}

TEST(TestVector, Insert_many_1) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  vector1.insert_many(vector1.begin(), -1);
  EXPECT_EQ(vector1[0], -1);
  EXPECT_EQ(vector1[1], 1);
  EXPECT_EQ(vector1.size(), (size_t)7);
}

TEST(TestVector, Insert_many_2) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  vector1.insert_many(vector1.begin(), -2, -1);
  EXPECT_EQ(vector1[0], -2);
  EXPECT_EQ(vector1[1], -1);
  EXPECT_EQ(vector1[2], 1);
  EXPECT_EQ(vector1.size(), (size_t)8);
}

TEST(TestVector, Insert_many_3) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.insert_many(vector1.begin());
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Insert_many_4) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 11, 12, 13, 14, 15, 16, 4, 5, 6};
  vector1.insert_many(vector1.begin() + 3, 11, 12, 13, 14, 15, 16);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Insert_many_Back_1) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1};
  vector1.insert_many_back(6, 5, 4, 3, 2, 1);
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(TestVector, Insert_many_Back_2) {
  s21::vector<int> vector1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> vector2 = {1, 2, 3, 4, 5, 6};
  vector1.insert_many_back();
  EXPECT_TRUE(compare_vectors(vector1, vector2));
}

TEST(Vector_Access, at_Good) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ(a.at(0), 1);
}

TEST(Vector_Access, at_Bad) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3U);
  EXPECT_ANY_THROW(a.at(3));
}

TEST(Vector_Access, at_Operation_Good) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ(a[0], 1);
}

TEST(Vector_Access, at_Operation_Bad) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3U);
  EXPECT_ANY_THROW(a[3]);
}

TEST(Vector_Access, front) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.front(), 1);
}

TEST(Vector_Access, back) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.back(), 3);
}

TEST(Vector_Access, data) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(*(a.data()), 1);
}

TEST(Vector_Capacity, empty_True) {
  s21::vector<int> a = {};
  EXPECT_EQ(a.empty(), 1);
}

TEST(Vector_Capacity, empty_False) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.empty(), 0);
}

TEST(Vector_Capacity, size) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3U);
}

TEST(Vector_Capacity, max_size) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.max_size(),
            std::numeric_limits<s21::vector<int>::size_type>::max());
}

TEST(Vector_Capacity, reserve) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ(a.capacity(), 3U);
  a.reserve(10);
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ(a.capacity(), 10U);
}

TEST(Vector_Capacity, capacity) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ(a.capacity(), 3U);
}

TEST(S21VectorTest, OutOfBoundsAccess) {
  s21::vector<int> vec{1, 2, 3};

  EXPECT_THROW(vec[3], std::out_of_range);
  EXPECT_THROW(vec[5], std::out_of_range);
  EXPECT_THROW(vec[100], std::out_of_range);
}

TEST(S21VectorTest, FrontElementAccess) {
  s21::vector<int> vec;

  EXPECT_THROW(vec.front(), std::out_of_range);

  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);

  EXPECT_EQ(vec.front(), 10);
}

TEST(S21VectorTest, out_of_range) {
  s21::vector<int> vec;

  EXPECT_THROW(vec.back(), std::out_of_range);

  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);

  EXPECT_EQ(vec.back(), 30);
}

TEST(S21VectorTest1, out_of_range) {
  s21::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);

  EXPECT_THROW(vec[3], std::out_of_range);
  EXPECT_THROW(vec[100], std::out_of_range);
}

TEST(S21VectorTest2, const_out_of_range) {
  const s21::vector<int> constVec = {1, 2, 3};

  EXPECT_THROW(constVec[100], std::out_of_range);
}

TEST(S21VectorTest3, pop_back_empty) {
  s21::vector<int> vec;
  vec.pop_back();

  EXPECT_EQ(vec.size(), 0U);
}

TEST(S21VectorTest4, insert_to_empty) {
  s21::vector<int> vec;
  vec.insert(vec.begin(), 1);

  EXPECT_EQ(vec.size(), 1U);
}

TEST(Vector_Capacity, shrink_to_fit) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ(a.capacity(), 3U);
  a.reserve(10);
  EXPECT_EQ(a.capacity(), 10U);
  a.shrink_to_fit();
  EXPECT_EQ(a.capacity(), 3U);
}
