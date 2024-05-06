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

template<typename T>
struct OperationApplier {
    char operation;
    int operation_pos;
    T operand;
    T result;

    OperationApplier(T operand, char operation) : operation{operation}, operand{operand} {}
    ~OperationApplier(){};

    T operator()() {
        switch (operation) {
            case '+':
                result += operand;
                break;
            case '-':
                result -= operand;
                break;
            case '*':
                result *= operand;
                break;
            case '/':
                result /= operand;
                break;
        }
        return result;
    }
};

double calculate(std::stack<std::string> &stack) {
    if(find_operation_and_location(stack).second == 0) stack.pop();
    double result = std::stod(stack.top());
    OperationApplier<double> operation_to_do{std::stod(stack.top()),
                                             find_operation_and_location(stack).first};
    stack.pop();
    while (!stack.empty()) {
        operation_to_do.operation = find_operation_and_location(stack).first;
        operation_to_do.operation_pos = find_operation_and_location(stack).second;
        operation_to_do.result = result;
        operation_to_do.operand = std::stod(stack.top());
        for (int i = 0; i < operation_to_do.operation_pos; i++) {
            result = operation_to_do();
            stack.pop();
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
    expression.push(std::to_string(4));
    expression.emplace("+");
    std::cout << "Current stack is: ";
    show_stack(expression);
    std::cout << "Result: " << calculate(expression);
    return 0;
}
