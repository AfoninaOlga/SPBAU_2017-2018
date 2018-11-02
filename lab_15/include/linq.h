#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;

template<typename T>
class enumerator {
public:
    virtual const T& operator*() const = 0;
    virtual enumerator<T>& operator++() = 0;
    virtual operator bool() const = 0;

    auto drop(int count) {
        return drop_enumerator<T>(*this, count);
    }

    auto take(int count) {
        return take_enumerator<T>(*this, count);
    }

    template<typename U = T, typename F>
    auto select(F func) {
        return select_enumerator<U, T, F>(*this, std::move(func));
    }

    template<typename F>
    auto until(F func) {
        return until_enumerator<T, F>(*this, std::move(func));
    }

    auto until_eq(const T &val) {
        return until([&val] (const T &x) { return x == val; });
    }

    template<typename F>
    auto where(F func) {
        return where_enumerator<T, F>(*this, std::move(func));
    }

    auto where_neq(const T &val) {
        return where([&val] (const T &x) { return x != val; });
    }

    std::vector<T> to_vector() {
        std::vector<T> res;
        while (*this) {
            res.push_back(**this);
            ++(*this);
        }
        return res;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        while (*this) {
        *it = **this;
        ++(*this);
        }
    }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
    const T& operator*() const {
        return *begin_;
    }

    enumerator<T>& operator++() {
        ++begin_;
        return *this;
    }

    operator bool() const {
        return begin_ != end_;
    }
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {
    }

private:
    Iter begin_, end_;
};

template<typename T>
auto from(T begin, T end) {
    return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
    const T& operator*() const {
        return *parent_;
    }

    enumerator<T>& operator++() {
        ++parent_;
        return *this;
    }

    operator bool() const {
        return parent_;
    }

    drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
        while (parent_ && count) {
            ++parent_;
            --count;
        }
    }

private:
    enumerator<T> &parent_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
    const T& operator*() const {
        return *parent_;
    }

    enumerator<T>& operator++() {
        ++taken_;
        if (!*this)
            return *this;
        ++parent_;
        return *this;
    }

    operator bool() const {
        return parent_ && taken_ < count_;
    }

    take_enumerator(enumerator<T> &parent, int count) :
                    parent_(parent), count_(count) { }

private:
    enumerator<T> &parent_;
    int taken_ = 0;
    int count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
    const T& operator*() const {
        return last_;
    }

    enumerator<T>& operator++() {
        ++parent_;
        if (parent_)
            last_ = func_(*parent_);
        return *this;
    }

    operator bool() const {
        return parent_;
    }

    select_enumerator(enumerator<U> &parent, F func) :
                    parent_(parent), func_(std::move(func)) {
        if (parent_)
            last_ = func_(*parent_);
    }

private:
    enumerator<U> &parent_;
    F func_;
    T last_;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
    const T& operator*() const {
        return *parent_;
    }

    enumerator<T>& operator++() {
        if (!*this)
            return *this;
        ++parent_;
        if (parent_ && !fin_)
            fin_ = predicate_(*parent_);
        return *this;
    }

    operator bool() const {
        return parent_ && !fin_;
    }

    until_enumerator(enumerator<T> &parent, F predicate) :
                    parent_(parent), predicate_(std::move(predicate)) {
        if (parent_ && !fin_)
            fin_ = predicate_(*parent_);
    }

private:
    enumerator<T> &parent_;
    F predicate_;
    bool fin_ = false;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
    const T& operator*() const {
        return *parent_;
    }

    enumerator<T>& operator++() {
        ++parent_;
        while (parent_ && !predicate_(*parent_))
            ++parent_;
        return *this;
    }

    operator bool() const {
        return parent_;
    }

    where_enumerator(enumerator<T> &parent, F predicate) :
                    parent_(parent), predicate_(std::move(predicate)) {
        while (parent_ && !predicate_(*parent_))
            ++parent_;
    }

private:
    enumerator<T> &parent_;
    F predicate_;
};

#endif

