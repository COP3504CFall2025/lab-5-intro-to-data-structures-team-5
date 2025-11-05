#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ();

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    };
    void pushBack(const T& item) override {
        list.addTail(item);
    };

    // Core Removal Operations
    T popFront() override {
        if (this->getSize() == 0) {
            throw std::out_of_range("No data in deque to pop.");
        }
        T frontData = list.getHead()->data;
        list.removeHead();
        return frontData;
    };
    T popBack() override {
        if (this->getSize() == 0) {
            throw std::out_of_range("No data in deque to pop.");
        }
        T backData = list.getTail()->data;
        list.removeTail();
        return backData;
    };

    // Element Accessors
    const T& front() const override {
        if (this->getSize() == 0) {
            throw std::out_of_range("No data in deque.");
        }
        return list.getHead()->data;
    };
    const T& back() const override {
        if (this->getSize() == 0) {
            throw std::out_of_range("No data in deque.");
        }
        return list.getTail()->data;
    };

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };
};






