#include "cassert"
#include "algorithm"
#include "cstring"
#include "my_vector.h"

MyVector::MyVector(std::size_t init_capacity) : _sz(0), _cp(init_capacity), _data(new int[_cp]) {}

MyVector::~MyVector() {
  delete [] _data;
}

void MyVector::set(std::size_t index, int value) {
  assert(index >= 0 && index < _sz);
  _data[index] = value;
}
  
int MyVector::get(std::size_t index) {
  assert(index >= 0 && index < _sz);
  return _data[index];
}

std::size_t MyVector::size() {
  return _sz;
}

std::size_t MyVector::capacity() {
  return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
  if (new_capacity > _cp) {
    _cp = new_capacity;
    int *tmp = new int[_cp];
    memcpy(tmp, _data, _sz * sizeof(int));
    delete [] _data;
    _data = tmp;  
  }  
}

void MyVector::resize(std::size_t new_size) {
  if (_sz < new_size) {
    if (new_size > _cp) {
      _cp = std::max(new_size, _cp * 2);
    }
    int *tmp = new int[_cp];
    memcpy(tmp, _data, _sz * sizeof(int));
    memset(tmp + _sz, 0, (new_size - _sz) * sizeof(int));
    delete [] _data;
    _data = tmp;
  }
  _sz = new_size;
}
 
void MyVector::push_back(int value) {
  if (_sz == _cp) {
    reserve(_cp * 2);
  }
  _data[_sz] = value;
  ++_sz;
}

void MyVector::insert(std::size_t index, int value) {
  assert(index >= 0 && index <= _sz);
  if (_sz == _cp) {
    MyVector::reserve(_cp * 2);
  }
  memmove(_data + index + 1, _data + index, (_sz - index) * sizeof(int));
  _data[index] = value;
  ++_sz;
}

void MyVector::erase(std::size_t index) {
  assert(index >= 0 && index < _sz);
  memmove(_data + index, _data + index + 1, (_sz - index) * sizeof(int));
  --_sz;
}

