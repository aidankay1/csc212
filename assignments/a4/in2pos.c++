/*
4A. Transforming Infix to Postfix notation
*/

#include <iostream>
#include <iterator>
#include <stack>

std::string InfixToPostfix(char*);
bool HasEqualOrGreaterPrecedence(char, char);

int main(int argc, char** argv) {
    char* infix_expression = argv[1];
    std::string postfix_expression = InfixToPostfix(infix_expression);
    std::cout << postfix_expression << '\n';
}

// Convert infix notation to postfix notation
std::string InfixToPostfix(char* raw_infix_expression) {
    std::string infix_expression(raw_infix_expression);
    std::string postfix_expression = "";
    std::stack<char> stack;

    for (auto it = infix_expression.begin(); it != infix_expression.end(); it++) {
        const char ch = *it;

        if (ch == ' ') continue;

        if (ch == '(') {
            stack.push(ch);
            continue;
        }

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            if (ch == '-') {
                const char next = *std::next(it, 1);
                // Prevents interpreting a negative sign as a minus sign
                if (next != ' ') {
                    postfix_expression += ch;
                    continue;
                }
            }

            while (!stack.empty() && HasEqualOrGreaterPrecedence(ch, stack.top())) {
                postfix_expression += stack.top();
                postfix_expression += ' ';
                stack.pop();
            }

            stack.push(ch);
            continue;
        }

        if (ch == ')') {
            while (stack.top() != '(') {
                postfix_expression += stack.top();
                postfix_expression += ' ';
                stack.pop();
            }

            stack.pop();
            continue;
        }

        // Any character that is not a parenthesis or an operator is a number, so just add it to the postfix expression
        postfix_expression += ch;

        const char next = *std::next(it, 1);
        // Add a space only if at the end of the current number or the end of the entire infix expression
        if (next == ' ' || !next) postfix_expression += ' ';
    }

    // Once end of expression is reached, write remaining operators
    while (!stack.empty()) {
        postfix_expression += stack.top();
        postfix_expression += ' ';
        stack.pop();
    }

    return postfix_expression;
}

// Check order of operations
bool HasEqualOrGreaterPrecedence(char current, char next) {
    // Parentheses do not count as operators
    if (next == '(' || next == ')') return false;
    if (current == '^') return false;
    if (current == '*' || current == '/') {
        if (next == '^' || next == '*' || next == '/') return true;
        return false;
    }
    return true;
}
