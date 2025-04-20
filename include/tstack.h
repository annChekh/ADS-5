// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
    T* data;
    int capacity;
    int top;
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i <= top; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    TStack() : capacity(10), top(-1) {
        data = new T[capacity];
    }
    ~TStack() {
        delete[] data;
    }
    void push(const T& value) {
        if (top + 1 >= capacity) {
            resize();
        }
        data[++top] = value;
    }
    void pop() {
        if (top < 0) {
            throw std::underflow_error("Stack underflow");
        }
        --top;
    }
    T top() const {
        if (top < 0) {
            throw std::underflow_error("Stack is empty");
        }
        return data[top];
    }
    bool isEmpty() const {
        return top == -1;
    }
};
#endif  // INCLUDE_TSTACK_H_
