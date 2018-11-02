#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>
#include <utility>
#include <cassert>
#include <iostream>

template <class T>
class my_vector {
public:
    my_vector<T>(std::size_t n = 0) : size_(n) {
        capacity_ = 1;
        while (capacity_ < size_)
            capacity_ *= 2;
        array_ = reinterpret_cast<T*>(new char [capacity_ * sizeof(T)]);
        for (std::size_t i = 0; i < size_; i++)
            new (array_ + i) T();
    }
    
    my_vector<T>(my_vector<T>& other) : capacity_(other.capacity_), size_(other.size_) {
        array_ = reinterpret_cast<T*>(new char [capacity_ * sizeof(T)]);
        for (std::size_t i = 0; i < size_; i++)
            new (array_ + i) T(other[i]);

    }
    
    my_vector<T>& operator=(my_vector<T>& other) {
        if (this != &other) {
            clear();
            reserve(other.size());
            size_ = other.size();
            for (std::size_t i = 0; i < size_; i++)
                new (array_ + i) T(other[i]);
        }
        return *this;
    }
    
    bool operator==(const my_vector<T>& other) const {
        if (capacity_ != other.capacity() || size_ != other.size())
            return false;
        for (size_t i = 0; i < size_; i++)
            if (array_[i] != other[i])
                return false;
        return true;
    }
    
    bool operator!=(const my_vector<T> &other) const {
        return !(*this == other);
    }
    
    ~my_vector<T>() {
        for (std::size_t i = 0; i < size_; i++)
            array_[i].~T();
        delete[]reinterpret_cast<char *>(array_);
    }

    std::size_t size() const{
        return size_;
    }
    
    std::size_t capacity() const{
        return capacity_;
    }
    
    bool empty() const{
        return !size_;
    };

    void resize(std::size_t n) {
        reserve(n);
        for (std::size_t i = n; i < size_; i++)
            array_[i].~T();
        for (std::size_t i = size_; i < n; i++)
            new (array_ + i) T();
        size_ = n;
    }
    
    void reserve(std::size_t n) {
        if (capacity_ < n) {
            while (capacity_ < n)
                capacity_ *= 2;
            T* tmp = reinterpret_cast<T*>(new char [capacity_ * sizeof(T)]);
            for (std::size_t i = 0; i < size_; i++) {
                new (tmp + i) T(array_[i]);
                array_[i].~T();
            }
            delete[]reinterpret_cast<char *>(array_);
            array_ = tmp;
        }
    }

    const T& operator[](std::size_t index) const {
       return array_[index];
    }

    T& operator[](std::size_t index) {
        return array_[index];
    }
    
    void push_back(const T &t) {
        if (size_ == capacity_)
            reserve(capacity_ * 2);
        new (array_ + size_) T(t);
        size_++;
    }
    
    void pop_back() {
        array_[--size_].~T();
    }
    
    void clear() {
        while (size_)
            array_[--size_].~T();
    }

private:
    std::size_t capacity_;
    std::size_t size_;
    T* array_;
};

template <class T>
std::ostream& operator<<(std::ostream &ostr, const my_vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    return ostr;
}

#endif

