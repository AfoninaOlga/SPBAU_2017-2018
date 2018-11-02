#include <utility>
#include <cassert>
#include "cstring"
#include "matrix.h"
using std::size_t;

Matrix::Matrix(std::size_t r, std::size_t c) {
    _data = new int* [r];
    int *tmp = new int [r * c];
    memset(tmp, 0, c * r * sizeof(int));
    for (size_t i = 0; i < r; ++i) {
        _data[i] = tmp + i * c;
    }
    _rows = r;
    _cols = c;
}

Matrix::~Matrix() {
    delete [] _data[0];
    delete [] _data;
}

Matrix::Matrix(const Matrix &m) {
    _rows = m._rows;
    _cols = m._cols;
    _data = new int* [m._rows];
    int *line = new int [m._rows * m._cols];
    for (size_t i = 0; i < _rows; ++i) {
        _data[i] = line + i * _cols;
    }
    for (size_t i = 0; i < m._rows; ++i) {
        for (size_t j = 0; j < m._cols; ++j) {
            _data[i][j] = m._data[i][j];
        }
    }
}

std::size_t Matrix::get_rows() {
    return _rows;
}
std::size_t Matrix::get_cols() {
    return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    assert(i < _rows && j < _cols);
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    assert(i < _rows && j < _cols);
    return _data[i][j];
}

void Matrix::print(FILE* f) const {
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            fprintf(f, "%i ", _data[i][j]);
        }
        fprintf(f, "\n");
    }
}

void Matrix::swap(Matrix &m) {
    std::swap(_data, m._data);
    std::swap(_rows, m._rows);
    std::swap(_cols, m._cols);
}

Matrix& Matrix::operator=(Matrix m) {
    swap(m);
    return *this;
}

bool Matrix::operator==(const Matrix& m) const{
    if (m._rows != _rows || m._cols != _cols)
        return false;
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            if (m._data[i][j] != _data[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(m == *this);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    for (size_t i = 0; i < m._rows; ++i) {
        for (size_t j = 0; j < m._cols; ++j) {
            _data[i][j] += m._data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    for (size_t i = 0; i < m._rows; ++i) {
        for (size_t j = 0; j < m._cols; ++j) {
            _data[i][j] -= m._data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    *this = *this * m;
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
    return Matrix(*this) += m;
}

Matrix Matrix::operator-(const Matrix& m) const {
    return Matrix(*this) -= m;
}

Matrix Matrix::operator*(const Matrix& m) const {
    Matrix tmp(_rows, m._cols);
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < m._cols; ++j) {
            for (size_t k = 0; k < _cols; ++k) {
                tmp._data[i][j] += _data[i][k] * m._data[k][j];
            }
        }
    }
    return tmp;
}
