#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    };

    // Deletion
    T dequeue() override {
        if (this->getSize() == 0) {
            throw std::runtime_error("No data to dequeue.");
        }

        T headData = list.getHead()->data;
        list.removeHead();
        return headData;
    };

    // Access
    T peek() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("No data in queue to peek.");
        }
        return list.getHead()->data;
    };

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };

};
