/// @file pa13a.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 10/10/23
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This program is a programming assignment that demonstrates
/// class concepts learned in Chapter 13 through the use of the Vector
/// class to provide a wide range of use cases.
///
/// @note People who helped me: N/A
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// preprocessor directives
// library includes
#include <iostream>
#include <string>

// header file(s)
#include "Vector.h"

// Global constant definition(s)


/// -------------------------------------------------------------------------
/// Structure Declaration(s)
/// -------------------------------------------------------------------------


/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
// Input Phase
std::istream& operator>>(std::istream& is, Vector& vector);

// Processing Phase
bool palindrome(const Vector& vector);
void nucleotideCount(const Vector& vector);

// Output Phase
std::ostream& operator<<(std::ostream& os, const Vector& vector);
void printStatistics(const Vector& vector);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Variable declarations(s)
    int exitState;                      // tracks the exit code for the process
    exitState = EXIT_SUCCESS;           // set state to successful run
    Vector vector;                      // constructs object from class

    /* ******* Input Phase ************************************************** */
    // input values using overload stream insertion
    std::cin >> vector;

    // verifiy input and assign exitState if error occurs
    for (Vector::value_type const c : vector) {
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
            exitState = EXIT_FAILURE;
        }
    }

    /* ******* Processing / Output Phase ************************************ */
    // if exitState not a success output error message
    if (exitState != EXIT_SUCCESS) {
        std::cout << "Error: Invalid Character Detected" << std::endl;
    } else {
        // proceed with processing and outputs
        printStatistics(vector);
    }

    // cleanup memory
    vector.clear();

    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------


/// Function will determine if the input is a palindrome.
/// @param vector are the integers stored to be referenced.
/// @return palindromeState The state of the palindrome.
bool palindrome(const Vector& vector) {
    bool boolState = true;                            // tracks boolState status
    Vector::size_type const length = vector.size();   // tracks vector length

    // loop and verify if start and end are equal
    for (Vector::size_type i = 0; i < length / 2; ++i) {
        /// verify if the values are the same at:
        /// start (i = 0)
        /// end (length - ((i = 0) - 1)))
        if (vector.at(i) != vector.at(length - i - 1)) {
            boolState = false;
        }
    }

    return boolState;
}


/// Function will count the number of nucleotides based on the input
/// @param vector are the elements stored to be referenced.
void nucleotideCount(const Vector& vector) {
    // Variable Declaration(s)
    Vector::size_type countA = 0;               // counts number of nucleotides
    Vector::size_type countC = 0;               // counts number of nucleotides
    Vector::size_type countG = 0;               // counts number of nucleotides
    Vector::size_type countT = 0;               // counts number of nucleotides

    // loop through vector and count nucleotides
    for (Vector::value_type const counter : vector) {
        switch (counter) {
        case 'A':
            countA++;
            break;
        case 'C':
            countC++;
            break;
        case 'G':
            countG++;
            break;
        case 'T':
            countT++;
            break;
        default:
            break;
        }
    }

    // output number of nucleotides
    std::cout << "Nucleotide Counts: "
              << "A=" << countA
              << " C=" << countC
              << " G=" << countG
              << " T=" << countT
              << std::endl;
}


/// Function will implement the overloaded (>>) operator to input values at
/// a given index.
///
/// @param is Is the input stream variable.
/// @param vector Is the dynamic array.
/// @return is Is the value at the index inserted into istream.
std::istream& operator>>(std::istream& is, Vector& vector) {
    std::string input;                  // stores cin input value(s)

    // receive input as a string
    is >> input;

    // loop through vector and push back all values
    for (Vector::value_type const c : input) {
        vector.push_back(c);
    }

    return is;
}


/// Function will implement the overloaded (<<) operator to output values at
/// a given index.
///
/// @param os Is the output stream variable.
/// @param vector Is the dynamic array.
/// @return os Is the value at the index inserted into ostream.
std::ostream& operator<<(std::ostream& os, const Vector& vector) {
    // loop through vector and output all values at index
    for (Vector::size_type i = 0; i < vector.size(); ++i) {
        os << vector.at(i);
    }

    return os;
}


/// Function will output the computed statistics and contents from the class.
/// @param vector are the integers stored to be referenced.
void printStatistics(const Vector& vector) {
    // Variable Declaration(s)
    Vector::size_type i;                    // index tracker

    /* ******* Contents: output the original sequence class's contents ****** */
    std::cout << "Original Sequence: ";

    // output values with overload stream extraction
    std::cout << vector << std::endl;

    /* ******* Contents: output the reverse sequence class's contents ******* */
    std::cout << "Reversed Sequence: ";
    // loop through vector
    for (i = vector.size(); i > 0; --i) {
        std::cout << vector.at(i - 1);
    }

    // end line
    std::cout << std::endl;

    /* ******* Palindrome: determine if the sequence is a palindrome ******** */
    if (!(palindrome(vector))) {
        std::cout << "Not Palindromic" << std::endl;
    } else {
        std::cout << "Palindromic" << std::endl;
    }

    /* ********** Nucleotide Counter: output the count of the *************** */
    /* ********** nucleotides contents ************************************** */
    nucleotideCount(vector);

}


// EOF: pa13a.cpp
