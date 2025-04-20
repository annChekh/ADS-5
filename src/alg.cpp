// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> opetrs;
    std::string output;
    std::string currNum;
    for (size_t i = 0; i < inf.length(); ++i) {
        char curr = inf[i];
        if (isspace(curr)) {
            continue;
        }
        if (isdigit(curr)) {
            while (i < inf.length() && (isdigit(inf[i]) || inf[i] == '.')) {
                currNum += inf[i++];
            }
            output += currNum + " ";
            currNum.clear();
            --i;
        } else if (curr == '(') {
            opetrs.push('(');
        } else if (curr == ')') {
            while (!opetrs.isEmpty() && opetrs.top() != '(') {
                output += opetrs.top();
                output += ' ';
                opetrs.pop();
            }
            if (!opetrs.isEmpty()) {
                opetrs.pop();
            } else {
                std::cerr << "Error" << std::endl;
                return "";
            }
        } else {
            while (!opetrs.isEmpty() &&
                   ((curr == '+' || curr == '-') &&
                   (opetrs.top() == '*' || opetrs.top() == '/')) ||
                   (opetrs.top() == curr)) {
                output += opetrs.top();
                output += ' ';
                opetrs.pop();
            }
            opetrs.push(curr);
        }
    }
    while (!opetrs.isEmpty()) {
        output += opetrs.top();
        output += ' ';
        opetrs.pop();
    }
    return output;
}

int eval(const std::string& pref) {
    TStack<int, 100> stack2;
    std::istringstream stream(pref);
    std::string currEl;
    while (stream >> currEl) {
        if (std::isdigit(currEl[0])) {
            stack2.push(std::stoi(currEl));
        } else if (opperator(currEl[0]) && currEl.size() == 1) {
            if (stack2.isEmpty()) {
                std::cerr << "Error" << std::endl;
                return 0;
            }
            int op2 = stack2.top(); stack2.pop();
            if (stack2.isEmpty()) {
                std::cerr << "Error" << std::endl;
                return 0;
            }
            int op1 = stack2.top(); stack2.pop();
            switch (currEl[0]) {
                case '+': stack2.push(op1 + op2);
                    break;
                case '-': stack2.push(op1 - op2);
                    break;
                case '*': stack2.push(op1 * op2);
                    break;
                case '/':
                    if (op2 == 0) {
                        std::cerr << "Error" << std::endl;
                        return 0;
                    }
                    stack2.push(op1 / op2);
                    break;
                default:
                    std::cerr << "Error" << std::endl;
                    return 0;
            }
        }
    }
    if (stack2.isEmpty()) {
        std::cerr << "Error" << std::endl;
        return 0;
    }
    int result = stack2.top(); stack2.pop();
    if (!stack2.isEmpty()) {
        std::cerr << "Error" << std::endl;
        return 0;
    }
    return result;
}
