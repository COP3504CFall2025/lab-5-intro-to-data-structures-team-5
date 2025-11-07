#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : 
        capacity_(4), 
        size_(0),
        front_(0),
        back_(0),
        data_(new T[capacity_])
    {};
    explicit ABDQ(std::size_t capacity) :
        capacity_(capacity),
        size_(0),
        front_(0),
        back_(0),
        data_(new T[capacity_])
    {};

    ABDQ(const ABDQ& other) {
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        for (std::size_t i = 0; i < capacity_; i++) {
            data_[i] = other.data_[i];
        }
    };

    ABDQ(ABDQ&& other) noexcept {
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    };

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }

        T* new_data = new T[other.capacity_];

        for (size_t i = 0; i < other.capacity_; i++) {
            new_data[i] = other.data_[i];
        }

        delete data_;
        data_ = new_data;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        return *this;
    };

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    };

    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    };

    // Insertion
    void pushFront(const T& item) override {
        if ((back_ + 1) % capacity_ == front_) { // full
            // should we not do this, and just overwrite data?
            throw std::overflow_error("Deque is full. Please resize first with ensureCapacity()");
        }

        // bc of how we do this and pushBack
        // accessing requires looking at next/prev element
        // from given index
        data_[front_] = item;
        front_ = (front_ - 1) % capacity_;
    };
    void pushBack(const T& item) override { 
        if ((back_ + 1) % capacity_ == front_) { // full
            // should we not do this, and just overwrite data?
            throw std::overflow_error("Deque is full. Please resize first with ensureCapacity()");
        }

        data_[back_] = item;
        back_ = (back_ + 1) % capacity_; // set back to next element; if past capacity then it should circle around to front of array
    };

    // Deletion
    T popFront() override {
        if (front_ == back_) {
            throw std::out_of_range("No data in deque to pop.");
        }

        front_ = (front_ + 1) % capacity_;
        return data_[front_];
    };
    T popBack() override {
        if (front_ == back_) {
            throw std::out_of_range("No data in deque to pop.");
        }

        back_ = (back_ - 1) % capacity_;
        return data_[back_];
    };

    // Access
    const T& front() const override {
        if (front_ == back_) {
            throw std::out_of_range("No data in deque.");
        }
        
        return data_[(front_ + 1) % capacity_];
    };
    const T& back() const override {
        if (front_ == back_) {
            throw std::out_of_range("No data in deque.");
        }

        return data_[(back_ - 1) % capacity_];
    };

    // Size Regulators
    void ensureCapacity() {
        T* new_data = new T[capacity_ * 2];
        capacity_ *= 2;
        for (size_t i = 0; i < size_; i++) {
          new_data[i] = data_[i];  
        }
        delete data_;
        data_ = new_data;
    }

    void shrinkIfNeeded() {
        if (size_ < capacity_/2) {
            T* new_data = new T[capacity_/2];
            capacity_ /= 2;
            for (size_t i = 0; i < size_; i++) {
                new_data[i] = data_[i];
            }
            delete data_;
            data_ = new_data;
        }
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    };

};
