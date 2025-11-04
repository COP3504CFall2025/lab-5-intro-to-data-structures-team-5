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
    LLQ();

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    };

    // Deletion
    T dequeue() override {
        T headData = list.getHead()->data;
        list.removeHead();
        return headData;
    };

    // Access
    T peek() const override {
        return list.getHead()->data;
    };

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };

};
