#include "s21_matrix+.h"

int S21Matrix::GetRows() const  // done
{
  return rows_;
}

int S21Matrix::GetCols() const  // done
{
  return cols_;
}

void S21Matrix::SetRows(int rows_new)  // done
{
  if (rows_new <= 0) {
    throw std::invalid_argument("Invalid size of matrix");
  }

  S21Matrix matrix_new(rows_new, cols_);
  for (int i = 0; i < std::min(rows_, rows_new); i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_new.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(matrix_new);  // чтобы избавиться от возможных старых
                                  // мусорных данных + передача указателей
}

void S21Matrix::SetCols(int cols_new)  // done
{
  if (cols_new <= 0) {
    throw std::invalid_argument("Invalid size of matrix");
  }

  S21Matrix matrix_new(rows_, cols_new);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < std::min(cols_, cols_new); j++) {
      matrix_new(i, j) = (*this)(i, j);
    }
  }
  *this = std::move(matrix_new);
}

S21Matrix::S21Matrix()  // done
{
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols)  // done?
{
  if (rows < 0 || cols < 0) {
    throw std::invalid_argument("Invalid size of matrix");
  }
  if (rows == 0 || cols == 0) {
    matrix_ = nullptr;
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_)  // done?
{
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)  // noexcept //done
{
  cols_ = std::move(other.cols_);
  rows_ = std::move(other.rows_);
  matrix_ = std::move(other.matrix_);
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix()  // done
{
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i]) delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = cols_ = 0;
  // matrix_ = nullptr;
}

bool S21Matrix::EqMatrix(const S21Matrix& other)  // done
{
  if (matrix_ == nullptr && other.matrix_ == nullptr) return true;
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other)  // done
{
  if (cols_ != other.cols_ || rows_ != other.cols_) {
    throw std::logic_error("The matrices must be of the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this).matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other)  // done
{
  if (cols_ != other.cols_ || rows_ != other.cols_) {
    throw std::logic_error("The matrices must be of the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num)  // done
{
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other)  // done
{
  if (cols_ != other.rows_) {
    throw std::logic_error("Error in size, when multiplying two matrices");
  }
  S21Matrix matrix_new(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        matrix_new.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(matrix_new);  // передача ресурсов
}

S21Matrix S21Matrix::Transpose()  // done
{
  S21Matrix matrix_new(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_new.matrix_[j][i] = matrix_[i][j];
    }
  }
  return matrix_new;
}

S21Matrix
S21Matrix::CalcComplements()  // Aij =(−1)**(i+j)*Mij, Mij = детерминант матрицы
                              // // с вычеркнутыми i, j (минор крч говоря)
{
  if (rows_ != cols_) {
    throw std::logic_error("The matrix must be square");
  }

  S21Matrix CalcCompl(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      CalcCompl.matrix_[i][j] =
          std::pow(-1, (i + 1 + j + 1)) * Minor(i, j).Determinant();
    }
  }
  return CalcCompl;
}

double S21Matrix::Determinant()  // done
{
  if (rows_ != cols_) {
    throw std::logic_error(
        "To find the determinant, the matrix must be square");
  }

  double determinant = 0.0;
  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {
    determinant = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  }

  else {
    for (int i = 0; i < cols_; i++) {
      S21Matrix matrix_new = Minor(0, i);
      determinant += std::pow(-1, i) * matrix_[0][i] * matrix_new.Determinant();
    }
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix()  // done
{
  if (rows_ != cols_) {
    throw std::logic_error("The matrix must be square");
  }
  double determinant = Determinant();
  if (fabs(determinant) < 1e-7) {
    throw std::logic_error("Determiniant must be non zero");
  }
  // else if (rows_==1)
  // {
  //  return (1.0 / this->matrix_[0][0]);
  // }
  return (CalcComplements().Transpose() * (1.0 / determinant));
}

S21Matrix S21Matrix::Minor(int rows, int cols)  // dooonnnnn
{
  if (cols < 0) {
    throw std::invalid_argument("Invalid cols in taking minor");
  }
  int k = 0;
  S21Matrix matrix_new(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    if (i == rows) {
      continue;
    }
    int l = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == cols) {
        continue;
      }
      matrix_new.matrix_[k][l] = matrix_[i][j];
      l++;
    }
    k++;
  }
  return matrix_new;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {  // done
  S21Matrix matrix_new(*this);
  matrix_new.SumMatrix(other);
  return matrix_new;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other)  // done
{
  S21Matrix matrix_new(*this);
  matrix_new.SubMatrix(other);
  return matrix_new;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other)  // done
{
  S21Matrix matrix_new(*this);  // copy
  matrix_new.MulMatrix(other);
  return matrix_new;
}

S21Matrix S21Matrix::operator*(const double num) {  // done
  S21Matrix matrix_new(*this);                      // copy
  matrix_new.MulNumber(num);
  return matrix_new;
}

bool S21Matrix::operator==(const S21Matrix& other)  // done
{
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other)  // done
{
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other)  // done
{
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Invalid index of matric");
  }
  return matrix_[i][j];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {  // копирование done
  if (this == &other) {
    return *this;  // Самоприсваивание
  }
  S21Matrix matrix_new(other);
  *this = std::move(matrix_new);
  return *this;
}

S21Matrix& S21Matrix::operator=(
    S21Matrix&& other) noexcept {  // перемещение done
  if (this == &other) {
    return *this;  // Самоприсваивание
  } else {
    if (matrix_) {
      for (auto i = 0; i < rows_; i++) {
        if (matrix_[i]) delete[] matrix_[i];
      }
      delete[] matrix_;
    }
  }
  rows_ = std::move(other.rows_);
  cols_ = std::move(other.cols_);
  matrix_ = std::exchange(other.matrix_, nullptr);
  return *this;
}