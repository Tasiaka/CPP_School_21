#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <string>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

TEST(S21multisetTest, DefaultConstructor) {
  s21::multiset<int> miltiset;
  ASSERT_TRUE(miltiset.empty());
  ASSERT_EQ(0U, miltiset.size());
  EXPECT_EQ(miltiset.size(), 0U);
}

TEST(S21multisetTest, InitializerListConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3, 2, 4, 2};
  ASSERT_FALSE(ms1.empty());
  ASSERT_EQ(6U, ms1.size());
}

TEST(S21multisetTest, CopyConstructor) {
  s21::multiset<int> set({1, 2, 3, 2});
  s21::multiset<int> copy(set);
  ASSERT_FALSE(set.empty());
  ASSERT_FALSE(copy.empty());
  ASSERT_EQ(set.size(), copy.size());
}

TEST(S21multisetTest, MoveConstructor) {
  s21::multiset<int> multiset({1, 2, 3});
  s21::multiset<int> move(std::move(multiset));
  ASSERT_TRUE(multiset.empty());
  ASSERT_FALSE(move.empty());
  ASSERT_EQ(3U, move.size());
  EXPECT_EQ(multiset.size(), 0U);
}

TEST(S21multisetTest, AssignmentOperator1) {
  s21::multiset<int> multiset1({1, 2, 3});
  s21::multiset<int> multiset2;
  multiset2 = multiset1;
  ASSERT_FALSE(multiset1.empty());
  ASSERT_FALSE(multiset2.empty());
  ASSERT_EQ(multiset1.size(), multiset2.size());
}

TEST(S21multisetTest, AssignmentOperator2) {
  s21::multiset<int> multiset1({1, 2, 3});
  s21::multiset<int> multiset2;
  multiset2 = std::move(multiset1);
  ASSERT_TRUE(multiset1.empty());
  ASSERT_FALSE(multiset2.empty());
  ASSERT_EQ(3U, multiset2.size());
}

TEST(S21multisetTest, IteratorBegin) {
  s21::multiset<int> multiset({1, 2, 3, 1, 5});
  s21::multiset<int>::iterator iterat;
  iterat = multiset.begin();
  s21::multiset<int>::iterator itFind;
  itFind = multiset.find(1);
  ASSERT_TRUE(iterat == itFind);
  ASSERT_EQ(itFind, iterat);
}

TEST(S21multisetTest, CapacityEmpty) {
  s21::multiset<int> multiset({1, 2, 3});
  s21::multiset<int> empty;
  ASSERT_FALSE(multiset.empty());
  ASSERT_TRUE(empty.empty());
}

TEST(S21multisetTest, CapacitySize) {
  s21::multiset<int> multiset({1, 2, 3});
  s21::multiset<int> empty;
  EXPECT_EQ(multiset.size(), 3U);
  EXPECT_EQ(empty.size(), 0U);
}

TEST(S21multisetTest, CapacityMaxSize) {
  s21::multiset<int> multiset;
  ASSERT_TRUE(multiset.max_size() > 0);
}

TEST(S21multisetTest, ModifierClear) {
  s21::multiset<int> multiset({1, 2, 3});
  ASSERT_FALSE(multiset.empty());
  multiset.clear();
  ASSERT_TRUE(multiset.empty());
  EXPECT_EQ(multiset.size(), 0U);
}

TEST(S21multisetTest, ModifierInsert1) {
  s21::multiset<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(1);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  set.insert(5);
  EXPECT_EQ(set.size(), 3U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(5));
}

TEST(S21multisetTest, ModifierInsert2) {
  s21::multiset<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(10);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(10));
}

TEST(S21multisetTest, ModifierErase) {
  s21::multiset<int> set = {1, 2, 3, 2};
  EXPECT_EQ(set.size(), 4U);
  auto it = set.find(2);
  set.erase(it);
  EXPECT_EQ(set.size(), 3U);
  ASSERT_TRUE(set.contains(2));
}

TEST(S21multisetTest, ModifierSwap) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2 = {4, 5, 6};
  multiset1.swap(multiset2);
  EXPECT_EQ(multiset1.size(), 3U);
  EXPECT_EQ(multiset2.size(), 3U);
  ASSERT_TRUE(multiset1.contains(4));
  ASSERT_TRUE(multiset1.contains(5));
  ASSERT_TRUE(multiset1.contains(6));
  ASSERT_TRUE(multiset2.contains(1));
  ASSERT_TRUE(multiset2.contains(2));
  ASSERT_TRUE(multiset2.contains(3));
}

TEST(S21multisetTest, ModifierMerge) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2 = {3, 4, 5};
  multiset1.merge(multiset2);
  EXPECT_EQ(multiset1.size(), 6U);
  EXPECT_EQ(multiset2.size(), 0U);
  ASSERT_TRUE(multiset1.contains(1));
  ASSERT_TRUE(multiset1.contains(2));
  ASSERT_TRUE(multiset1.contains(3));
  ASSERT_TRUE(multiset1.contains(4));
  ASSERT_TRUE(multiset1.contains(5));
}

TEST(S21multisetTest, LookupCount) {
  s21::multiset<int> multiset = {1, 2, 3, 2, 3, 7, 2};
  EXPECT_EQ(multiset.size(), 7U);
  EXPECT_EQ(multiset.count(2), 3U);
  EXPECT_EQ(multiset.count(3), 2U);
  EXPECT_EQ(multiset.count(10), 0U);
}

TEST(S21multisetTest, LookupEqualRange) {
  s21::multiset<int> multiset = {1, 2, 3, 3, 7};
  EXPECT_EQ(multiset.size(), 5U);
  auto range = multiset.equal_range(3);
  ASSERT_EQ(*range.first, 3);
  ASSERT_EQ(*range.second, 7);
  range = multiset.equal_range(7);
  ASSERT_EQ(*range.first, 7);
  ASSERT_EQ(range.second, multiset.end());
  range = multiset.equal_range(8);
  ASSERT_EQ(range.first, multiset.end());
  ASSERT_EQ(range.second, multiset.end());
}

TEST(S21multisetTest, LookupLowerBound) {
  s21::multiset<int> multiset = {1, 2, 3, 3, 7};
  EXPECT_EQ(multiset.size(), 5U);
  auto it = multiset.lower_bound(3);
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 7);
}

TEST(S21multisetTest, LookupUpperBound) {
  s21::multiset<int> multiset = {1, 7, 3, 3, 2};
  EXPECT_EQ(multiset.size(), 5U);
  auto it = multiset.upper_bound(3);
  ASSERT_EQ(*it, 7);
}

TEST(S21multisetTest, Insert_many) {
  s21::multiset<int> set;
  s21::multiset<int> res = {1, 2, 3, 3, 4, 4, 5, 5};

  set.insert_many(1, 2, 3, 3, 4, 4, 5, 5);
  auto it = set.begin();
  auto it2 = res.begin();

  for (; it != set.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(MapOperators, BracketOperator) {
  s21::map<int, std::string> map;
  map[1] = "one";
  map[2] = "two";
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
  map[1] = "uno";
  EXPECT_EQ(map[1], "uno");
}

TEST(map_constructor, case1) {
  s21::map<int, int> s21_map_int;
  s21::map<double, double> s21_map_double;
  s21::map<std::string, std::string> s21_map_string;

  EXPECT_EQ(s21_map_int.size(), 0U);
  EXPECT_EQ(s21_map_double.size(), 0U);
  EXPECT_EQ(s21_map_string.size(), 0U);
}

TEST(map_constructor, case2) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map = {pair1, pair2, pair3};

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_constructor, case3) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};

  s21::map<double, std::string> s21_map = {pair1, pair2, pair3};

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_constructor, case4) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3};

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_constructor, case5) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<int, double> s21_map_int{pair1};
  s21::map<double, std::string> s21_map_double{pair2};
  s21::map<std::string, int> s21_map_string{pair3};

  EXPECT_EQ(s21_map_int.size(), 1U);
  EXPECT_EQ(s21_map_double.size(), 1U);
  EXPECT_EQ(s21_map_string.size(), 1U);
}

TEST(map_constructor, case6) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref = {pair1, pair2, pair3};
  s21::map<int, double> s21_map_res(s21_map_ref);

  EXPECT_EQ(s21_map_res.size(), s21_map_ref.size());
}

TEST(map_constructor, case7) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};

  s21::map<double, std::string> s21_map_ref = {pair1, pair2, pair3};
  s21::map<double, std::string> s21_map_res(s21_map_ref);

  EXPECT_EQ(s21_map_res.size(), s21_map_ref.size());
}

TEST(map_constructor, case8) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<std::string, int> s21_map_ref = {pair1, pair2, pair3};
  s21::map<std::string, int> s21_map_res(s21_map_ref);

  EXPECT_EQ(s21_map_res.size(), s21_map_ref.size());
}

TEST(map_constructor, case9) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref = {pair1, pair2, pair3};
  s21::map<int, double> s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case10) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};

  s21::map<double, std::string> s21_map_ref = {pair1, pair2, pair3};
  s21::map<double, std::string> s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case11) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<std::string, int> s21_map_ref = {pair1, pair2, pair3};
  s21::map<std::string, int> s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case12) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref = {pair1, pair2, pair3};
  s21::map<int, double> s21_map_res;
  s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case13) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};

  s21::map<double, std::string> s21_map_ref = {pair1, pair2, pair3};

  s21::map<double, std::string> s21_map_res;
  s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case14) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<std::string, int> s21_map_ref = {pair1, pair2, pair3};

  s21::map<std::string, int> s21_map_res;
  s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case15) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref_int{pair1, pair2, pair3};
  s21::map<int, double> s21_map_res_int{s21_map_ref_int};

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_ref_double{pair4, pair5, pair6};
  s21::map<double, std::string> s21_map_res_double{s21_map_ref_double};

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_ref_string{pair7, pair8, pair9};
  s21::map<std::string, int> s21_map_res_string{s21_map_ref_string};

  auto it_res_int = s21_map_res_int.begin();
  for (auto it_ref_int = s21_map_ref_int.begin();
       it_ref_int != s21_map_ref_int.end(); ++it_ref_int) {
    EXPECT_EQ(it_res_int->first, it_ref_int->first);
    it_res_int++;
  }

  auto it_res_double = s21_map_res_double.begin();
  for (auto it_ref_double = s21_map_ref_double.begin();
       it_ref_double != s21_map_ref_double.end(); ++it_ref_double) {
    EXPECT_EQ(it_res_double->first, it_ref_double->first);
    it_res_double++;
  }

  auto it_res_string = s21_map_res_string.begin();
  for (auto it_ref_string = s21_map_ref_string.begin();
       it_ref_string != s21_map_ref_string.end(); ++it_ref_string) {
    EXPECT_EQ(it_res_string->first, it_ref_string->first);
    it_res_string++;
  }
}

TEST(map_insert, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{9, 1.4};
  std::pair<int, double> pair3{9, 1.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{98, 3.9};

  s21::map<int, double> s21_map;

  std::pair<s21::map<int, double>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->first, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert2 =
      s21_map.insert(pair2);
  std::pair<s21::map<int, double>::iterator, bool> insert3 =
      s21_map.insert(pair3);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  std::pair<s21::map<int, double>::iterator, bool> insert4 =
      s21_map.insert(pair4);
  EXPECT_EQ(insert4.first->first, 23);
  EXPECT_EQ(insert4.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert5 =
      s21_map.insert(pair5);
  EXPECT_EQ(insert5.first->first, 98);
  EXPECT_EQ(insert5.second, 1);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case2) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};
  std::pair<double, std::string> pair4{2.77, "hi"};
  std::pair<double, std::string> pair5{3.9, "hola"};

  s21::map<double, std::string> s21_map;

  std::pair<s21::map<double, std::string>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->first, 1.4);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<double, std::string>::iterator, bool> insert2 =
      s21_map.insert(pair2);
  EXPECT_EQ(insert2.first->first, 2.77);
  EXPECT_EQ(insert2.second, 1);

  std::pair<s21::map<double, std::string>::iterator, bool> insert3 =
      s21_map.insert(pair3);
  EXPECT_EQ(insert3.first->first, 3.9);
  EXPECT_EQ(insert3.second, 1);

  std::pair<s21::map<double, std::string>::iterator, bool> insert4 =
      s21_map.insert(pair4);
  std::pair<s21::map<double, std::string>::iterator, bool> insert5 =
      s21_map.insert(pair5);
  EXPECT_EQ(insert4.second, 0);
  EXPECT_EQ(insert5.second, 0);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case3) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hi", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello", 1};

  s21::map<std::string, int> s21_map;

  std::pair<s21::map<std::string, int>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->first, "hello");
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<std::string, int>::iterator, bool> insert2 =
      s21_map.insert(pair2);
  EXPECT_EQ(insert2.first->first, "hi");
  EXPECT_EQ(insert2.second, 1);

  std::pair<s21::map<std::string, int>::iterator, bool> insert3 =
      s21_map.insert(pair3);
  EXPECT_EQ(insert3.second, 0);

  std::pair<s21::map<std::string, int>::iterator, bool> insert4 =
      s21_map.insert(pair4);
  EXPECT_EQ(insert4.first->first, "hola");
  EXPECT_EQ(insert4.second, 1);

  std::pair<s21::map<std::string, int>::iterator, bool> insert5 =
      s21_map.insert(pair5);
  EXPECT_EQ(insert5.second, 0);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case4) {
  std::pair<int, double> pair1{9, 1.4};

  s21::map<int, double> s21_map;

  std::pair<s21::map<int, double>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->first, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert2 =
      s21_map.insert(pair1);
  std::pair<s21::map<int, double>::iterator, bool> insert3 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  EXPECT_EQ(s21_map.size(), 1U);
}

TEST(map_insert, case5) {
  std::pair<double, std::string> pair1{1.4, "hello"};

  s21::map<double, std::string> s21_map = {pair1};

  std::pair<s21::map<double, std::string>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.second, 0);

  EXPECT_EQ(s21_map.size(), 1U);
}

TEST(map_insert, case6) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};

  s21::map<std::string, int> s21_map = {pair1};

  std::pair<s21::map<std::string, int>::iterator, bool> insert1 =
      s21_map.insert(pair2);
  EXPECT_EQ(insert1.first->first, "hi");
  EXPECT_EQ(insert1.second, 1);

  EXPECT_EQ(s21_map.size(), 2U);
}

TEST(map_insert, case7) {
  s21::map<int, double> s21_map;

  std::pair<s21::map<int, double>::iterator, bool> insert1 =
      s21_map.insert(9, 1.4);
  EXPECT_EQ(insert1.first->first, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert2 =
      s21_map.insert(9, 1.4);
  std::pair<s21::map<int, double>::iterator, bool> insert3 =
      s21_map.insert(9, 1.4);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  std::pair<s21::map<int, double>::iterator, bool> insert4 =
      s21_map.insert(23, 2.77);
  EXPECT_EQ(insert4.first->first, 23);
  EXPECT_EQ(insert4.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert5 =
      s21_map.insert(98, 3.9);
  EXPECT_EQ(insert5.first->first, 98);
  EXPECT_EQ(insert5.second, 1);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case8) {
  s21::map<double, std::string> s21_map;

  std::pair<s21::map<double, std::string>::iterator, bool> insert1 =
      s21_map.insert(1.4, "hello");
  EXPECT_EQ(insert1.first->first, 1.4);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<double, std::string>::iterator, bool> insert2 =
      s21_map.insert(2.77, "hi");
  EXPECT_EQ(insert2.first->first, 2.77);
  EXPECT_EQ(insert2.second, 1);

  std::pair<s21::map<double, std::string>::iterator, bool> insert3 =
      s21_map.insert(3.9, "hola");
  EXPECT_EQ(insert3.first->first, 3.9);
  EXPECT_EQ(insert3.second, 1);

  std::pair<s21::map<double, std::string>::iterator, bool> insert4 =
      s21_map.insert(2.77, "hi");
  std::pair<s21::map<double, std::string>::iterator, bool> insert5 =
      s21_map.insert(3.9, "hola");
  EXPECT_EQ(insert4.second, 0);
  EXPECT_EQ(insert5.second, 0);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case9) {
  s21::map<std::string, int> s21_map;

  std::pair<s21::map<std::string, int>::iterator, bool> insert1 =
      s21_map.insert("hello", 1);
  EXPECT_EQ(insert1.first->first, "hello");
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<std::string, int>::iterator, bool> insert2 =
      s21_map.insert("hi", 2);
  EXPECT_EQ(insert2.first->first, "hi");
  EXPECT_EQ(insert2.second, 1);

  std::pair<s21::map<std::string, int>::iterator, bool> insert3 =
      s21_map.insert("hi", 2);
  EXPECT_EQ(insert3.second, 0);

  std::pair<s21::map<std::string, int>::iterator, bool> insert4 =
      s21_map.insert("hola", 3);
  EXPECT_EQ(insert4.first->first, "hola");
  EXPECT_EQ(insert4.second, 1);

  std::pair<s21::map<std::string, int>::iterator, bool> insert5 =
      s21_map.insert("hello", 1);
  EXPECT_EQ(insert5.second, 0);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case10) {
  s21::map<int, double> s21_map;

  std::pair<s21::map<int, double>::iterator, bool> insert1 =
      s21_map.insert(9, 1.4);
  EXPECT_EQ(insert1.first->first, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert2 =
      s21_map.insert(9, 1.4);
  std::pair<s21::map<int, double>::iterator, bool> insert3 =
      s21_map.insert(9, 1.4);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  EXPECT_EQ(s21_map.size(), 1U);
}

TEST(map_insert, case11) {
  std::pair<double, std::string> pair1{1.4, "hello"};

  s21::map<double, std::string> s21_map = {pair1};

  std::pair<s21::map<double, std::string>::iterator, bool> insert1 =
      s21_map.insert(1.4, "hello");
  EXPECT_EQ(insert1.second, 0);

  EXPECT_EQ(s21_map.size(), 1U);
}

TEST(map_insert, case12) {
  std::pair<std::string, int> pair1{"hello", 1};

  s21::map<std::string, int> s21_map = {pair1};

  std::pair<s21::map<std::string, int>::iterator, bool> insert1 =
      s21_map.insert("hi", 2);
  EXPECT_EQ(insert1.first->first, "hi");
  EXPECT_EQ(insert1.second, 1);

  EXPECT_EQ(s21_map.size(), 2U);
}

TEST(map_begin, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{15, 1.456};
  std::pair<int, double> pair3{7, 151.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{2, 3.9};

  s21::map<int, double> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->first, 2);
}

TEST(map_begin, case2) {
  std::pair<double, std::string> pair1{11.4, "hello"};
  std::pair<double, std::string> pair2{2.770001, "hee"};
  std::pair<double, std::string> pair3{3.901, "hola"};
  std::pair<double, std::string> pair4{2.77, "hi"};
  std::pair<double, std::string> pair5{3.9, "hee-hee"};

  s21::map<double, std::string> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->first, 2.77);
}

TEST(map_begin, case3) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hi-hi", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->first, "hello");
}

TEST(map_begin, case5) {
  std::pair<double, std::string> pair1{1.4, "hello"};

  s21::map<double, std::string> s21_map = {pair1, pair1};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->first, 1.4);
  EXPECT_EQ(min_value->second, "hello");
}

TEST(map_begin, case6) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hello", 2};
  std::pair<std::string, int> pair3{"hello", 45};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->first, "hello");
  EXPECT_EQ(min_value->second, 1);
}

TEST(map_end, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{15, 1.456};
  std::pair<int, double> pair3{7, 151.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{2, 3.9};

  s21::map<int, double> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto max_value = s21_map.end();
  max_value--;
  EXPECT_EQ(max_value->first, 23);
}

TEST(map_end, case2) {
  std::pair<double, std::string> pair1{11.4, "hello"};
  std::pair<double, std::string> pair2{2.770001, "hee"};
  std::pair<double, std::string> pair3{3.901, "hola"};
  std::pair<double, std::string> pair4{11.400000001, "hi"};
  std::pair<double, std::string> pair5{3.9, "hee-hee"};

  s21::map<double, std::string> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto max_value = --s21_map.end();

  EXPECT_EQ(max_value->first, 11.400000001);
}

TEST(map_end, case3) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola-hola", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};
  std::map<std::string, int> std_map = {pair1, pair2, pair3, pair4, pair5};
  auto max_value = --s21_map.end();
  auto max_value_std = --std_map.end();
  EXPECT_EQ(max_value->first, max_value_std->first);
}

TEST(map_end, case5) {
  std::pair<double, std::string> pair1{1.4, "hello"};

  s21::map<double, std::string> s21_map = {pair1, pair1};

  auto max_value = --s21_map.end();

  EXPECT_EQ(max_value->first, 1.4);
  EXPECT_EQ(max_value->second, "hello");
}

TEST(map_end, case6) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hello", 2};
  std::pair<std::string, int> pair3{"hello", 45};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3};

  auto max_value = --s21_map.end();

  EXPECT_EQ(max_value->first, "hello");
  EXPECT_EQ(max_value->second, 1);
}

TEST(map_balance, case1) {
  std::pair<int, double> pair1{1, 1.4};
  std::pair<int, double> pair2{15, 1.456};
  std::pair<int, double> pair3{5, 151.4};

  s21::map<int, double> s21_map = {pair1, pair2, pair3};

  auto max_value = --s21_map.end();

  EXPECT_EQ(max_value->first, 15);
  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_balance, case2) {
  std::pair<double, std::string> pair1{11.4, "hello"};
  std::pair<double, std::string> pair2{2.770001, "hi"};
  std::pair<double, std::string> pair3{3.901, "hola"};

  s21::map<double, std::string> s21_map = {pair1, pair2, pair3};

  auto min_value = --s21_map.end();

  EXPECT_EQ(min_value->first, 11.4);
  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_balance, case3) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola-hola", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto min_value = --s21_map.end();

  EXPECT_EQ(min_value->first, "hola-hola");
  EXPECT_EQ(s21_map.size(), 5U);
}

TEST(map_balance, case4) {
  std::pair<int, int> pair1{10, 10};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{20, 20};
  std::pair<int, int> pair4{30, 30};
  std::pair<int, int> pair5{1543, 1543};

  s21::map<int, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  EXPECT_EQ((--s21_map.end())->first, 1543);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.size(), 5U);
}

TEST(map_balance, case5) {
  std::pair<int, int> pair1{30, 30};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{43, 43};
  std::pair<int, int> pair4{1, 1};
  std::pair<int, int> pair5{20, 20};
  std::pair<int, int> pair6{40, 60};
  std::pair<int, int> pair7{60, 60};
  std::pair<int, int> pair8{35, 35};
  std::pair<int, int> pair9{32, 32};

  s21::map<int, int> s21_map = {pair1, pair2, pair3, pair4, pair5,
                                pair6, pair7, pair8, pair9};

  EXPECT_EQ((--s21_map.end())->first, 60);
  EXPECT_EQ(s21_map.begin()->first, 1);
  EXPECT_EQ(s21_map.size(), 9U);
}

TEST(map_erase, case2) {
  std::pair<int, int> pair1{30, 30};
  std::pair<int, int> pair2{1543, 1543};

  s21::map<int, int> s21_map = {pair1, pair2};

  auto it = s21_map.begin();
  it++;
  s21_map.erase(it);
  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(map_erase, case3) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola-hola", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = --s21_map.end();
  s21_map.erase(it);
  EXPECT_EQ((--s21_map.end())->first, "hola");
  EXPECT_EQ(s21_map.size(), 4U);

  it = --s21_map.end();
  s21_map.erase(it);
  EXPECT_EQ((--s21_map.end())->first, "hi");
  EXPECT_EQ(s21_map.size(), 3U);

  s21_map.insert(pair3);
  s21_map.insert(pair4);
  it = --s21_map.end();
  s21_map.erase(it);
  EXPECT_EQ((--s21_map.end())->first, "hola");
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(map_erase, case4) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{12.4457, 2};
  std::pair<double, int> pair3{56.84, 2};
  std::pair<double, int> pair4{941.44, 3};
  std::pair<double, int> pair5{44.48, 1};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = --s21_map.end();
  it--;
  s21_map.erase(it);
  it = --s21_map.end();
  EXPECT_EQ(it->first, 941.44);
  EXPECT_EQ(s21_map.size(), 4U);

  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ((--s21_map.end())->first, 44.48);
  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_erase, case5) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4};

  auto it = s21_map.begin();
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  EXPECT_EQ(it->first, 44.48);
  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_erase, case6) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{6.84, 2};
  std::pair<double, int> pair5{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(it->first, 44.48);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(map_erase, case7) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{12.4457, 2};
  std::pair<double, int> pair3{56.84, 2};
  std::pair<double, int> pair4{941.44, 3};
  std::pair<double, int> pair5{44.48, 1};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.begin();
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  EXPECT_EQ(it->first, 44.48);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(map_erase, case8) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4};

  auto it = s21_map.begin();
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  EXPECT_EQ(it->first, 22.2);
  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_erase, case9) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{32.45, 2};
  std::pair<double, int> pair5{65.12, 3};
  std::pair<double, int> pair6{66.32, 3};
  std::pair<double, int> pair7{40.54, 3};
  std::pair<double, int> pair8{6.4, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4,
                                   pair5, pair6, pair7, pair8};

  auto it = --s21_map.end();
  it--;
  it--;
  it--;
  it--;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(it->first, 40.54);
  EXPECT_EQ(s21_map.size(), 7U);
}

TEST(map_erase, case10) {
  std::pair<double, int> pair1{22.2, 1};

  s21::map<double, int> s21_map = {pair1};

  auto it = --s21_map.end();
  it--;
  ++it;
  s21_map.erase(it);
  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(map_empty, case1) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4};

  EXPECT_EQ(s21_map.empty(), 0);
}

TEST(map_empty, case2) {
  s21::map<double, int> s21_map;

  EXPECT_EQ(s21_map.empty(), 1);
}

TEST(map_swap, case1) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};
  std::pair<double, int> pair5{22.2, 15};

  s21::map<double, int> s21_map_ref = {pair1, pair2};
  s21::map<double, int> s21_map_res = {pair3, pair4, pair5};

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 3U);
  EXPECT_EQ(s21_map_ref.begin()->first, 1.44);

  EXPECT_EQ(s21_map_res.size(), 2U);
  EXPECT_EQ(s21_map_res.begin()->first, 22.2);
}

TEST(map_swap, case2) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};

  s21::map<double, int> s21_map_ref = {pair1, pair2};
  s21::map<double, int> s21_map_res;

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 0U);

  EXPECT_EQ(s21_map_res.size(), 2U);
  EXPECT_EQ(s21_map_res.begin()->first, 22.2);
}

TEST(map_swap, case3) {
  std::pair<double, int> pair1{12.4457, 2};
  std::pair<double, int> pair2{1.44, 3};
  std::pair<double, int> pair3{22.2, 15};

  s21::map<double, int> s21_map_ref;
  s21::map<double, int> s21_map_res = {pair1, pair2, pair3};

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 3U);
  EXPECT_EQ(s21_map_ref.begin()->first, 1.44);

  EXPECT_EQ(s21_map_res.size(), 0U);
}

TEST(map_swap, case4) {
  s21::map<double, int> s21_map_ref;
  s21::map<double, int> s21_map_res;

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 0U);
}

TEST(map_contains, case1) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};

  s21::map<double, int> s21_map = {pair1, pair2};

  EXPECT_EQ(s21_map.contains(22.2), true);
  EXPECT_EQ(s21_map.contains(44.48), true);
}

TEST(map_contains, case2) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};

  s21::map<double, int> s21_map_ref = {pair1, pair2};
  s21::map<double, int> s21_map_res;

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_ref.contains(22.2), false);
  EXPECT_EQ(s21_map_ref.contains(44.48), false);

  EXPECT_EQ(s21_map_res.size(), 2U);
  EXPECT_EQ(s21_map_res.contains(22.2), true);
  EXPECT_EQ(s21_map_res.contains(44.48), true);
}

TEST(map_contains, case3) {
  std::pair<double, int> pair1{12.4457, 2};
  std::pair<double, int> pair2{1.44, 3};
  std::pair<double, int> pair3{22.2, 15};

  s21::map<double, int> s21_map_ref;
  s21::map<double, int> s21_map_res = {pair1, pair2, pair3};

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 3U);
  EXPECT_EQ(s21_map_ref.contains(12.4457), true);
  EXPECT_EQ(s21_map_ref.contains(1.44), true);
  EXPECT_EQ(s21_map_ref.contains(22.2), true);

  EXPECT_EQ(s21_map_res.size(), 0U);
  EXPECT_EQ(s21_map_res.contains(12.4457), false);
  EXPECT_EQ(s21_map_res.contains(1.44), false);
  EXPECT_EQ(s21_map_res.contains(22.2), false);
}

TEST(map_contains, case4) {
  s21::map<double, int> s21_map;

  EXPECT_EQ(s21_map.size(), 0U);
  EXPECT_EQ(s21_map.contains(12.4457), false);
}

TEST(map_at, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 3.9};
  std::pair<int, double> pair22{88, 3.9};
  std::pair<int, double> pair33{108, 3.9};

  s21::map<int, double> s21_map_int{pair1,  pair2,  pair3,
                                    pair11, pair22, pair33};
  EXPECT_EQ(s21_map_int.at(9), 1.4);
  EXPECT_EQ(s21_map_int.at(23), 2.77);
  EXPECT_EQ(s21_map_int.at(98), 3.9);
  EXPECT_EQ(s21_map_int.at(78), 3.9);
  EXPECT_EQ(s21_map_int.at(88), 3.9);
  EXPECT_EQ(s21_map_int.at(108), 3.9);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_double{pair4, pair5, pair6};
  EXPECT_EQ(s21_map_double.at(1.4), "hello");
  EXPECT_EQ(s21_map_double.at(2.77), "hi");
  EXPECT_EQ(s21_map_double.at(3.9), "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_string{pair7, pair8, pair9};
  EXPECT_EQ(s21_map_string.at("hello"), 1);
  EXPECT_EQ(s21_map_string.at("hi"), 2);
  EXPECT_EQ(s21_map_string.at("hola"), 3);
}

TEST(map_brackets, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 3.9};
  std::pair<int, double> pair22{88, 3.9};
  std::pair<int, double> pair33{108, 3.9};

  s21::map<int, double> s21_map_int{pair1,  pair2,  pair3,
                                    pair11, pair22, pair33};
  EXPECT_EQ(s21_map_int[9], 1.4);
  EXPECT_EQ(s21_map_int[23], 2.77);
  EXPECT_EQ(s21_map_int[98], 3.9);
  EXPECT_EQ(s21_map_int[78], 3.9);
  EXPECT_EQ(s21_map_int[88], 3.9);
  EXPECT_EQ(s21_map_int[108], 3.9);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_double{pair4, pair5, pair6};
  EXPECT_EQ(s21_map_double[1.4], "hello");
  EXPECT_EQ(s21_map_double[2.77], "hi");
  EXPECT_EQ(s21_map_double[3.9], "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_string{pair7, pair8, pair9};
  EXPECT_EQ(s21_map_string["hello"], 1);
  EXPECT_EQ(s21_map_string["hi"], 2);
  EXPECT_EQ(s21_map_string["hola"], 3);
}

TEST(map_brackets, case2) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{8, 3.9};

  s21::map<int, double> s21_map_int = {pair1, pair2, pair3};
  s21_map_int[78] = 78.0;
  s21_map_int[88] = 88.0;
  s21_map_int[108] = 108.0;

  EXPECT_EQ(s21_map_int[9], 1.4);
  EXPECT_EQ(s21_map_int[23], 2.77);
  EXPECT_EQ(s21_map_int[8], 3.9);
  EXPECT_EQ(s21_map_int[78], 78.0);
  EXPECT_EQ(s21_map_int[88], 88.0);
  EXPECT_EQ(s21_map_int[108], 108.0);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_double{pair4, pair5};
  s21_map_double[3.9] = "hola";

  EXPECT_EQ(s21_map_double[1.4], "hello");
  EXPECT_EQ(s21_map_double[2.77], "hi");
  EXPECT_EQ(s21_map_double[3.9], "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_string{pair7};
  s21_map_string["hi"] = 2;
  s21_map_string["hola"] = 3;

  EXPECT_EQ(s21_map_string["hello"], 1);
  EXPECT_EQ(s21_map_string["hi"], 2);
  EXPECT_EQ(s21_map_string["hola"], 3);
}

TEST(map_merge, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 4.59};
  std::pair<int, double> pair22{88, 12.902};
  std::pair<int, double> pair33{108, 56.41};

  s21::map<int, double> s21_map_int_ref{pair1, pair2, pair3};
  s21::map<int, double> s21_map_int_res{pair11, pair22, pair33};

  s21_map_int_res.merge(s21_map_int_ref);

  EXPECT_EQ(s21_map_int_res.size(), 6U);
}

TEST(map_merge, case2) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_int_ref{pair1, pair2, pair3};
  s21::map<int, double> s21_map_int_res;

  s21_map_int_res.merge(s21_map_int_ref);

  EXPECT_EQ(s21_map_int_res.size(), 3U);
}

TEST(map_merge, case3) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_int_ref;
  s21::map<int, double> s21_map_int_res{pair1, pair2, pair3};

  EXPECT_EQ(s21_map_int_res.size(), 3U);
}

TEST(map_merge, case4) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair4{1, 22.2};
  std::pair<int, double> pair5{8, 44.48};
  std::pair<int, double> pair6{32, 12.4457};

  s21::map<int, double> s21_map_int_ref = {pair1, pair2, pair3, pair4};
  s21::map<int, double> s21_map_int_res = {pair5, pair6};

  s21_map_int_res.merge(s21_map_int_ref);

  EXPECT_EQ(s21_map_int_res.size(), 6U);
}

TEST(MapTest, BasicConstructor) {
  s21::map<int, int> test;
  EXPECT_EQ(test.empty(), true);
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, int> test1;
  test1.insert(1, 2);
  test1.insert(2, 3);
  test1.insert(3, 4);
  s21::map<int, int> test2(test1);
  EXPECT_EQ(test2.at(1), 2);
  EXPECT_EQ(test2.at(2), 3);
  EXPECT_EQ(test2.at(3), 4);
}

TEST(MapTest, MoveConstructor) {
  s21::map<int, int> test1({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  s21::map<int, int> test2(std::move(test1));
  EXPECT_EQ(test2.at(1), 2);
  EXPECT_EQ(test2.at(2), 3);
  EXPECT_EQ(test2.at(3), 4);
  EXPECT_EQ(test2.at(4), 5);
}

TEST(MapTest, ConstructorsList) {
  s21::map<int, std::string> new_map;

  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (my_iter != my_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(std_iter == std_map.end());

  s21::map<int, std::string> my_map2(my_map);
  std::map<int, std::string> std_map2(std_map);

  my_iter = my_map2.begin();
  std_iter = std_map2.begin();

  while (std_iter != std_map2.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map2.end());

  s21::map<int, std::string> my_map3 = std::move(my_map2);
  std::map<int, std::string> std_map3 = std::move(std_map2);

  my_iter = my_map3.begin();
  std_iter = std_map3.begin();

  while (std_iter != std_map3.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map3.end());

  s21::map<int, std::string> my_map4 = std::move(my_map2);
  std::map<int, std::string> std_map4 = std::move(std_map2);
}

TEST(MapTest, ConstructorsList2) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  EXPECT_EQ(test.empty(), false);
  EXPECT_EQ(test.at(1), 2);
  EXPECT_EQ(test.at(2), 3);
  EXPECT_EQ(test.at(3), 4);
  EXPECT_EQ(test.at(4), 5);
}

TEST(MapTest, At) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_ans = my_map.at(33);
  auto std_ans = std_map.at(33);
  ASSERT_TRUE(my_ans == std_ans);

  my_ans = my_map.at(3);
  std_ans = std_map.at(3);
  ASSERT_TRUE(my_ans == std_ans);
}

TEST(MapTest, AtOneValue) {
  s21::map<int, int> test;
  test.insert(1, 2);
  EXPECT_EQ(test.at(1), 2);
}

TEST(MapTest, AtManyValue) {
  s21::map<int, int> test;
  test.insert(1, 2);
  test.insert(2, 3);
  test.insert(3, 4);
  test.insert(-1, 5);
  EXPECT_EQ(test.at(3), 4);
}

TEST(MapTest, SquareBrackets) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_ans = my_map[33];
  auto std_ans = std_map[33];
  ASSERT_TRUE(my_ans == std_ans);

  my_ans = my_map[3];
  std_ans = std_map[3];
  ASSERT_TRUE(my_ans == std_ans);
}

TEST(MapTest, SquareBrackets1) {
  s21::map<int, int> test;
  test.insert(1, 2);
  EXPECT_EQ(test[1], 2);
}

TEST(MapTest, SquareBrackets2) {
  s21::map<int, int> test;
  test.insert(1, 2);
  test.insert(2, 3);
  test.insert(3, 4);
  test.insert(-1, 5);
  EXPECT_EQ(test[3], 4);
  test[4] = 5;
  test[5] = 6;
  EXPECT_EQ(test[5], 6);
}

TEST(MapTest, Empty) {
  s21::map<int, std::string> new_map;
  ASSERT_TRUE(new_map.empty() == true);

  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  ASSERT_TRUE(my_map.empty() == false);
}

TEST(MapTest, Size) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  ASSERT_EQ(my_map.size(), std_map.size());
}

TEST(MapTest, Clear) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  ASSERT_EQ(my_map.size(), std_map.size());
}

TEST(MapTest, Insert1) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert(1, "one");
  std_map.insert({1, "one"});
  my_map.insert(2, "two");
  std_map.insert({2, "two"});
  my_map.insert(22, "twotwo");
  std_map.insert({22, "twotwo"});
  my_map.insert(-22, "-twotwo");
  std_map.insert({-22, "-twotwo"});
  my_map.insert(22, "three");
  std_map.insert({22, "three"});
  my_map.insert(22234, "two3two");
  std_map.insert({22234, "two3two"});
  my_map.insert(12, "onetwo");
  std_map.insert({12, "onetwo"});
  my_map.insert(-12, "-onetwo");
  std_map.insert({-12, "-onetwo"});
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(MapTest, Insert2) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert({1, "one"});
  std_map.insert({1, "one"});
  my_map.insert({2, "two"});
  std_map.insert({2, "two"});
  my_map.insert({22, "twotwo"});
  std_map.insert({22, "twotwo"});
  my_map.insert({-22, "-twotwo"});
  std_map.insert({-22, "-twotwo"});
  my_map.insert({22, "three"});
  std_map.insert({22, "three"});
  my_map.insert({22234, "two3two"});
  std_map.insert({22234, "two3two"});
  my_map.insert({12, "onetwo"});
  std_map.insert({12, "onetwo"});
  my_map.insert({-12, "-onetwo"});
  std_map.insert({-12, "-onetwo"});
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(MapTest, Erase) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  test.erase(test.begin());
  EXPECT_EQ(test.contains(1), false);
}

TEST(MapTest, Erase1) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(MapTest, Erase2) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  ++my_iter;
  ++std_iter;

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(MapTest, Erase3) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  ++my_iter;
  ++std_iter;
  ++my_iter;
  ++std_iter;

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(MapTest, Swap) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  s21::map<int, std::string> my_map2{
      std::make_pair(-42, "fodasfo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};
  std::map<int, std::string> std_map2{
      std::make_pair(-42, "fodasfo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};

  my_map.swap(my_map2);
  std_map.swap(std_map2);

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());

  my_iter = my_map2.begin();
  std_iter = std_map2.begin();

  while (std_iter != std_map2.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map2.end());
}

TEST(MapTest, Merge) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  s21::map<int, std::string> my_map2{
      std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};
  std::map<int, std::string> std_map2{
      std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};

  my_map.merge(my_map2);
  std_map.merge(std_map2);

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(MapTest, Merge1) {
  s21::map<int, int> test1({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  s21::map<int, int> test2({{5, 6}, {6, 7}});
  test1.merge(test2);
  EXPECT_EQ(test1.size(), 6U);
  EXPECT_EQ(test1[1], 2);
  EXPECT_EQ(test1[5], 6);
  EXPECT_EQ(test1[6], 7);
}

TEST(MapTest, InsertAsign) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert_or_assign(1, "one");
  std_map.insert_or_assign(1, "one");
  my_map.insert_or_assign(2, "two");
  std_map.insert_or_assign(2, "two");
  my_map.insert_or_assign(22, "twotwo");
  std_map.insert_or_assign(22, "twotwo");
  my_map.insert_or_assign(-22, "-twotwo");
  std_map.insert_or_assign(-22, "-twotwo");
  my_map.insert_or_assign(22, "three");
  std_map.insert_or_assign(22, "three");
  my_map.insert_or_assign(22234, "two3two");
  std_map.insert_or_assign(22234, "two3two");
  my_map.insert_or_assign(12, "onetwo");
  std_map.insert_or_assign(12, "onetwo");
  my_map.insert_or_assign(-12, "-onetwo");
  std_map.insert_or_assign(-12, "-onetwo");

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(MapTest, Contains) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  ASSERT_EQ(my_map.contains(42), true);
  ASSERT_EQ(my_map.contains(42342), false);
  ASSERT_EQ(my_map.contains(33), true);
  ASSERT_EQ(my_map.contains(0), false);
}

TEST(map, ConstructorDefaultMap) {
  s21::map<int, char> my_empty_map;
  std::map<int, char> orig_empty_map;
  EXPECT_EQ(my_empty_map.empty(), orig_empty_map.empty());
}

TEST(map, ConstructorInitializerMap) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorInitializer2Map) {
  s21::map<int, char> my_map = {};
  std::map<int, char> orig_map = {};
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorCopyMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = my_map;
  std::map<int, int> orig_map_copy = orig_map;
  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorMoveMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = std::move(my_map);
  std::map<int, int> orig_map_copy = std::move(orig_map);
  EXPECT_EQ(my_map.size(), orig_map.size());
  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, MapOperator) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  my_map['a'] = "Alisa";
  orig_map['a'] = "Alisa";
  orig_map['b'] = "Ben";
  EXPECT_TRUE(my_map['a'] == orig_map['a']);
  EXPECT_FALSE(my_map['b'] == orig_map['b']);
  EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST(map, MapAtOperatorException) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  EXPECT_THROW(my_map.at('g') = "Alisa", std::out_of_range);
}

TEST(map, MapAtOperator) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  my_map.at('a') = "Alisa";
  orig_map.at('a') = "Alisa";
  orig_map.at('b') = "Ben";
  EXPECT_TRUE(my_map['a'] == orig_map['a']);
  EXPECT_FALSE(my_map['b'] == orig_map['b']);
  EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST(map, MapCapacity) {
  s21::map<char, std::string> my_map;
  std::map<char, std::string> orig_map;
  EXPECT_TRUE(my_map.empty() == orig_map.empty());
  my_map.insert('z', "wow");
  EXPECT_FALSE(my_map.empty() == orig_map.empty());
  EXPECT_EQ(my_map.size(), 1U);
}

TEST(map, MapClear) {
  s21::map<int, int> my_map;
  std::map<int, int> orig_map;
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.insert(std::make_pair(1, 1));
  orig_map.insert(std::make_pair(1, 1));
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
}

TEST(map, MapInsert1) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(std::make_pair(1, 'a'));
  my_map.insert(std::make_pair(2, 'a'));
  my_map.insert(std::make_pair(3, 'a'));
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert(std::make_pair(1, 'a'));
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert2) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert(1, 'a');
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert3) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert_or_assign(1, 'b');
  auto i = orig_map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(map, MapErase) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  my_map.erase(my_map.begin());
  orig_map.erase(orig_map.begin());
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, SwapMap) {
  s21::map<int, int> my_map = {{1, 1}};
  s21::map<int, int> my_swap_map = {{3, 3}, {4, 4}};

  my_map.swap(my_swap_map);
  EXPECT_EQ(my_map.size(), 2U);
  EXPECT_EQ(my_swap_map.size(), 1U);
  auto x = (*(my_map.begin())).first;
  auto y = (*(my_swap_map.begin())).first;
  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}

TEST(map, MergeMap) {
  s21::map<int, int> my_map = {{1, 1}, {4, 4}, {2, 2}};
  s21::map<int, int> my_map_merge = {{3, 3}, {4, 4}};

  std::map<int, int> orig_map = {{1, 1}, {4, 4}, {2, 2}};
  std::map<int, int> orig_map_merge = {{3, 3}, {4, 4}};

  my_map.merge(my_map_merge);
  orig_map.merge(orig_map_merge);

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
  EXPECT_EQ(my_map_merge.contains(4), false);
  EXPECT_EQ(my_map_merge.contains(3), false);
}

TEST(map, ConstMap) {
  const s21::map<int, int> my_map = {{1, 1}, {4, 4}, {2, 2}};
  const std::map<int, int> orig_map = {{1, 1}, {4, 4}, {2, 2}};
  auto it = my_map.begin();
  auto it_std = orig_map.begin();
  for (; it != my_map.end(); ++it, ++it_std) {
    EXPECT_EQ((*it).first, (*it_std).first);
    EXPECT_EQ((*it).second, (*it_std).second);
  }
}

TEST(map, insert_many) {
  s21::map<int, int> my_map = {{1, 1}, {4, 4}, {2, 2}};
  const std::map<int, int> orig_map = {{1, 1}, {4, 4}, {2, 2},
                                       {3, 3}, {5, 5}, {6, 6}};

  my_map.insert_many(std::pair(3, 3), std::pair(5, 5), std::pair(6, 6));
  auto it = my_map.begin();
  auto it_std = orig_map.begin();
  for (; it != my_map.end(); ++it, ++it_std) {
    EXPECT_EQ((*it).first, (*it_std).first);
    EXPECT_EQ((*it).second, (*it_std).second);
  }
}

TEST(MapOperators, AtOperator) {
  s21::map<int, std::string> map;
  map[1] = "one";
  map[2] = "two";
  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(2), "two");
  map.at(1) = "uno";
  EXPECT_EQ(map.at(1), "uno");
  EXPECT_THROW(map.at(3), std::out_of_range);
}

TEST(MapOperators, BracketOperatorDefaultConstruct) {
  s21::map<int, std::string> map;
  EXPECT_EQ(map[5], "");
  size_t n = 1;
  EXPECT_EQ(map.size(), n);
  EXPECT_EQ(map[5], "");
}

TEST(MapTest, OperatorAccess) {
  s21::map<int, std::string> map;
  map.insert(10, "ten");
  map.insert(20, "twenty");

  EXPECT_EQ(map[10], "ten");
  EXPECT_EQ(map[20], "twenty");

  map[15] = "fifteen";
  EXPECT_EQ(map[15], "fifteen");

  auto it = map.end();
  --it;
  EXPECT_EQ((*it).first, 20);
}

TEST(MapTest, TraverseEndToBegin) {
  s21::map<int, std::string> map;
  map.insert(10, "ten");
  map.insert(20, "twenty");
  map.insert(5, "five");

  auto it = map.end();

  --it;
  EXPECT_EQ((*it).first, 20);

  --it;
  EXPECT_EQ((*it).first, 10);
  --it;
  EXPECT_EQ((*it).first, 5);

  auto min_it = map.begin();
  EXPECT_EQ((*it).first, (*min_it).first);
}

TEST(MapTest, BeginEndEmptyMap) {
  s21::map<int, std::string> map;

  auto it = map.begin();
  auto end_it = map.end();

  EXPECT_EQ(it, end_it);
}

TEST(MapTest, EndPosition) {
  s21::map<int, std::string> map;
  map.insert(10, "ten");
  map.insert(20, "twenty");
  map.insert(30, "thirty");

  auto it = map.end();
  auto min_it = map.begin();

  --it;
  EXPECT_EQ((*it).first, 30);
  EXPECT_EQ((*it).second, "thirty");

  --it;
  EXPECT_EQ((*it).first, 20);
  EXPECT_EQ((*it).second, "twenty");

  --it;
  EXPECT_EQ((*it).first, 10);
  EXPECT_EQ((*it).second, "ten");

  EXPECT_EQ((*it).first, (*min_it).first);
  EXPECT_EQ((*it).second, (*min_it).second);
}

TEST(MapMergeTest, MergeDisjointMaps) {
  s21::map<int, std::string> map1;
  map1.insert(10, "ten");
  map1.insert(20, "twenty");

  s21::map<int, std::string> map2;
  map2.insert(30, "thirty");
  map2.insert(40, "forty");

  map1.merge(map2);
  size_t n = 4;
  EXPECT_EQ(map1.size(), n);
  n = 0;
  EXPECT_EQ(map2.size(), n);
  EXPECT_EQ(map1.at(10), "ten");
  EXPECT_EQ(map1.at(20), "twenty");
  EXPECT_EQ(map1.at(30), "thirty");
  EXPECT_EQ(map1.at(40), "forty");
}

TEST(MapMergeTest, MergeOverlappingMaps) {
  s21::map<int, std::string> map1;
  map1.insert(10, "ten");
  map1.insert(20, "twenty");

  s21::map<int, std::string> map2;
  map2.insert(20, "twenty_new");
  map2.insert(30, "thirty");

  map1.merge(map2);

  size_t n = 3;
  EXPECT_EQ(map1.size(), n);
  n = 0;
  EXPECT_EQ(map2.size(), n);
  EXPECT_EQ(map1.at(10), "ten");
  EXPECT_EQ(map1.at(20), "twenty");
  EXPECT_EQ(map1.at(30), "thirty");
}

TEST(MapMergeTest, MergeWithEmptyMap) {
  s21::map<int, std::string> map1;
  map1.insert(10, "ten");
  map1.insert(20, "twenty");

  s21::map<int, std::string> map2;

  map1.merge(map2);

  size_t n = 2;
  EXPECT_EQ(map1.size(), n);
  n = 0;
  EXPECT_EQ(map2.size(), n);
  EXPECT_EQ(map1.at(10), "ten");
  EXPECT_EQ(map1.at(20), "twenty");

  map2.merge(map1);

  n = 2;
  EXPECT_EQ(map2.size(), n);
  n = 0;
  EXPECT_EQ(map1.size(), n);
  EXPECT_EQ(map2.at(10), "ten");
  EXPECT_EQ(map2.at(20), "twenty");
}

TEST(MapMergeTest, MergeIdenticalMaps) {
  s21::map<int, std::string> map1;
  map1.insert(10, "ten");
  map1.insert(20, "twenty");

  s21::map<int, std::string> map2;
  map2.insert(10, "ten");
  map2.insert(20, "twenty");

  map1.merge(map2);

  size_t n = 2;
  EXPECT_EQ(map1.size(), n);
  n = 0;
  EXPECT_EQ(map2.size(), n);
  EXPECT_EQ(map1.at(10), "ten");
  EXPECT_EQ(map1.at(20), "twenty");
}

TEST(set, ConstructorDefaultSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(set, ConstructorInitializerSet) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorInitializer2Set) {
  s21::set<char> my_set = {};
  std::set<char> orig_set = {};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorCopySet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = my_set;
  std::set<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorMoveSet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = std::move(my_set);
  std::set<int> orig_set_copy = std::move(orig_set);
  EXPECT_EQ(my_set.size(), orig_set.size());
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SetIteratorsSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, CapacitySet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, ClearSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, InsertSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_pr = my_set.insert("best");
  auto orig_pr = orig_set.insert("best");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert("is");
  orig_pr = orig_set.insert("is");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST(set, EraseSet) {
  s21::set<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set = {5, 4, 3, 2, 7, 8, 9};
  auto size = my_set.size();
  my_set.erase(my_set.end());
  auto new_size = my_set.size();
  EXPECT_EQ(size, new_size);
  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SwapSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3U);
  EXPECT_EQ(my_swap_set.size(), 1U);
  EXPECT_EQ(*my_set.begin(), 3);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(set, MergeSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(set, FindSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, ContainsSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<int> test;
  for (int i = 0; i < 20; ++i) {
    test.insert(i);
  }
  EXPECT_EQ(my_set.contains(2), orig_set.contains(2));
  EXPECT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}

TEST(Group_exmple, example1) { ASSERT_TRUE(1 == 1); }

TEST(S21setTest, DefaultConstructor) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  ASSERT_EQ(0U, set.size());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, InitializerListConstructor) {
  s21::set<int> s1({1, 2, 3});
  ASSERT_FALSE(s1.empty());
  ASSERT_EQ(3U, s1.size());
}

TEST(S21setTest, CopyConstructor) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> copy(set);
  ASSERT_FALSE(set.empty());
  ASSERT_FALSE(copy.empty());
  ASSERT_EQ(set.size(), copy.size());
}

TEST(S21setTest, MoveConstructor) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> move(std::move(set));
  ASSERT_TRUE(set.empty());
  ASSERT_FALSE(move.empty());
  ASSERT_EQ(3U, move.size());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, AssignmentOperator1) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2;
  set2 = set1;
  ASSERT_FALSE(set1.empty());
  ASSERT_FALSE(set2.empty());
  ASSERT_EQ(set1.size(), set2.size());
}

TEST(S21setTest, AssignmentOperator2) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2;
  set2 = std::move(set1);
  ASSERT_TRUE(set1.empty());
  ASSERT_FALSE(set2.empty());
  ASSERT_EQ(3U, set2.size());
}

TEST(S21setTest, IteratorBegin) {
  s21::set<int> set({1, 2, 3});
  s21::set<int>::iterator iterat;
  iterat = set.begin();
  s21::set<int>::iterator itFind;
  itFind = set.find(1);
  ASSERT_TRUE(iterat == itFind);
  ASSERT_EQ(itFind, iterat);
}

TEST(S21setTest, CapacityEmpty) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> empty;
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(empty.empty());
}

TEST(S21setTest, CapacitySize) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> empty;
  EXPECT_EQ(set.size(), 3U);
  EXPECT_EQ(empty.size(), 0U);
}

TEST(S21setTest, ModifierClear) {
  s21::set<int> set({1, 2, 3});
  ASSERT_FALSE(set.empty());
  set.clear();
  ASSERT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, ModifierInsert1) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(1);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(5));
}

TEST(S21setTest, ModifierInsert2) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(10);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(10));
}

TEST(S21setTest, ModifierErase) {
  s21::set<int> set = {1, 2, 3};
  EXPECT_EQ(set.size(), 3U);
  auto it = set.find(2);
  set.erase(it);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.contains(2));
}

TEST(S21setTest, ModifierSwap) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};
  set1.swap(set2);
  EXPECT_EQ(set1.size(), 3U);
  EXPECT_EQ(set2.size(), 3U);
  ASSERT_TRUE(set1.contains(4));
  ASSERT_TRUE(set1.contains(5));
  ASSERT_TRUE(set1.contains(6));
  ASSERT_TRUE(set2.contains(1));
  ASSERT_TRUE(set2.contains(2));
  ASSERT_TRUE(set2.contains(3));
}

TEST(S21setTest, ModifierMerge) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {3, 4, 5};
  set1.merge(set2);
  EXPECT_EQ(set1.size(), 5U);
  EXPECT_EQ(set2.size(), 0U);
  ASSERT_TRUE(set1.contains(1));
  ASSERT_TRUE(set1.contains(2));
  ASSERT_TRUE(set1.contains(3));
  ASSERT_TRUE(set1.contains(4));
  ASSERT_TRUE(set1.contains(5));
}

TEST(S21setTest, ModifierErase1) {
  s21::set<int> set;
  for (int i = 0; i < 100; ++i) {
    set.insert(i);
  }
  for (size_t i = 0U; i < 100U; ++i) {
    auto it = set.find(99 - i);
    set.erase(it);
    EXPECT_EQ(set.size(), 99 - i);
  }
}

TEST(S21setTest, ModifierConst) {
  const s21::set<int> set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const std::set<int> set_std = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::set<int>::const_iterator it1 = set.begin();
  s21::set<int>::const_iterator it;
  it = it1;
  auto it2 = set_std.begin();
  for (; it != set.end(); it++, it2++) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(S21setTest, ModifierConst1) {
  const s21::set<int> set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const std::set<int> set_std = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::set<int>::const_iterator it1 = set.end();
  s21::set<int>::const_iterator it = it1;
  it = --it1;
  auto it2 = set_std.end();
  --it2;
  for (; it != set.begin(); it--, it2--) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(set_constructor, case1) {
  s21::set<int> s21_set_int;
  s21::set<double> s21_set_double;
  s21::set<std::string> s21_set_string;

  EXPECT_EQ(s21_set_int.size(), 0U);
  EXPECT_EQ(s21_set_double.size(), 0U);
  EXPECT_EQ(s21_set_string.size(), 0U);
}

TEST(set_constructor, case2) {
  s21::set<int> s21_set_int{1, 2, 3, 4, 5};
  s21::set<double> s21_set_double{1.30359, 2847.4925, 923.39281};
  s21::set<std::string> s21_set_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_set_int.size(), 5U);
  EXPECT_EQ(s21_set_double.size(), 3U);
  EXPECT_EQ(s21_set_string.size(), 4U);
}

TEST(set_constructor, case3) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int{s21_set_ref_int};

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double{s21_set_ref_double};

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string{s21_set_ref_string};

  EXPECT_EQ(s21_set_ref_int.size(), s21_set_res_int.size());
  EXPECT_EQ(s21_set_ref_double.size(), s21_set_res_double.size());
  EXPECT_EQ(s21_set_ref_string.size(), s21_set_res_string.size());
}

TEST(set_constructor, case4) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}

TEST(set_constructor, case5) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int;
  s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double;
  s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string;
  s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}

TEST(set_constructor, case7) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4};
  s21::set<int> s21_set_res_int{s21_set_ref_int};

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281, 1.23};
  s21::set<double> s21_set_res_double{s21_set_ref_double};

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string{s21_set_ref_string};

  auto it_res_int = s21_set_res_int.begin();
  for (auto it_ref_int = s21_set_ref_int.begin();
       it_ref_int != s21_set_ref_int.end(); ++it_ref_int) {
    EXPECT_EQ(*it_res_int, *it_ref_int);
    it_res_int++;
  }

  auto it_res_double = s21_set_res_double.begin();
  for (auto it_ref_double = s21_set_ref_double.begin();
       it_ref_double != s21_set_ref_double.end(); ++it_ref_double) {
    EXPECT_EQ(*it_res_double, *it_ref_double);
    it_res_double++;
  }

  auto it_res_string = s21_set_res_string.begin();
  for (auto it_ref_string = s21_set_ref_string.begin();
       it_ref_string != s21_set_ref_string.end(); ++it_ref_string) {
    EXPECT_EQ(*it_res_string, *it_ref_string);
    it_res_string++;
  }
}

TEST(set_insert, case1) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<int>::iterator, bool> insert4 = s21_set.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<int>::iterator, bool> insert5 = s21_set.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, true);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case2) {
  s21::set<double> s21_set;

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(*insert1.first, 1.4);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<double>::iterator, bool> insert2 = s21_set.insert(2.77);
  EXPECT_EQ(*insert2.first, 2.77);
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<double>::iterator, bool> insert3 = s21_set.insert(3.9);
  EXPECT_EQ(*insert3.first, 3.9);
  EXPECT_EQ(insert3.second, true);

  std::pair<s21::set<double>::iterator, bool> insert4 = s21_set.insert(2.77);
  std::pair<s21::set<double>::iterator, bool> insert5 = s21_set.insert(3.9);
  EXPECT_EQ(insert4.second, false);
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case3) {
  s21::set<std::string> s21_set;

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hello");
  EXPECT_EQ(*insert1.first, "hello");
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert2 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert2.first, "hi");
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert3 =
      s21_set.insert("hi");
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<std::string>::iterator, bool> insert4 =
      s21_set.insert("hola");
  EXPECT_EQ(*insert4.first, "hola");
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert5 =
      s21_set.insert("hello");
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case4) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, false);
  EXPECT_EQ(insert3.second, false);

  EXPECT_EQ(s21_set.size(), 1U);
}

TEST(set_insert, case5) {
  s21::set<double> s21_set = {21};

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set_insert, case6) {
  s21::set<std::string> s21_set = {"hello"};

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert1.first, "hi");
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set_begin, case1) {
  s21::set<int> s21_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*s21_set.begin(), 2);
}

TEST(set_begin, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901, 2.77, 3.9};

  EXPECT_EQ(*s21_set.begin(), 2.77);
}

TEST(set_begin, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hi-hi", "hola",
                                   "hello, there"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set_begin, case5) {
  s21::set<double> s21_set = {1.4, 1.4};

  EXPECT_EQ(*s21_set.begin(), 1.4);
}

TEST(set_begin, case6) {
  s21::set<std::string> s21_set = {"hello", "hello", "hello"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set_end, case1) {
  s21::set<int> s21_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*(--s21_set.end()), 23);
}

TEST(set_end, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901, 11.400000001, 3.9};

  EXPECT_EQ(*(--s21_set.end()), 11.400000001);
}

TEST(set_end, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  EXPECT_EQ(*(--s21_set.end()), "hola-hola");
}

TEST(set_end, case5) {
  s21::set<double> s21_set = {1.4, 1.4};

  EXPECT_EQ(*(--s21_set.end()), 1.4);
}

TEST(set_end, case6) {
  s21::set<std::string> s21_set = {"hello", "hello", "hello"};

  EXPECT_EQ(*(--s21_set.end()), "hello");
}

TEST(set_balance, case1) {
  s21::set<int> s21_set = {1, 15, 5};

  EXPECT_EQ(*(--s21_set.end()), 15);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_balance, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901};

  EXPECT_EQ(*(--s21_set.end()), 11.4);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_balance, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  EXPECT_EQ(*(--s21_set.end()), "hola-hola");
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set_balance, case4) {
  s21::set<int> s21_set = {10, 5, 20, 30, 1543};

  EXPECT_EQ(*(--s21_set.end()), 1543);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set_balance, case5) {
  s21::set<int> s21_set = {30, 5, 43, 1, 20, 40, 60, 35, 32};

  EXPECT_EQ(*(--s21_set.end()), 60);
  EXPECT_EQ(*s21_set.begin(), 1);
  EXPECT_EQ(s21_set.size(), 9U);
}

TEST(set_erase, case2) {
  s21::set<int> s21_set = {30, 1543};

  auto it = s21_set.begin();
  it++;
  s21_set.erase(it);
  it = s21_set.begin();
  s21_set.erase(it);

  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_erase, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  auto it = (--s21_set.end());
  s21_set.erase(it);
  EXPECT_EQ(*(--s21_set.end()), "hola");
  EXPECT_EQ(s21_set.size(), 4U);

  it = (--s21_set.end());
  s21_set.erase(it);
  EXPECT_EQ(*(--s21_set.end()), "hi");
  EXPECT_EQ(s21_set.size(), 3U);

  s21_set.insert("hola-hola");
  s21_set.insert("hola");
  it = (--s21_set.end());
  s21_set.erase(it);
  EXPECT_EQ(*(--s21_set.end()), "hola");
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case4) {
  s21::set<double> s21_set = {22.2, 12.4457, 56.84, 941.44, 44.48};

  auto it = (--s21_set.end());
  it--;
  s21_set.erase(it);
  it = (--s21_set.end());
  EXPECT_EQ(*it, 941.44);
  EXPECT_EQ(s21_set.size(), 4U);

  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*(--s21_set.end()), 44.48);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case5) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  auto it = s21_set.begin();
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case6) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 6.84, 1.44};

  auto it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  it++;
  it++;
  it++;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case7) {
  s21::set<double> s21_set = {22.2, 12.4457, 56.84, 941.44, 44.48};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case8) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  EXPECT_EQ(*it, 22.2);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case9) {
  s21::set<double> s21_set = {22.2,  44.48, 12.4457, 32.45,
                              65.12, 66.32, 40.54,   6.4};

  auto it = (--s21_set.end());
  it--;
  it--;
  it--;
  it--;
  it--;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 40.54);
  EXPECT_EQ(s21_set.size(), 7U);
}

TEST(set_erase, case10) {
  s21::set<double> s21_set = {22.2};

  auto it = (--s21_set.end());
  it--;
  ++it;
  s21_set.erase(it);
  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_empty, case1) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(s21_set.empty(), 0);
}

TEST(set_empty, case2) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.empty(), 1);
}

TEST(set_MaxSize, case1) {
  s21::set<double> s21_set;
  std::set<double> std_set;

  EXPECT_EQ(s21_set.max_size(), std_set.max_size());
}

TEST(set_MaxSize, case2) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  std::set<double> std_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(s21_set.max_size(), std_set.max_size());
}

TEST(set_swap, case1) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set_swap, case2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set_swap, case3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 0U);
}

TEST(set_swap, case4) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_res.size(), 0U);
}

TEST(set_contains, case1) {
  s21::set<double> s21_set = {22.2, 44.48};

  EXPECT_EQ(s21_set.contains(22.2), true);
  EXPECT_EQ(s21_set.contains(44.48), true);
}

TEST(set_contains, case2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_ref.contains(22.2), false);
  EXPECT_EQ(s21_set_ref.contains(44.48), false);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(s21_set_res.contains(22.2), true);
  EXPECT_EQ(s21_set_res.contains(44.48), true);
}

TEST(set_contains, case3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(s21_set_ref.contains(12.4457), true);
  EXPECT_EQ(s21_set_ref.contains(1.44), true);
  EXPECT_EQ(s21_set_ref.contains(22.2), true);

  EXPECT_EQ(s21_set_res.size(), 0U);
  EXPECT_EQ(s21_set_res.contains(12.4457), false);
  EXPECT_EQ(s21_set_res.contains(1.44), false);
  EXPECT_EQ(s21_set_res.contains(22.2), false);
}

TEST(set_contains, case4) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.size(), 0U);
  EXPECT_EQ(s21_set.contains(12.4457), false);
}

TEST(set_find, case2) {
  s21::set<double> s21_set = {12.4457, 1.44, 22.2};

  auto it = s21_set.begin();
  ++it;
  EXPECT_EQ(*s21_set.find(12.4457), *it);

  it--;
  EXPECT_EQ(*s21_set.find(1.44), *it);

  it++;
  it++;
  EXPECT_EQ(*s21_set.find(22.2), *it);
}

TEST(S21setTest, ConstSet) {
  const s21::set<int> set({1, 2, 3});
  const std::set<int> orig({1, 2, 3});

  auto it = set.begin();
  auto it_orig = orig.begin();

  for (; it != set.end(); ++it, ++it_orig) {
    EXPECT_EQ(*it, *it_orig);
  }
}

TEST(S21setTest, ConstSetEmpty) {
  const s21::set<int> set;
  const std::set<int> orig;

  auto it = set.begin();
  auto it_orig = orig.begin();

  for (; it != set.end(); ++it, ++it_orig) {
    EXPECT_EQ(*it, *it_orig);
  }
}

TEST(S21setTest, Insert_many) {
  s21::set<int> set;
  s21::set<int> res = {1, 2, 3};

  set.insert_many(3, 2, 1);
  auto it = set.begin();
  auto it2 = res.begin();

  for (; it != set.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(setEraseTest, EraseLeafNode) {
  s21::set<int> set;
  set.insert(10);
  set.insert(5);
  set.insert(15);

  auto it = set.find(5);
  set.erase(it);

  size_t n = 2;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(5), set.end());
}

TEST(setEraseTest, EraseNodeWithOneChild) {
  s21::set<int> set;
  set.insert(10);
  set.insert(5);
  set.insert(1);

  auto it = set.find(5);
  set.erase(it);

  size_t n = 2;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(5), set.end());
  ASSERT_NE(set.find(1), set.end());
}

TEST(setEraseTest, EraseNodeWithTwoChildren) {
  s21::set<int> set;
  set.insert(10);
  set.insert(5);
  set.insert(15);
  set.insert(12);
  set.insert(18);

  auto it = set.find(15);
  set.erase(it);

  size_t n = 4;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(15), set.end());
  ASSERT_NE(set.find(12), set.end());
}

TEST(setEraseTest, EraseRootNode) {
  s21::set<int> set;
  set.insert(10);

  auto it = set.find(10);
  set.erase(it);

  size_t n = 0;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(10), set.end());
}

TEST(setEraseTest1, EraseRootNode) {
  s21::set<int> set;

  auto it = set.begin();
  set.erase(it);

  size_t n = 0;
  ASSERT_EQ(set.size(), n);
}

TEST(setEraseTest2, EraseRootNode) {
  s21::set<int> set;
  set.insert(5);
  set.insert(10);

  auto it = set.begin();
  set.erase(it);

  size_t n = 1;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(5), set.end());
}

TEST(setEraseTest3, EraseRootNode) {
  s21::set<int> set;
  set.insert(10);
  set.insert(5);

  auto it = set.find(10);
  set.erase(it);

  size_t n = 1;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(10), set.end());
}

TEST(setEraseTest4, EraseNodeWithRightChild) {
  s21::set<int> set;

  set.insert(10);
  set.insert(5);
  set.insert(15);
  set.insert(20);

  auto it = set.find(15);
  set.erase(it);

  ASSERT_EQ(set.find(15), set.end());
  ASSERT_NE(set.find(20), set.end());
  size_t n = 3;
  ASSERT_EQ(set.size(), n);
}

TEST(SetUpdateHeightTest, ThrowsWhenTreeIsEmpty) {
  s21::set<int> my_set;
  ASSERT_THROW(my_set.tree_->updateHeight(nullptr), std::logic_error);
}

TEST(SetUpdateHeightTest, NoThrowWhenNodeIsEndNode) {
  s21::set<int> my_set;
  my_set.insert(10);
  auto it = my_set.end();
  ASSERT_NO_THROW(my_set.tree_->updateHeight(it.getCurNode()));
}

TEST(SetUpdateHeightTest, UpdateHeightForSingleNode) {
  s21::set<int> my_set;
  my_set.insert(10);
  auto it = my_set.begin();
  ASSERT_NO_THROW(my_set.tree_->updateHeight(it.getCurNode()));
  ASSERT_EQ(it.getCurNode()->height_, 1);
}

TEST(SetUpdateHeightTest, UpdateHeightForMultipleNodes) {
  s21::set<int> my_set;
  my_set.insert(10);
  my_set.insert(5);
  my_set.insert(15);

  auto it = my_set.begin();
  ASSERT_NO_THROW(my_set.tree_->updateHeight(it.getCurNode()));
  ASSERT_EQ(it.getCurNode()->height_, 1);

  it = my_set.find(10);
  ASSERT_NO_THROW(my_set.tree_->updateHeight(it.getCurNode()));
  ASSERT_EQ(it.getCurNode()->height_, 2);
}

TEST(MultisetInsertManyTest, InsertManyNoElements) {
  s21::multiset<int> my_multiset;
  auto results = my_multiset.insert_many();

  size_t n = 0;
  ASSERT_EQ(results.size(), n);
}
