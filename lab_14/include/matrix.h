#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <cstdio>
#include <cstddef>
#include <string>
#include <exception>

class Matrix {
public:
    Matrix();
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(const Matrix &other);
    ~Matrix();
    std::size_t rows() const;
    std::size_t cols() const;
    void set(std::size_t row, std::size_t col, int val);
    int get(std::size_t row, std::size_t col) const;
    Matrix & operator=(Matrix other);
private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};

Matrix operator*(const Matrix &lhs, const Matrix &rhs);
Matrix & operator+=(Matrix &lhs, const Matrix &rhs);
Matrix & operator*=(Matrix &lhs, const Matrix &rhs);

class MatrixException : public std::exception {
private:
    std::string _message;
public:
    MatrixException(const char* msg) : _message(msg) {};
    const char* what() {
        return _message.c_str(); 
    };
};

#endif

