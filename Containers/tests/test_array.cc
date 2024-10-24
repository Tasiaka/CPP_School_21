#include <array>

#include "../s21_containers.h"
#include "../s21_containersplus.h"
#include "gtest/gtest.h"

TEST(TestArray, BasicConstructor_1) {
  s21::array<int, 6> arr_instance_s21;
  std::array<int, 6> arr_instance_std;
  ASSERT_EQ(arr_instance_s21.size(), arr_instance_std.size());
  for (size_t i = 0; i < arr_instance_s21.size(); i++) {
    ASSERT_EQ(arr_instance_s21[i], 0);
  }
}

TEST(TestArray, BasicConstructor_2) {
  s21::array<char, 6> arr_instance_s21;
  std::array<char, 6> arr_instance_std;
  ASSERT_EQ(arr_instance_s21.size(), arr_instance_std.size());
  for (size_t i = 0; i < arr_instance_s21.size(); i++) {
    ASSERT_EQ(arr_instance_s21[i], 0);
  }
}

TEST(TestArray, BasicConstructor_3) {
  s21::array<int, 0> arr_instance_empty_s21;
  std::array<int, 0> arr_instance_empty_std;
  ASSERT_EQ(arr_instance_empty_s21.size(), arr_instance_empty_std.size());
}

TEST(TestArray, InitListConstructor_1) {
  s21::array<int, 6> arr_instance_s21{1, 2};
  std::array<int, 6> arr_instance_std{1, 2};
  ASSERT_EQ(arr_instance_s21.size(), arr_instance_std.size());
  for (size_t i = 0; i < arr_instance_s21.size(); i++) {
    ASSERT_EQ(arr_instance_s21[i], arr_instance_std[i]);
  }
}

TEST(TestArray, InitListConstructor_2) {
  s21::array<char, 2> arr_instance_s21{'a', 'v'};
  std::array<char, 2> arr_instance_std{'a', 'v'};
  ASSERT_EQ(arr_instance_s21.size(), arr_instance_std.size());
  for (size_t i = 0; i < arr_instance_s21.size(); i++) {
    ASSERT_EQ(arr_instance_s21[i], arr_instance_std[i]);
  }
}

TEST(TestArray, CopyConstructor_1) {
  s21::array<char, 2> arr_instance_s21_1{'a', 'v'};
  s21::array<char, 2> arr_instance_s21_2(arr_instance_s21_1);
  ASSERT_EQ(arr_instance_s21_1.size(), arr_instance_s21_2.size());
  ASSERT_NE(&arr_instance_s21_1, &arr_instance_s21_2);
  for (size_t i = 0; i < arr_instance_s21_2.size(); i++) {
    ASSERT_EQ(arr_instance_s21_1[i], arr_instance_s21_2[i]);
  }
}

TEST(TestArray, CopyConstructor_2) {
  s21::array<char, 2> arr_instance_s21_1{'a', 'v'};
  s21::array<char, 2> arr_instance_s21_2(arr_instance_s21_1);
  s21::array<char, 2> arr_instance_s21_3(arr_instance_s21_2);
  ASSERT_EQ(arr_instance_s21_1.size(), arr_instance_s21_3.size());
  ASSERT_NE(&arr_instance_s21_1, &arr_instance_s21_3);
  for (size_t i = 0; i < arr_instance_s21_3.size(); i++) {
    ASSERT_EQ(arr_instance_s21_1[i], arr_instance_s21_3[i]);
  }
}

TEST(TestArray, MoveConstructor_1) {
  s21::array<char, 2> arr_instance_s21_1{'a', 'v'};
  s21::array<char, 2> arr_instance_s21_2(std::move(arr_instance_s21_1));
  ASSERT_EQ(arr_instance_s21_1.size(), arr_instance_s21_2.size());
  ASSERT_NE(&arr_instance_s21_1, &arr_instance_s21_2);
  for (size_t i = 0; i < arr_instance_s21_2.size(); i++) {
    ASSERT_EQ(arr_instance_s21_1[i], arr_instance_s21_2[i]);
  }
}

TEST(TestArray, MoveConstructor_2) {
  s21::array<char, 2> arr_instance_s21_1{'a', 'v'};
  s21::array<char, 2> arr_instance_s21_2(std::move(arr_instance_s21_1));
  s21::array<char, 2> arr_instance_s21_3(std::move(arr_instance_s21_2));
  ASSERT_EQ(arr_instance_s21_1.size(), arr_instance_s21_3.size());
  ASSERT_NE(&arr_instance_s21_1, &arr_instance_s21_3);
  for (size_t i = 0; i < arr_instance_s21_3.size(); i++) {
    ASSERT_EQ(arr_instance_s21_1[i], arr_instance_s21_3[i]);
  }
}

TEST(TestArray, MoveAssignConstructor_1) {
  s21::array<char, 2> arr_instance_s21_1{'a', 'v'};
  s21::array<char, 2> arr_instance_s21_2 = std::move(arr_instance_s21_1);
  ASSERT_EQ(arr_instance_s21_1.size(), arr_instance_s21_2.size());
  ASSERT_NE(&arr_instance_s21_1, &arr_instance_s21_2);
  for (size_t i = 0; i < arr_instance_s21_2.size(); i++) {
    ASSERT_EQ(arr_instance_s21_1[i], arr_instance_s21_2[i]);
  }
}

TEST(TestArray, MoveAssignConstructor_2) {
  s21::array<char, 2> arr_instance_s21_1{'a', 'v'};
  s21::array<char, 2> arr_instance_s21_2 = std::move(arr_instance_s21_1);
  s21::array<char, 2> arr_instance_s21_3 = std::move(arr_instance_s21_2);
  ASSERT_EQ(arr_instance_s21_1.size(), arr_instance_s21_3.size());
  ASSERT_NE(&arr_instance_s21_1, &arr_instance_s21_3);
  for (size_t i = 0; i < arr_instance_s21_3.size(); i++) {
    ASSERT_EQ(arr_instance_s21_1[i], arr_instance_s21_3[i]);
  }
}

TEST(TestArray, AssignConstructor_1) {
  s21::array<char, 2> arr_instance_s21;
  arr_instance_s21 = {'a', 'v'};
  std::array<char, 2> arr_instance_std;
  arr_instance_std = {'a', 'v'};
  ASSERT_EQ(arr_instance_s21.size(), arr_instance_std.size());
  for (size_t i = 0; i < arr_instance_s21.size(); i++) {
    ASSERT_EQ(arr_instance_s21[i], arr_instance_std[i]);
  }
}

TEST(TestArray, At_1) {
  s21::array<char, 9> arr_instance_s21{'a', 'v'};
  std::array<char, 9> arr_instance_std{'a', 'v'};
  ASSERT_EQ(arr_instance_s21.at(0), arr_instance_std.at(0));
  ASSERT_EQ(arr_instance_s21.at(1), arr_instance_std.at(1));
  ASSERT_EQ(arr_instance_s21.at(8), arr_instance_std.at(8));
}

TEST(TestArray, OperatorBrackets) {
  s21::array<char, 9> arr_instance_s21{'a', 'v'};
  std::array<char, 9> arr_instance_std{'a', 'v'};
  ASSERT_EQ(arr_instance_s21[0], arr_instance_std[0]);
  ASSERT_EQ(arr_instance_s21[1], arr_instance_std[1]);
  ASSERT_EQ(arr_instance_s21[8], arr_instance_std[8]);
}

TEST(TestArray, Front) {
  s21::array<char, 9> arr_instance_s21{'a', 'v'};
  std::array<char, 9> arr_instance_std{'a', 'v'};
  ASSERT_EQ(arr_instance_s21.front(), arr_instance_std.front());
}

TEST(TestArray, Back) {
  s21::array<char, 9> arr_instance_s21{'a', 'v'};
  std::array<char, 9> arr_instance_std{'a', 'v'};
  ASSERT_EQ(arr_instance_s21.back(), arr_instance_std.back());
}

TEST(TestArray, Data) {
  s21::array<char, 9> arr_instance_s21{'a', 'v'};
  ASSERT_EQ(arr_instance_s21.data(), arr_instance_s21.begin());
}

TEST(TestArray, BeginEnd_1) {
  s21::array<char, 3> arr_instance_s21{'a', 'v', 'f'};
  auto element_1 = arr_instance_s21.begin() + 1;
  auto element_2 = arr_instance_s21.end() - 1;
  ASSERT_EQ(*element_1, 'v');
  ASSERT_EQ(*element_2, 'f');
  ASSERT_TRUE(element_1 == (element_2 - 1));
  ASSERT_TRUE(element_1 != element_2);
  ASSERT_EQ(++element_1, &arr_instance_s21[2]);
  ASSERT_EQ(--element_2, &arr_instance_s21[1]);
}

TEST(TestArray, Empty) {
  s21::array<char, 9> arr_instance_s21_1{'a', 'v'};
  std::array<char, 9> arr_instance_std_1{'a', 'v'};
  ASSERT_EQ(arr_instance_s21_1.empty(), arr_instance_std_1.empty());

  s21::array<char, 2> arr_instance_s21_2;
  std::array<char, 2> arr_instance_std_2;
  ASSERT_EQ(arr_instance_s21_2.empty(), arr_instance_std_2.empty());

  s21::array<char, 0> arr_instance_s21_3;
  std::array<char, 0> arr_instance_std_3;
  ASSERT_EQ(arr_instance_s21_3.empty(), arr_instance_std_3.empty());
}

TEST(TestArray, Size) {
  s21::array<char, 9> arr_instance_s21_1{'a', 'v'};
  std::array<char, 9> arr_instance_std_1{'a', 'v'};
  ASSERT_EQ(arr_instance_s21_1.size(), arr_instance_std_1.size());

  s21::array<char, 2> arr_instance_s21_2;
  std::array<char, 2> arr_instance_std_2;
  ASSERT_EQ(arr_instance_s21_2.size(), arr_instance_std_2.size());

  s21::array<char, 0> arr_instance_s21_3;
  std::array<char, 0> arr_instance_std_3;
  ASSERT_EQ(arr_instance_s21_3.size(), arr_instance_std_3.size());
}

TEST(TestArray, MaxSize) {
  s21::array<char, 9> arr_instance_s21_1{'a', 'v'};
  std::array<char, 9> arr_instance_std_1{'a', 'v'};
  ASSERT_EQ(arr_instance_s21_1.max_size(), arr_instance_std_1.max_size());

  s21::array<char, 2> arr_instance_s21_2;
  std::array<char, 2> arr_instance_std_2;
  ASSERT_EQ(arr_instance_s21_2.max_size(), arr_instance_std_2.max_size());

  s21::array<char, 0> arr_instance_s21_3;
  std::array<char, 0> arr_instance_std_3;
  ASSERT_EQ(arr_instance_s21_3.max_size(), arr_instance_std_3.max_size());
}

TEST(TestArray, Fill) {
  s21::array<char, 9> arr_instance_s21{'a', 'v'};
  std::array<char, 9> arr_instance_std{'a', 'v'};
  arr_instance_s21.fill('f');
  arr_instance_std.fill('f');

  for (size_t i = 0; i < 9; i++) {
    ASSERT_EQ(arr_instance_s21[i], arr_instance_std[i]);
  }
}

TEST(S21ArrayTest, InitializerListExceedsCapacity) {
  EXPECT_THROW((s21::array<int, 3>({1, 2, 3, 4})), std::out_of_range);
}

TEST(TestArray, Swap) {
  s21::array<char, 9> arr_instance_s21_1{'a', 'v'};
  s21::array<char, 9> arr_instance_s21_2{'c', 'o'};
  arr_instance_s21_1.swap(arr_instance_s21_2);

  ASSERT_EQ(arr_instance_s21_1[0], 'c');
  ASSERT_EQ(arr_instance_s21_1[1], 'o');
  ASSERT_EQ(arr_instance_s21_1[2], '\0');
  ASSERT_EQ(arr_instance_s21_2[0], 'a');
  ASSERT_EQ(arr_instance_s21_2[1], 'v');
  ASSERT_EQ(arr_instance_s21_2[2], '\0');
}
