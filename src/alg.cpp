// Copyright 2025 NNTU-CS
#include <string>
#include <iostream>
#include <map>
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
    TStack<int, 100> operands;
    std::string currNum;
    for (size_t i = 0; i < pref.length(); ++i) {
        char curr = pref[i];
        if (isspace(curr)) {
            continue;
        }

        if (isdigit(curr)) {
            while (i < pref.length() && (isdigit(pref[i]) || pref[i] == '.')) {
                currNum += pref[i++];
            }
            operands.push(std::stoi(currNum));
            currNum.clear();
            --i;
        } else {
            if (operands.isEmpty()) {
                std::cerr << "Error" << std::endl;
                return 0;
            }
            int right = operands.top(); operands.pop();
            if (operands.isEmpty()) {
                std::cerr << "Error" << std::endl;
                return 0;
            }
            int left = operands.top(); operands.pop();
            int result;
            switch (curr) {
                case '+': result = left + right;
                  break;
                case '-': result = left - right;
                  break;
                case '*': result = left * right;
                  break;
                case '/':
                    if (right == 0) {
                        std::cerr << "Error" << std::endl;
                        return 0;
                    }
                    result = left / right;
                    break;
                default: 
                    std::cerr << "Error" << std::endl;
                    return 0;
            }
            operands.push(result);
        }
    }
    if (operands.isEmpty()) {
        std::cerr << "Error" << std::endl;
        return 0;
    }
    return operands.top();
}
