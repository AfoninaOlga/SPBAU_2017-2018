#include <iostream> 
#include "shared_ptr.h"

shared_ptr::shared_ptr(Matrix* obj) {
    storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
    storage_ = other.storage_;
    storage_->incr();
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
    std::swap(other.storage_, storage_);
    return *this;
}

shared_ptr::~shared_ptr() {
    storage_->decr();
    if (!storage_->getCounter())
        delete storage_;
}

Matrix* shared_ptr::ptr() const {
    return storage_->getObject();    
}

bool shared_ptr::isNull() const {
    return storage_->getObject() == NULL;
}

void shared_ptr::reset(Matrix* obj) {
    shared_ptr tmp = shared_ptr(obj);
    std::swap(tmp.storage_, storage_);
}

Matrix* shared_ptr::operator->() const {
    return storage_->getObject();
}

Matrix& shared_ptr::operator*() const {
    return *storage_->getObject();
}

shared_ptr::Storage::Storage(Matrix* mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ++ref_count_;
}

void shared_ptr::Storage::decr() {
    --ref_count_;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}

