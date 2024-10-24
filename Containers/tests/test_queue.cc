#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

template <typename value_type>
bool check_eq(s21::queue<value_type> m_queue,
              std::queue<value_type> orig_queue) {
  bool result = true;
  if (m_queue.size() == orig_queue.size()) {
    while (!m_queue.empty() && !orig_queue.empty()) {
      if (m_queue.front() != orig_queue.front()) {
        result = false;
        break;
      }
      m_queue.pop();
      orig_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(Queue_test, construct_def_empty) {
  s21::queue<int> lol_my;
  EXPECT_THROW(lol_my.back(), std::logic_error);

  s21::queue<int> lol_my1;
  lol_my1.push(1);
  lol_my1.push(2);
  lol_my1.push(3);
  lol_my1.push(4);

  std::queue<int> lol_orig;
  lol_orig.push(1);
  lol_orig.push(2);
  lol_orig.push(3);
  lol_orig.push(4);

  int kek = lol_my1.front();
  int kek_orig = lol_orig.front();
  int kek_back = lol_my1.back();
  int kek_orig_back = lol_orig.back();
  EXPECT_EQ(lol_my1.size(), 4U);
  EXPECT_EQ(kek, kek_orig);
  EXPECT_EQ(kek_back, kek_orig_back);
}

TEST(Queue_test, lol) {
  s21::queue<int> lol_my;
  s21::queue<int> lol_my1;
  lol_my.push(1);
  lol_my.push(2);
  lol_my.push(3);
  lol_my1.push(1);
  lol_my1.push(2);
  lol_my1.push(3);
  lol_my.pop();
  lol_my.pop();
  lol_my.front();
  lol_my.back();
  lol_my = lol_my1;
}

TEST(Queue_test, front) {
  s21::queue<int> lol_my;
  EXPECT_THROW(lol_my.front(), std::logic_error);
}

TEST(Queue_test, empty) {
  s21::queue<int> lol_my1;
  std::queue<int> lol_orig;
  EXPECT_EQ(lol_my1.empty(), lol_orig.empty());
}

TEST(Queue_test, swap) {
  s21::queue<int> kek = {1, 2, 3, 5, 6, 7};
  s21::queue<int> kek2 = {55, 22, 53, 8342, 5643, 422};
  kek.swap(kek2);
  EXPECT_EQ(kek.back(), 422);
  EXPECT_EQ(kek.front(), 55);
}

TEST(Queue_test, not_eq_length) {
  s21::queue<int> kek = {1, 2, 3, 5, 6, 7};
  s21::queue<int> kek2 = {55, 22, 53, 8342, 5643, 422, 44, 76, 33};
  kek.swap(kek2);
  EXPECT_EQ(kek.back(), 33);
  EXPECT_EQ(kek.front(), 55);
}

TEST(Queue_test, empty_swap) {
  s21::queue<int> kek;
  s21::queue<int> kek2;
  kek.swap(kek2);
  EXPECT_THROW(kek.back(), std::logic_error);
  EXPECT_THROW(kek.front(), std::logic_error);
}

TEST(Queue_test, CompareQueues) {
  s21::queue<int> my_queue{1, 3, 10, -5, 20};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(3);
  std_queue.push(10);
  std_queue.push(-5);
  std_queue.push(20);
  EXPECT_TRUE(check_eq(my_queue, std_queue));
  std_queue.push(20);
  EXPECT_FALSE(check_eq(my_queue, std_queue));
}

TEST(Queue_test, pop) {
  s21::queue<int> lol{1, 3, 10, -5, 20, 21};
  std::queue<int> lol_orig;
  lol_orig.push(1);
  lol_orig.push(3);
  lol_orig.push(10);
  lol_orig.push(-5);
  lol_orig.push(20);
  lol_orig.push(21);
  lol.pop();
  lol.pop();
  lol_orig.pop();
  lol_orig.pop();
  EXPECT_TRUE(check_eq(lol, lol_orig));
  EXPECT_EQ(lol.front(), 10);

  s21::queue<int> empty_kek;
  EXPECT_THROW(empty_kek.back(), std::logic_error);
  EXPECT_THROW(empty_kek.pop(), std::logic_error);
  EXPECT_THROW(empty_kek.front(), std::logic_error);
}

TEST(Queue_test, InitializerqueueConstructor_2) {
  std::initializer_list<int> b;
  s21::queue<int> lol{b};
  std::queue<int> lol_orig{b};
  EXPECT_TRUE(check_eq(lol, lol_orig));
}

TEST(Queue_test, MoveConstructor) {
  std::queue<int> lol_orig;
  lol_orig.push(1);
  lol_orig.push(3);
  lol_orig.push(10);
  lol_orig.push(-5);
  lol_orig.push(20);
  lol_orig.push(21);

  s21::queue<int> lol_my;
  lol_my.push(1);
  lol_my.push(3);
  lol_my.push(10);
  lol_my.push(-5);
  lol_my.push(20);
  lol_my.push(21);
  EXPECT_TRUE(check_eq(lol_my, lol_orig));
}

TEST(Queue, Constructor_Default) {
  s21::queue<int> our_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(our_queue.empty(), std_queue.empty());
}

TEST(Queue, Constructor_List) {
  s21::queue<int> our_queue = {1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_EQ(our_queue.front(), std_queue.front());
  EXPECT_EQ(our_queue.back(), std_queue.back());
}

TEST(Queue, Constructor_Copy) {
  s21::queue<int> our_queue = {1, 2, 3};
  s21::queue<int> our_copy(our_queue);
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_copy(std_queue);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(Queue, Operator_Copy) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = our_queue_int;
  std_queue_empty = std_queue_int;
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, Constructor_Move) {
  s21::queue<int> our_queue = {1, 2, 3};
  s21::queue<int> our_move(std::move(our_queue));
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_move(std::move(std_queue));
  EXPECT_EQ(our_move.front(), std_move.front());
  EXPECT_EQ(our_move.back(), std_move.back());
  EXPECT_EQ(our_queue.empty(), std_queue.empty());
}

TEST(Queue, Operator_Move) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = std::move(our_queue_int);
  std_queue_empty = std::move(std_queue_int);
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, FrontAndBack) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<double> our_queue_double = {1.1f, 2.1f, 3.1f};
  std::queue<double> std_queue_double;
  std_queue_double.push(1.1f);
  std_queue_double.push(2.1f);
  std_queue_double.push(3.1f);
  s21::queue<std::string> our_queue_string = {"abc", "def", "ghf"};
  std::queue<std::string> std_queue_string;
  std_queue_string.push("abc");
  std_queue_string.push("def");
  std_queue_string.push("ghf");
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_double.front(), std_queue_double.front());
  EXPECT_EQ(our_queue_string.front(), std_queue_string.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  EXPECT_EQ(our_queue_double.back(), std_queue_double.back());
  EXPECT_EQ(our_queue_string.back(), std_queue_string.back());
}

TEST(Queue, Empty) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.empty(), std_queue_empty.empty());
}

TEST(Queue, Size) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.size(), std_queue_int.size());
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.size(), std_queue_empty.size());
}

TEST(Queue, Push) {
  s21::queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
}

TEST(Queue, Pop) {
  s21::queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  our_queue_int.pop();
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  our_queue_int.pop();
  our_queue_int.pop();
  std_queue_int.pop();
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, Swap) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty.swap(our_queue_int);
  std_queue_empty.swap(std_queue_int);
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, InsertManyBack) {
  s21::queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);
  EXPECT_EQ(our_queue_int.back(), 3);
}

class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  s21::queue<int> s0_{1, 2, 3, 4, 5};
  s21::queue<int> s1_{};
};

TEST_F(QueueTest, default_constructor) {
  ASSERT_TRUE(s1_.empty());
  ASSERT_EQ(s1_.size(), 0U);
}

TEST_F(QueueTest, initializer_list_constructor) {
  ASSERT_EQ(s0_.back(), 5);
  ASSERT_FALSE(s0_.empty());
  ASSERT_EQ(s0_.size(), 5U);
  s0_.pop();
  ASSERT_EQ(s0_.size(), 4U);
  s0_.pop();
  ASSERT_EQ(s0_.size(), 3U);
  ASSERT_EQ(s0_.front(), 3);
  s0_.pop();
  s0_.pop();
  s0_.pop();
  ASSERT_TRUE(s0_.empty());
}

TEST_F(QueueTest, copy_constructor) {
  s21::queue<int> copy(s0_);
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();

  ASSERT_TRUE(copy.empty());
  ASSERT_TRUE(s0_.empty());

  copy.push(69);
  s0_.push(69);
  ASSERT_EQ(copy.front(), s0_.front());
  ASSERT_EQ(copy.back(), s0_.back());
}

TEST_F(QueueTest, move_constructor) {
  s21::queue<int> moved(std::move(s0_));
  ASSERT_EQ(moved.size(), 5U);
  ASSERT_EQ(moved.back(), 5);
}

TEST_F(QueueTest, copy_assignment) {
  s21::queue<int> copy;
  copy = s0_;
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();
  ASSERT_EQ(copy.front(), s0_.front());
  copy.pop();
  s0_.pop();

  ASSERT_TRUE(copy.empty());
  ASSERT_TRUE(s0_.empty());

  copy.push(69);
  s0_.push(69);
  ASSERT_EQ(copy.front(), s0_.front());
}

TEST_F(QueueTest, move_assignment) {
  s21::queue<int> moved;
  moved = std::move(s0_);
  ASSERT_EQ(moved.size(), 5U);
  ASSERT_EQ(moved.back(), 5);
}

TEST_F(QueueTest, swap) {
  ASSERT_EQ(s1_.size(), 0U);
  ASSERT_EQ(s0_.size(), 5U);
  ASSERT_FALSE(s0_.empty());
  ASSERT_TRUE(s1_.empty());
  s0_.swap(s1_);
  ASSERT_FALSE(s1_.empty());
  ASSERT_TRUE(s0_.empty());
  ASSERT_EQ(s0_.size(), 0U);
  ASSERT_EQ(s1_.size(), 5U);
}

TEST(Queue, consts) {
  s21::queue<int> x;
  std::queue<int> y;
  int val = 69;
  x.push(val);
  y.push(val);
  x.push(val);
  x.push(val);
  y.push(val);
  y.push(val);
  const s21::queue<int> cx = x;
  const std::queue<int> cy = y;

  ASSERT_EQ(cx.front(), cy.front());
  ASSERT_EQ(cx.back(), cy.back());
}

TEST_F(QueueTest, swap_test) {
  std::queue<int> s0({1, 2, 3, 4, 5});
  ASSERT_EQ(s0_.size(), 5U);

  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(s0.front(), s0_.front());
    s0.pop();
    s0_.pop();
  }
}

TEST_F(QueueTest, push_pop_front_empty_size) {
  std::queue<int> s0;
  ASSERT_EQ(s1_.size(), 0U);
  ASSERT_TRUE(s1_.empty());

  s1_.push(1);
  s0.push(1);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.push(2);
  s0.push(2);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.push(3);
  s0.push(3);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.push(4);
  s0.push(4);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.push(5);
  s0.push(5);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_TRUE(s1_.empty());
  ASSERT_TRUE(s0.empty());
}

TEST_F(QueueTest, front_pop_push_size_empty) {
  std::queue<int> s0;
  ASSERT_EQ(s1_.size(), 0U);
  ASSERT_TRUE(s1_.empty());

  s1_.push(1);
  s0.push(1);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.push(2);
  s0.push(2);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.push(3);
  s0.push(3);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.push(4);
  s0.push(4);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.push(5);
  s0.push(5);
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.front(), s0.front());
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_FALSE(s1_.empty());

  s1_.pop();
  s0.pop();
  ASSERT_EQ(s1_.size(), s0.size());
  ASSERT_TRUE(s1_.empty());
  ASSERT_TRUE(s0.empty());
}

TEST(Queue, copy_constructor) {
  s21::queue<int> s1;
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s1.push(4);

  s21::queue<int> s0(s1);
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_EQ(s1.front(), s0.front());
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s0.empty());

  s1.pop();
  s0.pop();
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_EQ(s1.front(), s0.front());
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s0.empty());

  s1.pop();
  s0.pop();
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_EQ(s1.front(), s0.front());
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s0.empty());

  s1.pop();
  s0.pop();
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_EQ(s1.front(), s0.front());
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s0.empty());

  s1.pop();
  s0.pop();
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_TRUE(s1.empty());
  ASSERT_TRUE(s0.empty());
}

TEST(Queue, move_constructor) {
  s21::queue<int> s1;
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s1.push(4);
  s1.push(5);

  s21::queue<int> s0(std::move(s1));
  ASSERT_EQ(s1.size(), 0U);
  ASSERT_EQ(s0.size(), 5U);
  ASSERT_TRUE(s1.empty());
  ASSERT_FALSE(s0.empty());

  ASSERT_EQ(s0.front(), 1);
  s0.pop();
  ASSERT_EQ(s0.front(), 2);
  s0.pop();
  ASSERT_EQ(s0.front(), 3);
  s0.pop();
  ASSERT_EQ(s0.front(), 4);
  s0.pop();
  ASSERT_EQ(s0.front(), 5);
  s0.pop();
  ASSERT_TRUE(s0.empty());
}

TEST(Queue, constructor) {
  s21::queue<int> s0;
  ASSERT_EQ(s0.size(), 0U);
  ASSERT_TRUE(s0.empty());
}

TEST(Queue, copy_assignment) {
  s21::queue<int> s1;
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s1.push(4);

  s21::queue<int> s0;
  s0 = s1;
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_EQ(s1.front(), s0.front());
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s0.empty());

  s1.pop();
  s0.pop();
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_EQ(s1.front(), s0.front());
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s0.empty());

  s1.pop();
  s0.pop();
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_EQ(s1.front(), s0.front());
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s0.empty());

  s1.pop();
  s0.pop();
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_EQ(s1.front(), s0.front());
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s0.empty());

  s1.pop();
  s0.pop();
  ASSERT_EQ(s1.size(), s0.size());
  ASSERT_TRUE(s1.empty());
  ASSERT_TRUE(s0.empty());
}

TEST(Queue, move_assignment) {
  s21::queue<int> s1;
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s1.push(4);
  s1.push(5);

  s21::queue<int> s0;
  s0 = std::move(s1);
  ASSERT_EQ(s1.size(), 0U);
  ASSERT_EQ(s0.size(), 5U);
  ASSERT_TRUE(s1.empty());
  ASSERT_FALSE(s0.empty());

  ASSERT_EQ(s0.front(), 1);
  s0.pop();
  ASSERT_EQ(s0.front(), 2);
  s0.pop();
  ASSERT_EQ(s0.front(), 3);
  s0.pop();
  ASSERT_EQ(s0.front(), 4);
  s0.pop();
  ASSERT_EQ(s0.front(), 5);
  s0.pop();
  ASSERT_TRUE(s0.empty());
}

TEST(Queue, back) {
  s21::queue<int> s0;
  s0.push(1);
  s0.push(2);
  s0.push(3);
  s0.push(4);
  s0.push(5);

  ASSERT_EQ(s0.back(), 5);
  s0.pop();
  ASSERT_EQ(s0.back(), 5);
  s0.pop();
  ASSERT_EQ(s0.back(), 5);
  s0.pop();
  ASSERT_EQ(s0.back(), 5);
  s0.pop();
  ASSERT_EQ(s0.back(), 5);
  s0.pop();
  ASSERT_TRUE(s0.empty());
}

TEST(QueueTests, FrontOnEmptyQueueThrows) {
  const s21::queue<int> empty_queue;
  EXPECT_THROW(empty_queue.front(), std::out_of_range);
}

TEST(QueueTests, BackOnEmptyQueueThrows) {
  const s21::queue<int> empty_queue;
  EXPECT_THROW(empty_queue.back(), std::out_of_range);
}
