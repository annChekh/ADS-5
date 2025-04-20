// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> operators;
  std::string output;
  std::string currentNumber;
  for (size_t i = 0; i < inf.length(); ++i) {
    char current = inf[i];
    if (isspace(current)) {
        continue;
    }
    if (isdigit(current)) {
      while (i < inf.length() && (isdigit(inf[i]) || inf[i] == '.')) {
        currentNumber += inf[i++];
      }
            output += currentNumber + " ";
            currentNumber.clear();
            --i;
    } else if (current == '(') {
      operators.push('(');
    } else if (current == ')') {
        while (!operators.isEmpty() && operators.top() != '(') {
          output += operators.top();
          output += ' ';
          operators.pop();
        }
            operators.pop();
        } else {
            while (!operators.isEmpty() &&
                   ((current == '+' || current == '-') &&
                   (operators.top() == '*' || operators.top() == '/')) ||
                   (operators.top() == current)) ) {
                output += operators.top();
                output += ' ';
                operators.pop();
            }
            operators.push(current);
        }
    }
    while (!operators.isEmpty()) {
        output += operators.top();
        output += ' ';
        operators.pop();
    }
  return output;
}

int eval(const std::string& pref) {
    TStack<int, 100> operands;
    std::string currentNumber;
    for (size_t i = 0; i < post.length(); ++i) {
        char current = post[i];
        if (isspace(current)) {
            continue;
        }
        if (isdigit(current)) {
            while (i < post.length() && (isdigit(post[i]) || post[i] == '.')) {
                currentNumber += post[i++];
            }
            operands.push(std::stoi(currentNumber));
            currentNumber.clear();
            --i;
        } else {
            int right = operands.top(); operands.pop();
            int left = operands.top(); operands.pop();
            int result;
            switch (current) {
              case '+': result = left + right;
                break;
              case '-': result = left - right;
                break;
              case '*': result = left * right;
                break;
              case '/': 
                  if (right == 0) throw std::invalid_argument("Cannot divided by zero");
                  result = left / right; 
                  break;
              default: throw std::invalid_argument("Unknown operator");
            }
          operands.push(result);
      }
    }
  return operands.top();
}
