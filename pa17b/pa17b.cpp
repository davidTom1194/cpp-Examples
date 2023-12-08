/// @file pa16.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 11/29/23
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief The programming assignment will implement and analyze various linked
/// lists to process a broken mechanical keyboard's input.  The program is
/// built to run for extended inputs while also allowing for output to match a
/// given set of parameters.
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
#include <iostream>
#include <string>
#include "LList.hpp"        // Include the custom linked list template file

/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
void processInput(const std::string& input, LList<int>& output);
void printList(const LList<int>& lst);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Variable Declaration(s)
    std::string inputLine;                  // Stores input

    // Read lines from standard input
    while (getline(std::cin, inputLine)) {
        LList<int> output;                  // Create an output list
        processInput(inputLine, output);    // Process the input line
        printList(output);                  // Print the processed list
    }

    return EXIT_SUCCESS;
}

/// @brief Processes the input string and populates the output linked list
/// @param input The input list to be processed
/// @param output The processed output list
void processInput(const std::string& input, LList<int>& output) {
    auto currentPos = output.begin();       // Current insertion position
    int number = 0;                         // Current number being processed
    bool isNumber = false;    // Flag to check if a number is being processed

    for (const char ch : input) {
        // Handle different characters in the input
        if (ch == ' ') {
            // Check spaces (' ')
            if (isNumber) {
                output.insert(currentPos, number);
                isNumber = false;
            }
        } else if (ch == '[') {
            // Check for bracket ('[')
            currentPos = output.begin();
            if (isNumber) {
                output.insert(currentPos, number);
                isNumber = false;
            }
        } else if (ch == ']') {
            // Check for bracket (']')
            currentPos = output.end();
            if (isNumber) {
                output.insert(currentPos, number);
                isNumber = false;
            }
        } else {
            if (!isNumber) {
                number = 0;
                isNumber = true;
            }
            /// Convert digits to integers (ch - '0')
            /// Shift the number to the left by one (number * 10)
            number = number * 10 + (ch - '0');
        }
    }

    // Insert the last number if present
    if (isNumber) {
        output.insert(currentPos, number);
    }
}

/// @brief Function prints the elements of the linked list
/// @param lst is the linked list storing the processed output
void printList(const LList<int>& lst) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it;
        // Add a space after each element except the last
        if (std::next(it) != lst.end()) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;         // End the line with a newline character
}
