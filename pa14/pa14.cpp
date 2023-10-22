/// @file pa14.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 10/24/23
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This program is a programming assignment that counts the number of
/// words obtained from an input and outputs the count of the words in
/// lexigraphical order.
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
#include <iostream>         // input/output

// template file(s)
#include "Vector.hpp"       // vector template

// Global constant definition(s)


/// -------------------------------------------------------------------------
/// Structure Declaration(s)
/// -------------------------------------------------------------------------

// used to store and count the frequency of words
struct WordFreq {
    std::string word;
    int frequency = 0;

};  // end struct WordFreq

/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
// Input Phase
std::string processWord(const std::string& word);

// Processing Phase
void verify(Vector<WordFreq>& counter, const std::string& word);
void selectionSort(Vector<WordFreq>& counter);

// Output Phase
std::ostream& operator<<(std::ostream& os, const Vector<WordFreq>& counter);
void printStatistics(const Vector<WordFreq>& counter);


/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Variable declarations(s)
    int exitState;                      // tracks the exit code for the process
    exitState = EXIT_SUCCESS;           // set state to successful run

    Vector<WordFreq> counter;           // set a struct to count
    std::string word;                   // stores the words as they are input

    /* ******* Input Phase ************************************************** */

    // loop input to find or store words
    while (std::cin >> word) {

        // process words for ordering and identification
        word = processWord(word);

    /* ******* Processing Phase ********************************************* */

        // verify word is new or not
        verify(counter, word);
    }

    // sort by alphabetical order and frequency count
    selectionSort(counter);

    /* ******* Output Phase ************************************************* */

    // output values
    printStatistics(counter);

    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------


/// Function will process words and convert them to lowercase.
/// @param word is the word being obtained and processed
/// @return result is the normalized word
std::string processWord(const std::string& word) {
    // Variable Declaration(s)
    std::string result;              // stores the normalized word
    size_t start = 0;                // tracks index of character in word
    // tracks index for end of word for arrays: (end = length - 1)
    size_t end = static_cast<size_t>(word.length() - 1);

    // loop through any repeating special characters for omission
    for (size_t i = 0; i < word.length() - 1; ++i) {

        // Start: verify index and word length & if not alnum at start
        if (start < word.length() && !isalnum(word[start])) {
            start++;
        }

        // End: verify index and word length & if not alnum at end
        if (end > start && !isalnum(word[end])) {
            end--;
        }
    }

    // Word: loop through remaining characters to add to string
    for (size_t i = start; i <= end; i++) {
        result += tolower(word[i]);
    }

    return result;
}


/// Function will verify the word is either new or has existed previously
/// @param counter is a dynamic vector/struct to track words and counts
/// @param word is a specific word to check in the vector
void verify(Vector<WordFreq>& counter, const std::string& word) {
    // Variable Declaration(s)
    bool found = false;                     // tracks if values have been found

    // loop throug each word to verify if it exists in the vector
    for (size_t i = 0; i < counter.size(); ++i) {

        if (counter[i].word == word) {
            // verify word exists and add to frequency
            counter[i].frequency++;
            found = true;
            i     = counter.size();             // used to break for loop
        }
    }

    // if word is not found and is not a special character then add
    if (!found && isalnum(word[0])) {
        counter.push_back({word, 1});
    }

}


/// Function will implement Chapter 8's (Malik - C++) selection sort algorithm
/// @param counter is a dynamic vector/struct to track words
/// @note Function based on programming assignment 8's sortArray fn
void selectionSort(Vector<WordFreq>& counter) {
    // Variable Declaration(s)
    size_t smallestIndex;               // tracks smallest index in array

    // for loop through words and frequency
    for (size_t i = 0; i < static_cast<size_t>(counter.size() - 1); i++) {
        smallestIndex = i;

        for (size_t j = i + 1; j < static_cast<size_t>(counter.size()); j++) {
            /* modified selection sort: frequency and lexigraphical sorting */
            // primary: sort by frequency count
            if (counter[j].frequency >  counter[smallestIndex].frequency ||
            // secondary: if frequency is equal, then lexigraphically order
               (counter[j].frequency == counter[smallestIndex].frequency &&
                counter[j].word      <  counter[smallestIndex].word)) {
                    smallestIndex = j;
            }
        }

        // set/reset tmp struct to store data
        const WordFreq tmp     = counter[smallestIndex];
        counter[smallestIndex] = counter[i];
        counter[i]             = tmp;
    }

}


/// Function will output values to ostream for further output
/// @param os is the ostream variable used for calling
/// @param counter is the dynamic vector/struct to track words
std::ostream& operator<<(std::ostream& os, const Vector<WordFreq>& counter) {
    // loop through struct and output word and frequency at index
    for (const auto& wf : counter) {
        os << wf.word
           << ": "
           << wf.frequency
           << std::endl;
    }

    return os;
}


/// Function will output the word and its respective frequency
/// @param counter is a dynamic vector/struct to track words
void printStatistics(const Vector<WordFreq>& counter) {
    // loop through struct and output word and frequency at index
    std::cout << counter;

}

// EOF: pa14.cpp
