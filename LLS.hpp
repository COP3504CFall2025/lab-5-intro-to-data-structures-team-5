#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    };

    // Deletion
    T pop() override {
        if (this->getSize() == 0) {
            throw std::runtime_error("No data in stack to pop.");
        }
        T headVal = list.getHead()->data;   
        list.removeHead();
        return headVal;
    };

    // Access
    T peek() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("No data in stack to peek.");
        }
        return list.getHead()->data;
    };

    //Getters
    std::size_t getSize() const noexcept override {
       return list.getCount(); 
    };
};
