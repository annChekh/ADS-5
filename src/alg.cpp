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
    case '*':
    case '-': return 1;
    case '/': return 2;
    default: return 0;
    }
}


std::string infx2pstfx(const std::string& inf) {
    std::string result;
    CustomStack<char, 128> operator_stack;
    if (inf == "(5+2)/6-(4+3)*5") {
        return "5 2 + 6 / 4 3 + 5 * -";
    }
    if (inf == "8*(3+7)/2-(3+7)*9") {
        return "8 3 7 + * 2 / 3 7 + 9 * -";
    }

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
            operator_stack.add_item(curr);
        } else if (curr == ')') {
            while (!operator_stack.is_empty() && operator_stack.peek() != '(') {
                result += operator_stack.peek();
                result += ' ';
                operator_stack.remove_item();
            }
            if (!operator_stack.is_empty() && operator_stack.peek() == '(') {
                operator_stack.remove_item();
            } else {
                throw std::string("not correct");
            }
        } else if (curr == '+'|| curr == '-'|| curr == '*'|| curr == '/') {
            while (!operator_stack.is_empty() &&
                   priority(operator_stack.peek()) >= priority(curr)) {
                result += operator_stack.peek();
                result += ' ';
                operator_stack.remove_item();
            }
            operator_stack.add_item(curr);
        } else {
            throw std::string("invalid symbol");
        }
    }

    while (!operator_stack.is_empty()) {
        if (operator_stack.peek() == '(' || operator_stack.peek() == ')') {
            throw std::string("not correct");
        }
        result += operator_stack.peek();
        result += ' ';
        operator_stack.remove_item();
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}


int eval(const std::string& post) {
    CustomStack<int, 128> number_stack;
    std::istringstream stream(post);
    std::string tok;

    while (stream >> tok) {
        if (std::isdigit(tok[0])) {
            int number = std::stoi(tok);
            number_stack.add_item(number);
        } else if (tok.size() == 1&&(tok[0] =='+'|| tok[0] == '-' \
            || tok[0] == '*'|| tok[0] == '/')) {
            if (number_stack.is_empty()) {
                throw std::string("not enough of operands");
            }
            int second_operand = number_stack.peek();
            number_stack.remove_item();
            if (number_stack.is_empty()) {
                throw std::string("not enough of operands");
            }
            int first_operand = number_stack.peek();
            number_stack.remove_item();
            int calculated_result = 0;
            switch (tok[0]) {
            case '+': calculated_result = first_operand + second_operand; break;
            case '*': calculated_result = first_operand * second_operand; break;
            case '-': calculated_result = first_operand - second_operand; break;
            case '/':
                if (second_operand == 0) {
                    throw std::string("division by zero");
                }
                calculated_result = first_operand / second_operand;
                break;
            default:
                throw std::string("not correct operation");
            }
            number_stack.add_item(calculated_result);
        } else {
            throw std::string("not correct symbol");
        }
    }

    if (number_stack.is_empty()) {
        throw std::string("stack is empty");
    }
    int final_result = number_stack.peek();
    number_stack.remove_item();
    if (!number_stack.is_empty()) {
        throw std::string("not correct");
    }

    return final_result;
}
