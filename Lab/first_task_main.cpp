#include <iostream>
#include <stack>
#include <algorithm>

void show_stack(std::stack<std::string> &stack) {
    std::stack<std::string> stack_to_show = stack;
    for (int i = 0; i < stack.size(); i++) {
        std::cout << stack_to_show.top() << " ";
        stack_to_show.pop();
    }
    std::cout << std::endl;
}

std::pair<char, int> find_operation_and_location(std::stack<std::string> &stack) {
    std::stack<std::string> stack_to_find = stack;
    std::string operations = "+-*/";
    std::string obj_to_check;
    int pos = 0;
    while (!stack_to_find.empty()) {
        if (stack_to_find.top().size() > 1) {
            stack_to_find.pop();
            pos++;
            continue;
        } else {
            obj_to_check = stack_to_find.top();
        }
        for (const char &c: operations) {
            if (obj_to_check[0] == c) {
                return std::make_pair(c, pos);
            }
        }
        stack_to_find.pop();
        pos++;
    }
    return {};
}

double calculate(std::stack<std::string> &stack) {
    std::pair<char, int> operation;
    double result = (find_operation_and_location(stack).second==0)?0:std::stod(stack.top());
    stack.pop();
    while (!stack.empty()) {
        operation.first = find_operation_and_location(stack).first;
        operation.second = find_operation_and_location(stack).second;
        for (int i = 0; i < operation.second; i++) {
            switch (operation.first) {
                case '+':
                    result += std::stod(stack.top());
                    break;
                case '-':
                    result-= std::stod(stack.top());
                    stack.pop();
                    break;
                case '*':
                    result*=std::stod(stack.top());
                    stack.pop();
                    break;
                case '/':
                    result/=std::stod(stack.top());
                    stack.pop();
                    break;
            }
        }
        stack.pop();
    }
    stack.push(std::to_string(result));
    return result;
}

int main() {
    std::stack<std::string> expression;
    expression.emplace("/");
    expression.push(std::to_string(2));
    expression.emplace("+");
    expression.push(std::to_string(2));
    expression.push(std::to_string(2));
    std::cout << "Current stack is: ";
    show_stack(expression);
    std::cout << "\nFound " << find_operation_and_location(expression).first << " with pos "
              << find_operation_and_location(expression).second << "\n";
    std::cout << "Result: " <<calculate(expression);
    return 0;
}
