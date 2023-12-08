/// @file pa18.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 12/5/23
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief The programming assignment will implement and analyze various integer
/// expressions to process infix expressions and convert to postfix notation to
/// then compute its value.
///
/// @note People who helped me: N/A
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

// Preprocessor directives
#include <iostream>         // Input/Output stream
#include <string>           // std::string use
#include <sstream>          // String streams
#include <stdexcept>        // Throw exceptions
#include "Stack.hpp"        // Include the custom stack template file

/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
// Required Functions
std::string infix2postfix(const std::string& infix);
int eval_postfix(const std::string& postfix);

// Helper Functions
int precedence(char op);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Variable Declaration(s)
    int exitState = EXIT_SUCCESS;       // tracks the return status
    int caseNumber = 1;                 // tracks the case number
    std::string infix;                  // declare infix string
    std::string postfix;                // declare postfix string
    int result;                         // tracks the result of the expression

    // Input Phase
    while (std::getline(std::cin, infix)) {
        // Convert infix to postfix
        postfix = infix2postfix(infix);

        // Processing Phase
        // Evaluate the postfix expression
        result = eval_postfix(postfix);

        // Output Phase
        std::cout << "Case " << caseNumber << ": " << result << std::endl;

        // Increment caseNumber
        caseNumber++;
    }

    return exitState;
}

/// @brief Converts an Infix expression to a Postfix expression.
///
/// This function takes an Infix expression as input and converts it to
/// its equivalent Postfix expression using a stack-based approach. The
/// Infix expression should only contain operands, arithmetic operators
/// (+, -, *, /), and parentheses. Operands and operators in the input
/// string must be separated by at least one space.
///
/// @param infix The string containing the Infix expression.
/// @return std::string A string containing the Postfix expression.
///
/// @note The function assumes that the Infix expression is well-formed
/// and valid. Error handling for invalid expressions is not implemented.
///
/// Example Usage:
/// @code
///   std::string infix = "2 + 3 * 4";
///   std::string postfix = infix2postfix(infix);
///   std::cout << "Postfix: " << postfix << std::endl; // Outputs: 2 3 4 * +
/// @endcode

std::string infix2postfix(const std::string& infix) {
    Stack<char> stack;              // Stores stack values
    std::stringstream postfix;      // Stores postfix values
    std::stringstream ss(infix);    // Tracks infix values for processing
    std::string token;              // String to track infix value
    bool expectOperand = true;      // Tracks negative values

    while (ss >> token) {
        const char c = token[0];

        // Check if token is an operand or a negative number
        if (isdigit(c) || (expectOperand && c == '-'
            && token.size() > 1)) {
            // Adds operand (including negatives) to postfix expression
            postfix << token << " ";
            // After an operand, expect an operator
            expectOperand = false;
        } else if (c == '(') {  // Open parenthesis
            // Push onto the stack and expect an operand
            stack.push(c);
            expectOperand = true;
        } else if (c == ')') {  // Close parenthesis
            // Pop operators until parenthesis is encountered
            while (!stack.empty() && stack.top() != '(') {
                postfix << stack.top() << " ";
                stack.pop();
            }
            // Pop the open parenthesis from the stack
            if (!stack.empty()) {
                stack.pop();  // Pop the '(' from the stack
            }
            // Expect an operator
            expectOperand = true;
        // If the token is an operator
        } else {
            // Pop operators form the stack comparing precedence
            while (!stack.empty() && precedence(c) <= precedence(stack.top())) {
                postfix << stack.top() << " ";
                stack.pop();
            }
            // Push the current operator onto the stack
            stack.push(c);
            // After an operator, an operand is expected
            expectOperand = true;
        }
    }

    // Pop all remaining operators from the stack
    while (!stack.empty()) {
        postfix << stack.top() << " ";
        stack.pop();
    }

    // Return the postfix expression
    return postfix.str();
}

/// @brief Evaluates a Postfix expression and returns its value.
///
/// This function takes a Postfix expression as input and evaluates it to
/// return its integer value. The Postfix expression should contain only
/// integer operands and standard arithmetic operators (+, -, *, /). Each
/// operand and operator in the input string must be separated by at least
/// one space.
///
/// @param postfix The string containing the Postfix expression.
/// @return int The integer value of the evaluated Postfix expression.
///
/// @note The function assumes that the Postfix expression is well-formed
/// and valid. Error handling for invalid expressions, such as division by
/// zero or malformed inputs, is not implemented.
///
/// Example Usage:
/// @code
///   std::string postfix = "2 3 4 * +";
///   int result = eval_postfix(postfix);
///   std::cout << "Result: " << result << std::endl; // Outputs: 14
/// @endcode

int eval_postfix(const std::string& postfix) {
    Stack<int> stack;                   // Stores stack values
    std::stringstream ss(postfix);      // Tracks postfix string values
    std::string token;                  // String to track postfix values

    // Process each token in the postfix expression
    while (ss >> token) {
        // Check if the token is a digit or an operand, including negatives
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            // Operand: Push it onto the stack
            const int num = std::stoi(token);
            stack.push(num);
        } else {
            // Operator: Pop two elements from stack, apply the operator,
            // and push the result back.
            if (stack.size() < 2) {
                throw std::invalid_argument("Invalid postfix expression");
            }

            // Pop the top two operands from the stack
            const int op2 = stack.top(); stack.pop();
            const int op1 = stack.top(); stack.pop();

            // Apply the operator to the operands and push result to stack
            switch (token[0]) {
                case '+':
                    stack.push(op1 + op2);
                    break;
                case '-':
                    stack.push(op1 - op2);
                    break;
                case '*':
                    stack.push(op1 * op2);
                    break;
                case '/':
                    // Check for division by 0
                    if (op2 == 0) {
                        throw std::invalid_argument(
                        "Division by zero encountered");
                    }
                    stack.push(op1 / op2);
                    break;
                case '%':
                    // Check for modulus by 0
                    if (op2 == 0) {
                        throw std::invalid_argument(
                        "Modulus by zero encountered");
                    }
                    stack.push(op1 % op2);
                    break;
                default:
                    throw std::invalid_argument("Invalid operator encountered");
                    break;
            }
        }
    }

    // Check if there is more than one item in the stack
    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression");
    }

    // The final result of the expression is the remaining item on the stack
    return stack.top();
}

/* ========== Helper Functions ========= */

/// @brief Function returns the precedence of operators.
///
/// This function analyzes the operators within an expression and evaluates
/// the precedence.  The expressions should contain operands and standard
/// arithmetic operators to be evaluated (including the modulus ('%') operator).
/// Each operator will be seperated by at least one space.
///
/// @param op The operator in the expression for evaluatioin
/// @return prec The precedence value assigned following the processing.
///
/// @note The function assumes there are only 5 operators ('+', '-', '*', '/',
/// and '%') and automatically assigns any values outside the parameters to a
/// negative precedence.  All error handling for expressions is handled
/// elsewhere.
///
/// Example Usage:
/// @code
///   char op1 = "*"
///   char op2 = "+";
///   if (precedence(op1) < precedence(op2)) {
///       std::cout << "false" << std::endl;
///   }
/// @endcode

int precedence(char op) {
    // Default precedence is 0
    int prec = 0;

    // Operators '+' and '-' have lower precedence
    if (op == '+' || op == '-') {
        prec = 1;
    // Operators '*', '/', and '%' have higher precedence
    } else if (op == '*' || op == '/' || op == '%') {
        prec = 2;
    // Any other unexpected operators have a negative precedence
    } else {
        prec = -1;
    }

    // Return the precedence value
    return prec;
}
