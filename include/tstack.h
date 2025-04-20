// Copyright 2021 NNTU-CS
#include <string>
#include <array>
#include <stdexcept>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack  {
 private:
    std::array<T, max_size> items;
    int current_index;

 public:
    constexpr CustomStack() : current_index(-1) {}

    bool is_empty() const {
        return current_index < 0;
    }

    bool is_full() const {
        return current_index >= max_size - 1;
    }

    void add_item(const T& value) {
        if (is_full()) {
            throw std::string("Stack is full");
        }
        items.at(++current_index) = value;
    }

    void remove_item() {
        if (is_empty()) {
            throw std::string("Stack is empty");
        }
        --current_index;
    }

    const T& peek() const {
        if (is_empty()) {
            throw std::string("Stack is empty");
        }
        return items.at(current_index);
    }

    T& peek() {
        if (is_empty()) {
            throw std::string("Stack is empty");
        }
        return items.at(current_index);  // Безопасный доступ к элементу массива
    }
};
#endif  // INCLUDE_TSTACK_H_
