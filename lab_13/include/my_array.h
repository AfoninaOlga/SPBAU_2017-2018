#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <cstring>
#include <cassert>
#include <climits>

template<typename T, std::size_t N>
class my_array {
  private:
      T array_[N];
  public:
      T& operator[](std::size_t index) {
          return array_[index];
      }

      const T& operator[](std::size_t index) const {
          return array_[index];
      }

      T& at(std::size_t index) {
          assert(index >= 0 && index < N);
          return operator[](index);
      }

      const T& at(std::size_t index) const {
          assert(index >= 0 && index < N);
          return operator[](index);
      }

      bool empty() const {
          return N == 0;
      }

      std::size_t size() const {
          return N;
      }

      void fill(const T& val) {
          for (std::size_t i = 0; i < N; ++i)
              array_[i] = val;
      }
};


template<std::size_t N>
class my_array<bool, N> {
  private:
      static const std::size_t capacity_ = (N + CHAR_BIT - 1) / CHAR_BIT;

      unsigned char array_[capacity_];

      std::size_t get_block(std::size_t index) const {
          return index / CHAR_BIT;
      }

      std::size_t get_ind(std::size_t index) const {
          return index % CHAR_BIT;
      }

      class proxy {
        private:
            unsigned char& data_;
            std::size_t ind_;
        public:
            proxy(unsigned char& data, std::size_t ind) : data_(data), ind_(ind) {}

            proxy & operator=(const bool val) {
                data_ &= ~(1 << ind_);
                data_ |= ((unsigned char)val << ind_);
                return *this;
            }

            proxy & operator=(const proxy &p) {
                return *this = bool(p);
            }

            operator bool() const {
                return (data_ >> ind_) & 1;
            }
      };

  public:
      my_array() {
          memset(array_, 0, capacity_);
      }

      bool empty() const {
          return N == 0;
      }

      std::size_t size() const {
          return N;
      }

      void fill(const bool val) {
          memset(array_, val ? -1 : 0, capacity_);
      }   

      proxy operator[](std::size_t index) {
          return proxy(array_[get_block(index)], get_ind(index));
      }

      bool operator[](std::size_t index) const {
          return (array_[get_block(index)] >> get_ind(index)) & 1;
      }

      proxy at(std::size_t index) {
          assert(index >= 0 && index < N);
          return operator[](index);
      }

      bool at(std::size_t index) const {
          assert(index >= 0 && index < N);
          return operator[](index);
      }
};

#endif

