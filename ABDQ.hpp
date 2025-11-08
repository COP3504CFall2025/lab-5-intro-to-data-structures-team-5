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
        data_(new T[4]),
        capacity_(4), 
        size_(0),
        front_(3),
        back_(0)
    {};

    explicit ABDQ(std::size_t capacity) :
        data_(new T[capacity]),
        capacity_(capacity),
        size_(0),
        front_(capacity - 1),
        back_(0)
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

        for (std::size_t i = 0; i < other.capacity_; i++) {
            new_data[i] = other.data_[i];
        }

        delete[] data_;
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

        delete[] data_;

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
        if (size_ == capacity_) { // full 
            ensureCapacity();
        }

        // bc of how we do this and pushBack
        // accessing requires looking at next/prev element
        // from given index
        data_[front_] = item;
        front_ = (front_ == 0) ? capacity_ - 1 : front_ - 1;
        size_++;
    };
    void pushBack(const T& item) override { 
        if (size_ == capacity_) { // full
            ensureCapacity();
        }

        data_[back_] = item;
        back_ = (back_ + 1) % capacity_; // set back to next element; if past capacity then it should circle around to front of array
        size_++;
    };

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("No data in deque to pop.");
        }


        front_ = (front_ + 1) % capacity_;
        T result = data_[front_];
        size_--;

        shrinkIfNeeded();

        return result;
    };
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("No data in deque to pop.");
        }

        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        T result = data_[back_];
        size_--;

        shrinkIfNeeded();

        return result;
    };

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("No data in deque.");
        }
        
        return data_[(front_ + 1) % capacity_];
    };
    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("No data in deque.");
        }

        return data_[(back_ == 0) ? capacity_ - 1 : back_ - 1];
    };

    // Size Regulators
    void ensureCapacity() {
        if (size_ < capacity_) return;


        T* new_data = new T[capacity_ * SCALE_FACTOR];

        for (std::size_t i = 0; i < size_; i++) {
            std::size_t old_index = (front_ + 1 + i) % capacity_; 
            new_data[i] = data_[old_index];  
        }

        delete[] data_;
        data_ = new_data;
        capacity_ *= SCALE_FACTOR;
        front_ = capacity_ - 1;
        back_ = size_;
    }

    void shrinkIfNeeded() {
        if (capacity_ > 1 && size_ <= capacity_ / 2) {
            T* new_data = new T[capacity_/SCALE_FACTOR];
            for (std::size_t i = 0; i < size_; i++) {
                std::size_t old_index = (front_ + 1 + i) % capacity_;
                new_data[i] = data_[old_index];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ /= SCALE_FACTOR;
            front_ = capacity_ - 1;
            back_ = size_;
        }
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    };

};
