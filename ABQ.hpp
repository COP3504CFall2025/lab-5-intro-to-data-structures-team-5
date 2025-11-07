#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

    void resize() {
        capacity_ *= scale_factor_;
        T* new_data = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
          new_data[i] = array_[i];  
        }
        delete[] array_;
        array_ = new_data;
    }
public:
    // Constructors + Big 5
    ABQ() :
        capacity_(1),
        curr_size_(0),
        array_(new T[capacity_])
    {};

    explicit ABQ(const size_t capacity) :
        capacity_(capacity),
        curr_size_(0),
        array_(new T[capacity_])
    {};

    ABQ(const ABQ& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];

        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    };

    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) {
            return *this;
        }

        T* new_arr = new T[rhs.capacity_];

        for (size_t i = 0; i < rhs.curr_size_; i++) {
            new_arr[i] = rhs.array_[i];
        }

        delete array_;
        array_ = new_arr;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;

        return *this;
    };

    ABQ(ABQ&& other) noexcept {
        array_ = other.array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;

        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    };

    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }

        delete array_;

        array_ = rhs.array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;

        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;

        return *this;
    };

    ~ABQ() noexcept override {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    };

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    };
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    };
    [[nodiscard]] T* getData() const noexcept; // not in README

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size_ >= capacity_) {
           resize();
        }
 
        for (size_t i = curr_size_; i > 0; i--) {
            // move every element to the right by one
            array_[i] = array_[i-1];
        }
        curr_size_++;
        array_[0] = data;
    };

    // Access
    T peek() const override {
        if (curr_size_ == 0) {
            throw std::out_of_range("No elements to peek in queue.");
        }

        return array_[curr_size_ - 1];
    };

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) {
            throw std::out_of_range("No elements to dequeue.");
        }

        return array_[--curr_size_];
    };

};
