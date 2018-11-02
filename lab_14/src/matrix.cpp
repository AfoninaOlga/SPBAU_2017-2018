#include "matrix.h"
#include <algorithm>

Matrix::Matrix() : _rows(0), _cols(0), _data(NULL) {}

Matrix::Matrix(std::size_t rows, std::size_t cols) : _rows(rows), _cols(cols) {
    if (_rows == 0 || _cols == 0) {
        _data = NULL;
        return;
    }
    _data = new int*[_rows];
    int *temp = new int[_rows * _cols];
    for (std::size_t i = 0; i < _rows; ++i)
        _data[i] = temp + i * _cols;
    for (std::size_t i = 0; i < _rows; ++i)
        for (std::size_t j = 0; j < _cols; ++j)
             _data[i][j] = 0;
}

Matrix::Matrix(const Matrix &other) : Matrix(other.rows(), other.cols()) {
    for (std::size_t i = 0; i < _rows; ++i)
        for (std::size_t j = 0; j < _cols; ++j)
            _data[i][j] = other.get(i, j);
}

Matrix::~Matrix() {
    if (_rows != 0 && _cols != 0) {
        delete[] _data[0];
        delete[] _data;
  }
}

std::size_t Matrix::rows() const {
    return _rows;
}

std::size_t Matrix::cols() const {
    return _cols;
}

void Matrix::set(std::size_t row, std::size_t col, int val) {
    _data[row][col] = val;
}

int Matrix::get(std::size_t row, std::size_t col) const {
    if (row >= _rows || col >= _cols)
        throw MatrixException("ACCESS: bad index.");
    return _data[row][col];
}

Matrix& Matrix::operator=(Matrix other) {
    std::swap(_rows, other._rows);
    std::swap(_cols, other._cols);
    std::swap(_data, other._data);
    return *this;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.cols() != rhs.rows())
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix res = Matrix(lhs.rows(), rhs.cols());
    for (std::size_t i = 0; i < res.rows(); ++i)
        for (std::size_t j = 0; j < res.cols(); ++j) {
            res.set(i, j, 0);
            for (std::size_t t = 0; t < lhs.cols(); ++t)
                res.set(i, j, res.get(i, j) + lhs.get(i, t) * rhs.get(t, j));
    }
    return res;
}

Matrix& operator+=(Matrix& lhs, const Matrix& rhs) {
    if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
        throw MatrixException("ADD: dimensions do not match.");
    for (std::size_t i = 0; i < lhs.rows(); ++i)
        for (std::size_t j = 0; j < lhs.cols(); ++j)
            lhs.set(i, j, lhs.get(i, j) + rhs.get(i, j));
    return lhs;
}

Matrix& operator*=(Matrix& lhs, const Matrix& rhs) {
    return lhs = lhs * rhs;
}
