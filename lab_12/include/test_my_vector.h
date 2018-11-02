#ifndef TEST_MY_VECTOR_H
#define TEST_MY_VECTOR_H

#include "my_vector.h"

template <typename T>
void test_my_vector(T t1, T t2) {
    my_vector<T> v, v1;
    assert(v.size() == 0);
    assert(v.capacity());
    assert(v.empty());

    v.resize(2);
    v[0] = t1;
    v[1] = t2;
    assert(!v.empty());
    assert(v[0] == t1 && v[1] == t2);
    assert((char*) &v[1] == (char*) &v[0] + sizeof(T));
    assert(v.size() == 2);
    assert(v.capacity() >= v.size());

    v1 = v;
    assert(v1 == v);

    my_vector<T> v2(v);
    assert(v == v2);
    
    my_vector<T> v3(666);
    assert(v3.size() == 666);

    size_t prev_sz = v.size();
    v.reserve(7);
    assert(v.capacity() >= 7);
    assert(v.size() == prev_sz);
    assert(v1 != v);

    v.push_back(t1);
    assert(v[2] == t1);
    assert(v.size() == prev_sz + 1);

    v.pop_back();
    assert(v.size() == prev_sz);
    assert(v[0] == t1);
    assert(v[1] == t2);

    v.resize(66);
    assert(v.size() == 66);
    assert(v.capacity() >= 66);

    v.clear();
    assert(v.empty());
}

#endif

