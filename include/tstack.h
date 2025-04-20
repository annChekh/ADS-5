// Copyright 2021 NNTU-CS
#include <string>
#include <array>
#include <stdexcept>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    std::array<T, size> data;
    int topIndex;
 public:
    TStack() : topIndex(-1) {}

    bool isEmpty() const noexcept {
        return topIndex == -1;
    }

    bool isFull() const noexcept {
        return topIndex == size - 1;
    }

    void push(const T& value) {
        if (isFull()) {
            throw std::overflow_error("Stack overflow");
        }
        data[++topIndex] = value;
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow");
        }
        return data[topIndex--];
    }

    const T& peek() const {
        if (isEmpty()) {
            throw std::logic_error("Stack is empty");
        }
        return data[topIndex];
    }

    void clear() noexcept {
        topIndex = -1;
    }
};
#endif  // INCLUDE_TSTACK_H_
