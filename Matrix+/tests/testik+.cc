#include <gtest/gtest.h>

#include "../project/s21_matrix+.h"

TEST(Test_GRows, 1) {
  S21Matrix val1(0, 0);
  EXPECT_EQ(0, val1.GetRows());
}

TEST(Test_GRows, 2) {
  S21Matrix val1(5, 1);
  EXPECT_EQ(5, val1.GetRows());
}

TEST(Test_GCols, 1) {
  S21Matrix val1(0, 0);
  EXPECT_EQ(0, val1.GetCols());
}

TEST(Test_GCols, 2) {
  S21Matrix val1(1, 5);
  EXPECT_EQ(5, val1.GetCols());
}

TEST(Test_SCols, 1) {
  S21Matrix val1(1, 1);
  val1.SetCols(5);
  EXPECT_EQ(5, val1.GetCols());
}

TEST(Test_SCols, 2) {
  S21Matrix val1(1, 1);
  EXPECT_THROW(val1.SetCols(-5), std::invalid_argument);
}

TEST(Test_SRows, 1) {
  S21Matrix val1(1, 1);
  val1.SetRows(5);
  EXPECT_EQ(5, val1.GetRows());
}

TEST(Test_SRows, 2) {
  S21Matrix val1(1, 1);
  EXPECT_THROW(val1.SetRows(-5), std::invalid_argument);
}

TEST(Test_S21Matrix, 1) {
  EXPECT_THROW(S21Matrix val1(-1, -1);, std::invalid_argument);
}

TEST(Test_EqMatrix, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  EXPECT_EQ(val1.EqMatrix(val2), true);
}

TEST(Test_EqMatrix, 2) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  val1.SetValue(0);
  val2.SetValue(1);
  EXPECT_EQ(val1.EqMatrix(val2), false);
}

TEST(Test_EqMatrix, 3) {
  S21Matrix val1(0, 0);
  S21Matrix val2(0, 0);
  EXPECT_EQ(val1.EqMatrix(val2), true);
}

TEST(Test_SumMatrix, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  val3.SetValue(2);
  val1.SumMatrix(val2);
  EXPECT_EQ(val1.EqMatrix(val3), true);
}

TEST(Test_SumMatrix, 2) {
  S21Matrix val1(1, 1);
  S21Matrix val2(2, 2);
  EXPECT_THROW(val1.SumMatrix(val2), std::logic_error);
}

TEST(Test_SubMatrix, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  val3.SetValue(0);
  val1.SubMatrix(val2);
  EXPECT_EQ(val1.EqMatrix(val3), true);
}

TEST(Test_SubMatrix, 2) {
  S21Matrix val1(1, 1);
  S21Matrix val2(2, 2);
  EXPECT_THROW(val1.SubMatrix(val2), std::logic_error);
}

TEST(Test_MulNumber, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  val1.SetValue(2);
  val2.SetValue(-0.4);
  val1.MulNumber(-0.2);
  EXPECT_EQ(val1.EqMatrix(val2), true);
}

TEST(Test_MulMatrix, 1) {
  S21Matrix val1(1, 1);
  S21Matrix val2(2, 2);
  EXPECT_THROW(val1.MulMatrix(val2), std::logic_error);
}

TEST(Test_MulMatrix, 2) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);
  val1.SetValue(1);
  val2.SetValue(5);
  val3.SetValue(15);
  val1.MulMatrix(val2);
  EXPECT_EQ(val1.EqMatrix(val3), true);
}

TEST(Test_Transpose, 1) {
  S21Matrix val1(3, 1);
  S21Matrix val2(1, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  // val1.Transpose();
  EXPECT_EQ(val1.Transpose().EqMatrix(val2), true);
}

TEST(Test_CalcComplements, 1) {
  S21Matrix val1(1, 5);
  EXPECT_THROW(val1.CalcComplements(), std::logic_error);
}

TEST(Test_CalcComplements, 2) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  val1.SetValue(1);
  val2.SetValue(0);
  EXPECT_EQ(val1.CalcComplements().EqMatrix(val2), true);
}

TEST(Test_Determinant, 1) {
  S21Matrix val1(1, 1);
  val1.SetValue(1);
  EXPECT_EQ(val1.Determinant(), 1);
}

TEST(Test_Determinant, 2) {
  S21Matrix val1(1, 5);
  EXPECT_THROW(val1.Determinant(), std::logic_error);
}

TEST(Test_Determinant, 3) {
  S21Matrix val1(5, 5);
  val1.SetValue(1);
  EXPECT_EQ(val1.Determinant(), 0);
}

TEST(Test_InverseMatrix, 1) {
  S21Matrix val1(1, 5);
  EXPECT_THROW(val1.InverseMatrix(), std::logic_error);
}

TEST(Test_InverseMatrix, 2) {
  S21Matrix val1(5, 5);
  val1.SetValue(1);
  EXPECT_THROW(val1.InverseMatrix(), std::logic_error);
}

TEST(Test_InverseMatrix, 3) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);

  val1.SetValue(1, 0, 0);
  val1.SetValue(2.0, 0, 1);
  val1.SetValue(3.0, 0, 2);
  val1.SetValue(4.0, 1, 0);
  val1.SetValue(5.0, 1, 1);
  val1.SetValue(5.0, 1, 2);
  val1.SetValue(5.0, 2, 0);
  val1.SetValue(5.0, 2, 1);
  val1.SetValue(5.0, 2, 2);

  val2.SetValue(0.0, 0, 0);
  val2.SetValue(-1.0, 0, 1);
  val2.SetValue(1.0, 0, 2);
  val2.SetValue(-1.0, 1, 0);
  val2.SetValue(2.0, 1, 1);
  val2.SetValue(-1.4, 1, 2);
  val2.SetValue(1.0, 2, 0);
  val2.SetValue(-1.0, 2, 1);
  val2.SetValue(0.6, 2, 2);

  val3.SetValue(0.0, 0, 0);
  val3.SetValue(-1.0, 0, 1);
  val3.SetValue(1.0, 0, 2);
  val3.SetValue(-1.0, 1, 0);
  val3.SetValue(2.0, 1, 1);
  val3.SetValue(-1.4, 1, 2);
  val3.SetValue(1.0, 2, 0);
  val3.SetValue(-1.0, 2, 1);
  val3.SetValue(0.6, 2, 2);

  EXPECT_EQ(val1.InverseMatrix().EqMatrix(val2), true);
}

TEST(Test_Minor, 2) {
  S21Matrix val1(1, 5);
  EXPECT_THROW(val1.Minor(0, -1), std::invalid_argument);
}

TEST(Test_Sum, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);
  S21Matrix val4(3, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  val3.SetValue(2);
  val1 += val2;
  EXPECT_EQ((val1).EqMatrix(val3), true);
}

TEST(Test_Sub, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);
  S21Matrix val4(3, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  val3.SetValue(0);
  val1 -= val2;
  EXPECT_EQ((val1).EqMatrix(val3), true);
}

TEST(Test_Eq, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  EXPECT_EQ((val1 == val2), true);
}

TEST(Test_MulNum, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  val1.SetValue(2);
  val2.SetValue(-0.4);
  EXPECT_EQ((val1 * (-0.2)).EqMatrix(val2), true);
}

TEST(Test_MulMatr, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);
  val1.SetValue(1);
  val2.SetValue(5);
  val3.SetValue(15);
  EXPECT_EQ((val1 * val2).EqMatrix(val3), true);
}

TEST(Test_summ, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);
  S21Matrix val4(3, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  val3.SetValue(0);
  val3 = val1 + val2;
  val1 += val2;
  EXPECT_TRUE(val1 == val3);
}

TEST(Test_subb, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);
  S21Matrix val4(3, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  val3.SetValue(-1);
  val3 = val1 - val2;
  val1 -= val2;
  EXPECT_TRUE(val1 == val3);
}

TEST(Test_mulNum, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  val1.SetValue(2);
  val2.SetValue(-0.4);
  val1 *= -0.2;
  EXPECT_EQ((val1).EqMatrix(val2), true);
}

TEST(Test_mulMatr, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  S21Matrix val3(3, 3);
  val1.SetValue(1);
  val2.SetValue(5);
  val3.SetValue(15);
  val1 *= val2;
  EXPECT_EQ((val1).EqMatrix(val3), true);
}

TEST(Test_I_J, 1) {
  S21Matrix val1(5, 5);
  EXPECT_THROW(val1(6, 5), std::out_of_range);
}

TEST(Test_eqq, 1) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  val1.SetValue(1);
  val2.SetValue(9);
  val2 = val1;
  EXPECT_TRUE(val1 == val2);
}

TEST(Test_eqq, 2) {
  S21Matrix val1(3, 3);
  S21Matrix val2(3, 3);
  val1.SetValue(1);
  val2.SetValue(1);
  val1 = val2;
  EXPECT_TRUE(val1 == val2);
}

TEST(Test_eqq, 3) {
  S21Matrix val1(3, 3);
  val1.SetValue(1);
  S21Matrix val2(std::move(val1));
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(val2(i, j), 1);
    }
  }
}

TEST(Test_eqq, 4) {
  S21Matrix val1;
  S21Matrix val2(0, 0);
  EXPECT_TRUE(val1 == val2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void S21Matrix::SetValue(double value)  // done
{
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = value;
    }
  }
}

void S21Matrix::SetValue(double value, int i, int j)  // done
{
  matrix_[i][j] = value;
}
