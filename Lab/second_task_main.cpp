#include <iostream>
#include <vector>
#include <stack>
#include <map>

bool is_correct(std::string &expr) {
    // Declare a stack to hold the previous brackets.
    std::stack<char> temp;
    for (char i : expr) {
        if (temp.empty()) temp.push(i);
        else if ((temp.top() == '(' && i == ')')
                 || (temp.top() == '{' && i == '}')
                 || (temp.top() == '[' && i == ']')) {
            temp.pop();
        } else temp.push(i);
    }
    if (temp.empty())return true;
    return false;
}

int main() {
    std::string expression{"({}[])"};
    std::string brackets;
    for (const char &c: expression) {
        switch (c) {
            case '{':
            case '[':
            case '(':
            case '}':
            case ']':
            case ')':
                brackets+= c;
                break;
            default:
                continue;
        }
    }
    bool (*is_correct_f)(std::string &exp);
    is_correct_f = &is_correct;
    std::cout << is_correct_f(brackets);
}