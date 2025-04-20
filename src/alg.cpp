// Copyright 2025 NNTU-CS
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: 
            return 0;
    }
}

bool opperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack1;
    std::ostringstream finall;
    bool flag = false;
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (c == ' ') continue;
        if (isdigit(c)) {
            if (flag) {
                finall << c;
            } else {
                if (!finall.str().empty()) finall << ' ';
                finall << c;
            }
            flag = true;
        } else {
                flag = false;
            if (c == '(') {
                stack1.push(c);
            } else if (c == ')') {
                while (!stack1.isEmpty() && stack1.peek() != '(') {
                    finall << ' ' << stack1.pop();
                }
                if (!stack1.isEmpty()) stack1.pop();
            } else if (opperator(c)) {
                while (!stack1.isEmpty() && stack1.peek() != '(' &&
                    prioritet(c) <= prioritet(stack1.peek())) {
                    finall << ' ' << stack1.pop();
                }
                stack1.push(c);
            }
        }
    }
    while (!stack1.isEmpty()) {
        finall << ' ' << stack1.pop();
    }
    return finall.str();
}

int eval(const std::string& post) {
    TStack<int, 100> stack2;
    std::istringstream stream(post);
    std::string token;
    while (stream >> token) {
        if (std::isdigit(token[0])) {
            stack2.push(std::stoi(token));
        } else if (opperator(token[0]) && token.size() == 1) {
            if (stack2.isEmpty()) {
                throw std::invalid_argument("Not enough operands");
            }
            int oper2 = stack2.pop();
            if (stack2.isEmpty()) {
                throw std::invalid_argument("Not enough operands");
            }
            int oper1 = stack2.pop();
            switch (token[0]) {
                case '+': stack2.push(oper1 + oper2);
                    break;
                case '-': stack2.push(oper1 - oper2);
                    break;
                case '*': stack2.push(oper1 * oper2);
                    break;
                case '/':
                    if (oper2 == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                stack2.push(oper1 / oper2);
                break;
            }
        }
    }
    if (stack2.isEmpty()) {
        throw std::invalid_argument("Empty expression");
    }
    int result = stack2.pop();
    if (!stack2.isEmpty()) {
        throw std::invalid_argument("Too many operands");
    }
    return result;
}
