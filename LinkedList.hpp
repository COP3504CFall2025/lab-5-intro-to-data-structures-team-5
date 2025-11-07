#pragma once
#include <iostream>
using namespace std;



template <typename T>

class LinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& d, Node* p, Node* n) : data(d), prev(p), next(n) {}
    };

	// Stores pointers to first and last nodes and count
	Node* head = nullptr;
	Node* tail = nullptr;
	unsigned int count = 0;

public:
	// Behaviors
	void printForward() const {
        Node* dummy = head;
        while (dummy != nullptr) {
            std::cout << dummy->data << std::endl;
            dummy = dummy->next;
        }
    };

	void printReverse() const {
        Node* dummy = tail;
        while (dummy != nullptr) {
            std::cout << dummy->data << std::endl;
            dummy = dummy->prev;
        }
    };

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
        return count;
    };
	Node* getHead() {
        return head;
    };
	const Node* getHead() const {
        return head;
    };
	Node* getTail() {
        return tail;
    };
	const Node* getTail() const {
        return tail;
    };

	// Insertion
	void addHead(const T& data) {
        Node* new_head = new Node(data, nullptr, head);
        if (head != nullptr) {
            head->prev = new_head;
        } else { // case of empty list
            tail = new_head;
        }
        head = new_head;
        count++;
    };

	void addTail(const T& data) {
        Node* new_tail = new Node(data, tail, nullptr);
        if (tail != nullptr) {
            tail->next = new_tail;
        } else { // case of empty list
            head = new_tail;
        }
        tail = new_tail;
        count++;
    };

	// Removal
	bool removeHead() {
        if (head == nullptr) {
            return false;
        }

        Node* old_head = head;
        head = head->next;
        
        if (head != nullptr) {
            head->prev = nullptr;
        } else { // list is empty
            tail = nullptr;
        }

        delete old_head;
        count--;
        return true;
    };

	bool removeTail() {
        if (tail == nullptr) {
            return false;
        }
        
        Node* old_tail = tail;
        tail = tail->prev;

        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete old_tail;
        count--;
        return true;
    };

	void clear() {
        while (head != nullptr) {
            removeHead();
        }
    };

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;

        return *this;
    };

	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clear();
        Node* dummy = rhs.head;
        while (dummy != nullptr) {
            this->addTail(dummy->data);
            dummy = dummy->next;
        }

        return *this;
    };

	// Construction/Destruction
	LinkedList() { 
    };

	LinkedList(const LinkedList<T>& list) {
        Node* dummy = list.head;
        while (dummy != nullptr) {
            this->addTail(dummy->data); // should set head and tail
            dummy = dummy->next;
        }
    };

	LinkedList(LinkedList<T>&& other) noexcept {
        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    };

	~LinkedList() {
        clear();
    };
};


