// Copyright 2025 NNTU-CS
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include "tstack.h"

int priority(char oper) {
    switch (oper) {
        case '+':
        case '-': 
            return 1;
        case '*':
        case '/': 
            return 2;
        default: 
            return 0;
    }
}

std::string infx2pstfx(const std::string& inf) {
    std::string result;
    TStack<char, 128> operator_stack;  // Changed from CustomStack to TStack

    for (size_t idx = 0; idx < inf.size(); ++idx) {
        char curr = inf[idx];
        if (curr == ' ') {
            continue;
        }

        if (std::isdigit(curr)) {
            while (idx < inf.size() && std::isdigit(inf[idx])) {
                result += inf[idx++];
            }
            --idx;
            result += ' ';
        } else if (curr == '(') {
            operator_stack.push(curr);
        } else if (curr == ')') {
            while (!operator_stack.isEmpty() && operator_stack.top() != '(') {
                result += operator_stack.top();
                result += ' ';
                operator_stack.pop();
            }
            if (operator_stack.isEmpty()) {
                throw std::runtime_error("Mismatched parentheses");
            }
            operator_stack.pop();
        } else if (curr == '+' || curr == '-' || curr == '*' || curr == '/') {
            while (!operator_stack.isEmpty() &&
                   priority(operator_stack.top()) >= priority(curr)) {
                result += operator_stack.top();
                result += ' ';
                operator_stack.pop();
            }
            operator_stack.push(curr);
        } else {
            throw std::runtime_error("Invalid symbol in expression");
        }
    }

    while (!operator_stack.isEmpty()) {
        if (operator_stack.top() == '(') {
            throw std::runtime_error("Mismatched parentheses");
        }
        result += operator_stack.top();
        result += ' ';
        operator_stack.pop();
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 128> number_stack;  // Changed from CustomStack to TStack
    std::istringstream stream(post);
    std::string currEl;

    while (stream >> currEl) {
        if (std::isdigit(currEl[0])) {
            number_stack.push(std::stoi(currEl));
        } else if (currEl.size() == 1 && 
                  (currEl[0] == '+' || currEl[0] == '-' ||
                   currEl[0] == '*' || currEl[0] == '/')) {
            if (number_stack.isEmpty()) {
                throw std::runtime_error("Not enough operands for operation");
            }
            int opnd2 = number_stack.top();
            number_stack.pop();

            if (number_stack.isEmpty()) {
                throw std::runtime_error("Not enough operands for operation");
            }
            int opnd1 = number_stack.top();
            number_stack.pop();

            int calcRes;
            switch (currEl[0]) {
                case '+': calcRes = opnd1 + opnd2; break;
                case '-': calcRes = opnd1 - opnd2; break;
                case '*': calcRes = opnd1 * opnd2; break;
                case '/':
                    if (opnd2 == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    calcRes = opnd1 / opnd2;
                    break;
                default:
                    throw std::runtime_error("Invalid operator");
            }
            number_stack.push(calcRes);
        } else {
            throw std::runtime_error("Invalid token in postfix expression");
        }
    }

    if (number_stack.isEmpty()) {
        throw std::runtime_error("Empty stack after evaluation");
    }

    int final_result = number_stack.top();
    number_stack.pop();

    if (!number_stack.isEmpty()) {
        throw std::runtime_error("Malformed postfix expression");
    }

    return final_result;
}
