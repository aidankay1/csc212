/*
4B. Evaluating a postfix expression
*/

#include <cmath>
#include <iostream>
#include <iterator>
#include <stack>

int evaluate(char*);

int main(int argc, char** argv) {
    char* postfix_expression = argv[1];
    int result = evaluate(postfix_expression);
    std::cout << result << '\n';
}

int evaluate(char* raw_postfix_expression) {
    std::string postfix_expression(raw_postfix_expression);
    std::stack<std::string> stack;

    std::string token = "";
    for (auto it = postfix_expression.begin(); it != postfix_expression.end(); it++) {
        char curr = *it;
        char next = *std::next(it, 1);

        if (curr == '+' || curr == '-' || curr == '*' || curr == '/' || curr == '^') {
            // If '-' represents a negative sign instead of a minus sign
            if (curr == '-' && (next && next != ' ')) {
                token += curr;
                continue;
            }

            int n2 = std::stoi(stack.top());
            stack.pop();
            int n1 = std::stoi(stack.top());
            stack.pop();

            int result;

            switch (curr) {
                case '+':
                    result = n1 + n2;
                    break;
                case '-':
                    result = n1 - n2;
                    break;
                case '*':
                    result = n1 * n2;
                    break;
                case '/':
                    result = std::floor(static_cast<double>(n1) / n2);
                    break;
                case '^':
                    result = std::pow(n1, n2);
                    break;
            }

            stack.push(std::to_string(result));
            continue;
        }

        // Keep adding to the current token as long as curr is a digit (i.e. not an operator or a space)
        if (curr != ' ') {
            token += curr;

            // If the end of the number has been reached, push it to the stack
            if (next == ' ' || !next) {
                stack.push(token);
                token.clear();
                continue;
            }
        }
    }

    return std::stoi(stack.top());
}
