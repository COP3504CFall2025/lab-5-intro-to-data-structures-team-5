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
        T headData;
        if (list.getHead()) {
            headData = list.getHead()->data;
        }

        if (!list.removeHead()) {
            throw std::runtime_error("Popping head failed.");
        }

        return headData;
    };
    T popBack() override {
        T backData;
        if (list.getTail()) {
            backData = list.getTail()->data;
        }

        if (!list.removeTail()) {
            throw std::runtime_error("Popping tail failed.");
        }

        return backData;
    };

    // Element Accessors
    const T& front() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("No data in deque.");
        }
        return list.getHead()->data;
    };
    const T& back() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("No data in deque.");
        }
        return list.getTail()->data;
    };

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };
};






