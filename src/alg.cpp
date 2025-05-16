// Copyright 2025 NNTU-CS
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include "tstack.h"

int prior(char op) {
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
    TStack<char, 100> st1;
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
                st1.push(c);
            } else if (c == ')') {
                while (!st1.isEmpty() && st1.peek() != '(') {
                    finall << ' ' << st1.pop();
                }
                if (!st1.isEmpty()) st1.pop();
            } else if (opperator(c)) {
                while (!st1.isEmpty() && st1.peek() != '(' &&
                    prior(c) <= prior(st1.peek())) {
                    finall << ' ' << st1.pop();
                }
                st1.push(c);
            }
        }
    }
    while (!st1.isEmpty()) {
        finall << ' ' << st1.pop();
    }
    return finall.str();
}

int eval(const std::string& pref) {
    TStack<int, 100> stk2;
    std::istringstream stream(pref);
    std::string token;
    while (stream >> token) {
        if (std::isdigit(token[0])) {
            stk2.push(std::stoi(token));
        } else if (opperator(token[0]) && token.size() == 1) {
            if (stk2.isEmpty()) {
                throw std::invalid_argument("Not enough operandov");
            }
            int oper2 = stk2.pop();
            if (stk2.isEmpty()) {
                throw std::invalid_argument("Not enough operandov");
            }
            int oper1 = stk2.pop();
            switch (token[0]) {
                case '+': 
                    stk2.push(oper1 + oper2);
                    break;
                case '-': 
                    stk2.push(oper1 - oper2);
                    break;
                case '*': 
                    stk2.push(oper1 * oper2);
                    break;
                case '/':
                    if (oper2 == 0) {
                        throw std::runtime_error("Division by 0");
                    }
                stk2.push(oper1 / oper2);
                break;
            }
        }
    }
    if (stk2.isEmpty()) {
        throw std::invalid_argument("Empty expression");
    }
    int result = stk2.pop();
    if (!stk2.isEmpty()) {
        throw std::invalid_argument("Many operands");
    }
    return result;
}
