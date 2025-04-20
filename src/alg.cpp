// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "tstack.h"

int prioritet(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
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
    CustomStack<int, 128> number_stack;
    std::istringstream stream(post);
    std::string currEl;

    while (stream >> currEl) {
        if (std::isdigit(currEl[0])) {
            number_stack.add_item(std::stoi(currEl));
        } 
        else if (currEl.size() == 1 && (currEl[0] == '+' || currEl[0] == '-' || 
                                     currEl[0] == '*' || currEl[0] == '/')) {
            if (number_stack.is_empty()) {
                throw std::runtime_error("Not enough operands for operation");
            }
            int opnd2 = number_stack.peek();
            number_stack.remove_item();

            if (number_stack.is_empty()) {
                throw std::runtime_error("Not enough operands for operation");
            }
            int opnd1 = number_stack.peek();
            number_stack.remove_item();

            int calcRes;
            switch (currEl[0]) {
                case '+': 
                    calcRes = opnd1 + opnd2; 
                    break;
                case '-': 
                    calcRes = opnd1 - opnd2; 
                    break;
                case '*': 
                    calcRes = opnd1 * opnd2; 
                    break;
                case '/':
                    if (opnd2 == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    calcRes = opnd1 / opnd2;
                    break;
                default:
                    throw std::runtime_error("Invalid operator");
            }
            number_stack.add_item(calcRes);
        } 
        else {
            throw std::runtime_error("Invalid token in postfix expression");
        }
    }

    if (number_stack.is_empty()) {
        throw std::runtime_error("Empty stack after evaluation");
    }

    int final_result = number_stack.peek();
    number_stack.remove_item();

    if (!number_stack.is_empty()) {
        throw std::runtime_error("Malformed postfix expression");
    }

    return final_result;
}
