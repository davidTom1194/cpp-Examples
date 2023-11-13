/// @file pa16.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 11/12/23
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief The programming assignment will implement and analyze various sorting
/// and searching algorithms.  The program is built to run for extended periods
/// while also allowing for output to match a given set of parameters.
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
#include <iomanip>          // output format
#include <vector>           // vectors
#include <random>           // random number generator
#include <algorithm>        // std::sort
#include <chrono>           // benchmark function
#include <cstdint>          // benchmark function

// Global constant definition(s)
const int COL1 = 15;        // column output width

/// -------------------------------------------------------------------------
/// Structure Declaration(s)
/// -------------------------------------------------------------------------


/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
/* ========== Sorting Algorithms =========== */
template <class RandomIt>
void bubble_sort(const RandomIt& first, const RandomIt& last);
template <class RandomIt>
void selection_sort(const RandomIt& first, const RandomIt& last);
template <class RandomIt>
void insertion_sort(const RandomIt& first, const RandomIt& last);

/* ========== Searching Algorithms =========== */
template <class ForwardIt, class T>
ForwardIt seq_search(const ForwardIt& first, const ForwardIt& last,
                     const T& target);
template <class RandomIt, class T>
RandomIt bin_search(RandomIt first, RandomIt last, const T& target);

/* ========== Additional Functions =========== */
template <class Func, class... Args>
int64_t benchmark(const Func& function, Args... args);

// Sort and Search Functions
void executeSortingFunction(const std::vector<int>& tmp,
                            std::vector<int64_t>& times);
void executeSearchFunction(std::vector<int>& tmp,
                           std::vector<int64_t>& times);

// Output Functions
void printHeader(const std::vector<std::string>& PROMPTS);
void printStatistics(size_t size, std::vector<int64_t> times);
void printTail(const std::vector<std::string>& PROMPTS);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Variable declarations(s)
    int exitState;                      // tracks the exit code for the process
    exitState = EXIT_SUCCESS;           // set state to successful run

    // Prompts for header output
    const std::vector<std::string> PROMPTS = { "Data Size", "Bubble",
                                               "Selection", "Insertion",
                                               "std::sort", "Seq Search",
                                               "Bin Search" };

    // Set data sizes for testing
    std::vector<size_t> data_sizes {
        2000, 4000, 8000, 16000, 32000, 64000, 128000
    };

    // Output header for reference during long run times
    printHeader(PROMPTS);

    /* ******* Data Initialization ****************************************** */

    // Create a random number generator using the Mersenne Twister algorithm
    std::random_device rd;   // source of random number
    std::mt19937 gen(rd());  // seed generator with random number
    // set range of values
    std::uniform_int_distribution<> distrib(1, 1'000'000);

    for (const size_t size : data_sizes) {
    // Pre-allocate a vector with the maximum required size (e.g., 128000).

        /* ========= NOTE: VECTOR SIZE IS DIVIDED BY 10 FOR TESTING ========= */
        std::vector<int> vec(size / 10);

        // Fill with uniformly-distributed random values
        for (auto& value : vec) {
            value = distrib(gen);
        }

        // Copy the random vector to a temporary value for reference
        std::vector<int> tmp = vec;

        // Store the times in a vector
        std::vector<int64_t> times;

    /* ******* Processing Phase ********************************************* */

        // Utilize the Sorting Algorithms
        executeSortingFunction(tmp, times);

        // Utilize the Search Algorithms
        executeSearchFunction(tmp, times);

    /* ******* Output Phase ************************************************* */

        // Output index and times and move to next line
        printStatistics(size, times);
        std::cout << std::endl;
}

    // Output tail and any additional notes
    printTail(PROMPTS);

    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------

/* ========== Sorting Algorithms =========== */

/// @brief Sorts the elements in the range [first, last) into ascending order
/// using bubble sort algorithm.
/// @complexity O(n^2)
/// @tparam RandomIT Type of iterator that points to elements in the range.
/// @param first Iterator to first element in the range to sort.
/// @param last Iterator to element following last element in the range to sort.

template <class RandomIt>
void bubble_sort(const RandomIt& first, const RandomIt& last) {
    // Iterate over each element in the range [last, first)
    for (RandomIt it = first; it != last; ++it) {
        // Inner loop - compare elements and swap if needed
        for (RandomIt jt = first; jt != last - (it - first) - 1; ++jt) {
            // If current element is greater than the next, swap
            if (*jt > *(jt + 1)) {
                const auto temp = *jt;        // Temporary variable for swapping
                *jt = *(jt + 1);
                *(jt + 1) = temp;
            }
        }
    }
}

/// @brief Sorts the elements in the range [first, last) into ascending order
/// using selection sort algorithm.
/// @complexity O(n^2)
/// @tparam RandomIT Type of iterator that points to elements in the range.
/// @param first Iterator to first element in the range to sort.
/// @param last Iterator to element following last element in the range to sort.

template <class RandomIt>
void selection_sort(const RandomIt& first, const RandomIt& last) {
    // Iterate over each element in the range [last, first)
    for (RandomIt it = first; it != last; ++it) {
        // sStep a
        // Assume the current position is the smallest
        RandomIt smallestIndex = it;

        // Find the smallest element
        for (RandomIt jt = it + 1; jt != last; ++jt) {
            // If the smaller element is found, update the smallestIndex
            if (*jt < *smallestIndex) {
                smallestIndex = jt;
            }
        }

        // Step b: Swap the smallest element
        const auto temp = *it;        // Temp variable to hold current value
        *it = *smallestIndex;
        *smallestIndex = temp;
    }
}

/// @brief Sorts the elements in the range [first, last) into ascending order
/// using insertion sort algorithm.
/// @complexity O(n^2)
/// @tparam RandomIT Type of iterator that points to elements in the range.
/// @param first Iterator to first element in the range to sort.
/// @param last Iterator to element following last element in the range to sort.

template <class RandomIt>
void insertion_sort(const RandomIt& first, const RandomIt& last){
    // Iterate over each element in the range [last, first)
    for (RandomIt it = first + 1; it != last; ++it) {
        const auto key = *it;   // Current element to be inserted
        RandomIt j = it - 1;    // Initialized variable for previous element

        // Move elements of the sorted sequence
        while (j >= first && *j > key) {
            *(j + 1) = *j;      // Move element to the right
            j--;                // Move to the previous element
        }
        *(j + 1) = key;         // Insert 'key' to correct position
    }
}

/* ========== Searching Algorithms =========== */

/// @brief Performs a sequential serach for a target value within a range.
/// @complexity O(n)
/// @tparam ForwardIT type of forward iterator to elements in the range.
/// @tparam T the type of the value to search for.
/// @param first Iterator to first element in the range to search.
/// @param last Iterator to element following last element in range to search.
/// @param target the value of the element to search for.
/// @return An iterator to the first element in the range that matches the
/// target value, or last if no such element is found.

template <class ForwardIt, class T>
ForwardIt seq_search(const ForwardIt& first, const ForwardIt& last,
                     const T& target) {
    // Variable Declaration(s)
    ForwardIt current = first;              // set temporary variable
    bool found = false;                     // set bool to find target

    // loop front start to finish until found
    while (current < last && !found) {
        if (*current == target) {
            found = true;
        } else {
            current++;
        }
    }

    // return statements using Malik's return
    return found ? current : last;
}

/// @brief Performs a binary search for a target value within a sorted range.
/// @complexity O(log n)
/// @tparam RandomIt Type of random access iterator to elements in the range.
/// @tparam T The type of the value to search for.
/// @param first Iterator to first element in the sorted range to search.
/// @param last Iterator to element following last element in the sorted range
/// to search.
/// @param target The value of the elment to search for.
/// @return An interator to the element that matches the target value, or last
/// if no such element is found.

template <class RandomIt, class T>
RandomIt bin_search(RandomIt first, RandomIt last, const T& target) {
    // Variable Declaration(s)
    bool found = false;         // set bool to find target
    RandomIt mid;               // set mid outside of loop
    RandomIt tmp = last;        // stores last prior to calculations

    while (first < last && !found) {
        // find the middle item
        mid = first + (last - first) / 2;      // calculate the middle

        // Check if the middle item is the target
        if (*mid == target) {
            found = true;
        } else if (*mid > target) {
            last = mid - 1;
        } else {
            first = mid + 1;
        }
    }

    // return last if target not found
    return found ? mid : tmp;
}

/* ========== Additional Functions =========== */

/// @brief Measures the execution time of a function in nanoseconds.
///
/// @details This function template takes a callable and its arguments, executes
/// the callable with the provided arguments, and measures the execution time
/// using high-resolution clock. It returns the duration taken for the function
/// call to execute in nanoseconds.
///
/// This can be used to benchmark algorithms, function calls, or any callable
/// constructs. The function being benchmarked is called exactly once. The
/// precision and accuracy of the benchmark depend on the resolution of the
/// clock on the system where the code is run.
///
/// Example usage:
/// @code
/// auto result = benchmark([](int x){ return x * x; }, 10);
/// std::cout << "Time taken: " << result << " nanoseconds" << std::endl;
/// @endcode
///
/// @tparam Func The type of the callable to be benchmarked.
/// @tparam Args The types of the arguments to pass to the callable.
/// @param function A reference to the callable to be benchmarked.
/// @param args The arguments to pass to the callable.
/// @return The execution time of the callable in nanoseconds as an int64_t.

template <class Func, class... Args>
int64_t benchmark(const Func& function, Args... args) {
    using namespace std::chrono;

    const auto start = high_resolution_clock::now();
    function(args...);
    const auto stop  = high_resolution_clock::now();

    return duration_cast<nanoseconds>(stop - start).count();
}

/// Function will execute the sorting algorithms to benchmark and store their
/// times to completion in a vector.
/// @param tmp Temporary variable used to reference randomly generated values.
/// @param times Vector to store the time to completion for each value.

void executeSortingFunction(const std::vector<int>& tmp,
                            std::vector<int64_t>& times) {
    // loop through all sorting algorithms
    for (size_t i = 0; i < 4; ++i) {
        // Variable Declaration(s)
        std::vector<int> temporary = tmp;       // Copy the vector for sorting
        // Declare time variable outside the switch-case
        int64_t sort_time;

        switch (i) {
            case 0:
                // Bubble Sort: Benchmark and store times
                sort_time = benchmark([&]() {
                    bubble_sort(temporary.begin(), temporary.end());
                });
                break;
            case 1:
                // Selection Sort: Benchmark and store times
                sort_time = benchmark([&]() {
                    selection_sort(temporary.begin(), temporary.end());
                });
                break;
            case 2:
                // Insertion Sort: Benchmark and store times
                sort_time = benchmark([&]() {
                    insertion_sort(temporary.begin(), temporary.end());
                });
                break;
            default:
                // std::sort: Benchmark and store times
                sort_time = benchmark([&]() {
                    std::sort(temporary.begin(), temporary.end());
                });
                break;
        }

        // store the time
        times.push_back(sort_time);
    }
}

/// Function will execute the searching algorithms to benchmark and store their
/// times to completion in a vector.
/// @param tmp Temporary variable used to reference randomly generated values.
/// @param times Vector to store the time to completion for each value.

void executeSearchFunction(std::vector<int>& tmp, std::vector<int64_t>& times) {
    // choose a value guaranteed to be absent from the dataset for worst-case.
    const int not_present = -1;
    bool found;     // Variable to store the result or search functions

    // benchmark Sequential search (worst-case)
    const int64_t seq_search_time = benchmark([&]() {
        found = seq_search(tmp.begin(), tmp.end(), not_present) != tmp.end();
    });

    // for Binary search, the dataset must be sorted
    std::sort(tmp.begin(), tmp.end());

    // benchmark Binary search (worst-case)
    const int64_t bin_search_time = benchmark([&]() {
        found = bin_search(tmp.begin(), tmp.end(), not_present) != tmp.end();
    });

    // Debug statement used to silence linter by using impossible scenario
    // Error: warning 522: highest operation... lacks side effects
    if (found) {
        std::cout << "Unexpectedly found an element." << std::endl;
    }

    // Store the times
    times.push_back(seq_search_time);
    times.push_back(bin_search_time);
}

/// Function will print a header used for the output of the times in their
/// respective tables.
/// @param PROMPTS the table used for size reference.
void printHeader(const std::vector<std::string>& PROMPTS) {
    // set a line of a given size
    const std::string line((COL1 + 2) * PROMPTS.size(), '-');

    /* ========== Header =========== */
    for (size_t i = 0; i < PROMPTS.size(); ++i) {
        std::cout << std::setw(COL1)
                  << PROMPTS[i] << " |";
    }

    // Print line breaker
    std::cout << std::endl;
    std::cout << line << std::endl;
}

/// Function will print the index and times for each value stored in the vector.
void printStatistics(size_t size, std::vector<int64_t> times) {
    /* ========== Index =========== */
    std::cout << std::setw(COL1)
              << size << " |";

    /* ========== Times =========== */
    for (size_t i = 0; i < times.size(); ++i) {
        std::cout << std::setw(COL1)
                  << std::fixed
                  << std::setprecision(9)
                  // convert times in nanoseconds to seconds
                  << static_cast<double>(times[i]) / 1e9
                  << " |";
    }
}

/// Function will print the end of the output based on program specifications.
/// @param PROMPTS the table used for size reference.
void printTail(const std::vector<std::string>& PROMPTS) {
    // Variable Declaration(s)
    const std::string disclaimer = "Time in seconds.";

    // set a line of a given size
    const std::string line((COL1 + 2) * PROMPTS.size(), '-');

    // Print line breaker and disclaimer
    std::cout << line << std::endl;
    std::cout << disclaimer << std::endl;
}

// EOF: pa16.cpp
