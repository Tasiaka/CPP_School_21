#ifndef MATRIX_PLUS
#define MATRIX_PLUS
#include <iostream>
// #include <bits/stdc++.h>
#include <exception>
#include <utility>

class S21Matrix {
 private:
  int rows_ = 0;
  int cols_ = 0;
  // std::unique_ptr<std::unique_ptr<double[]>[]>matrix_;
  double** matrix_;

 public:
  // accessors & mutators
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix Minor(int rows, int cols);

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int i, int j) const;

  S21Matrix& operator=(
      const S21Matrix& other);  // оператор копирования // const!!!
  S21Matrix& operator=(S21Matrix&& other) noexcept;  // оператор перемещения

  // FOR TESTS
  void SetValue(double value);
  void SetValue(double value, int i, int j);
};

#endif  // MATRIX_PLUS