// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string output;
    std::istringstream iss(inf);
    std::string currEl;

    while (iss >> currEl) {
        if (std::isdigit(currEl[0])) {
            output += currEl + " ";
        } else if (currEl.size() == 1 && isOperator(currEl[0])) {
            char op = currEl[0];
            while (!stack.IsEmpty() && isOperator(stack.Top()) &&
                precedence(stack.Top()) >= precedence(op)) {
                output += stack.Top();
                output += " ";
                stack.Pop();
            }
            stack.Push(op);
        } else if (currEl == "(") {
            stack.Push('(');
        } else if (currEl == ")") {
            while (!stack.IsEmpty() && stack.Top() != '(') {
                output += stack.Top();
                output += " ";
                stack.Pop();
            }
            if (!stack.IsEmpty() && stack.Top() == '(')
                stack.Pop();
        }
    }
    while (!stack.IsEmpty()) {
        output += stack.Top();
        output += " ";
        stack.Pop();
    }
    if (!output.empty() && output.back() == ' ')
        output.pop_back();

    return output;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string currEl;

    while (iss >> currEl) {
        if (std::isdigit(currEl[0]) ||
            (currEl.size() > 1 && currEl[0] == '-')) {
            stack.Push(std::stoi(currEl));
        } else if (currEl.size() == 1 && isOperator(currEl[0])) {
            int b = stack.Top(); stack.Pop();
            int a = stack.Top(); stack.Pop();
            int res = 0;
            switch (currEl[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/':
                    if (b == 0) throw std::runtime_error("Деление на ноль");
                    res = a / b;
                    break;
            }
            stack.Push(res);
        }
    }
    return stack.Top();
}
