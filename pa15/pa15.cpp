/// @file   pa15.cpp
/// @author David Tom
/// @date   November 7, 2023
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This C++ program defines a set of functions and corresponding unit
/// tests using the Catch2 testing framework. The functions cover tasks such
/// as calculating the length of a C-string, finding the sum of array elements,
/// counting occurrences of an element in a vector, generating all possible
/// subsets of a vector, efficiently calculating the power of a number using
/// recursion, and checking if a string is a case-insensitive palindrome using
/// recursion. The program initially provides function stubs, and their
/// implementations are included in comments. The unit tests ensure the
/// correctness of these functions for various scenarios and edge cases.

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

// ============================================================================
// == F U N C T I O N   P R O T O T Y P E S   --   D O   N O T   M U T A T E ==
// ============================================================================

// these are the prototypes copied from your assignment in Canvas
size_t compute_c_string_length(const char* str);
int    sum_of_array_elements(const int* arr, size_t size);
template <class T>
size_t count_occurrences_in_vector(const std::vector<T>& vec, const T& target);
std::vector<std::vector<int>> generate_all_subsets(const std::vector<int>&
                                                   input_set);
double recursive_power(double base, int exponent);
bool   is_palindrome(const std::string& str);

// add prototypes for helper functions you write here, if any
template <class T>
size_t count_occurrences_in_vector_helper(const std::vector<T>& vec, size_t
                                         index, const T& target);
void generate_all_subsets_helper(const std::vector<int>& input_set, size_t
                                 index, std::vector<int>& current,
                                 std::vector<std::vector<int>>& all_subnets);
void reverse_values(std::vector<int>& input);
bool is_palindrome_helper(const std::string& str, size_t left, size_t right);

// ====================s========================================================
// == F U N C T I O N   D E F I N I T I O N S  -- define your functions below =
// ============================================================================

/*
 * I have provided stubs for each of the functions.
 * Remove the // TODO after you define the function, please.
 * (There should be nothing left "to do" when it's time for you turnin!)
 */

/// This function recursively traverses the given C-string until it reaches the
/// null terminator, keeping a count of the characters encountered.
/// @param str Pointer to the C-string whose length is to be computed.
/// @return Length of the C-string.
size_t compute_c_string_length(const char* str) {
    if (*str == 0) {
        // Base case: if the current character is 0, return 0
        return 0;
    } else {
        // General case: return 1 plus the length of the string from the next
        //               character
        return 1 + compute_c_string_length(str + 1);
    }
}

/// Find the sum of all elements in an integer array.
/// @param arr The input integer array.
/// @param size The size of the array.
/// @return The sum of all elements in the array.
int sum_of_array_elements(const int* arr, size_t size) {
    if (size == 0) {
        // Base case: if the array size is 0, there are no elements to sum
        return 0;
    } else {
        // General case: continues until the base case is reached
        return arr[size - 1] + sum_of_array_elements(arr, size - 1);
    }
}

/// Count the number of times a given element appears in a std::vector.
/// @param vec The input std::vector.
/// @param target The element to count.
/// @return The count of occurrences of the target element.
template <class T>
size_t count_occurrences_in_vector(const std::vector<T>& vec, const T& target) {
    if (vec.empty()) {
        // Base case
        return 0;
    }

    return count_occurrences_in_vector_helper(vec, vec.size() - 1, target);
}

/// Generate all possible subsets of a set represented as a std::vector.
/// @param input_set The input set as a std::vector.
/// @return A std::vector of std::vectors containing all possible subsets.
/// @note Reversal of input and output needed to pass judge script.
std::vector<std::vector<int>> generate_all_subsets(const std::vector<int>&
                                                   input_set) {
    // Variable Declaration(s)
    std::vector<std::vector<int>>   all_subsets;    // Final array
    std::vector<int>                current;        // Temp vector
    std::vector<int> input = input_set;             // Make a copy of the input

    // Reverse the input
    reverse_values(input);

    // Helper function
    generate_all_subsets_helper(input, 0, current, all_subsets);

    // Reverse the output
    for (auto& subset : all_subsets) {
        reverse_values(subset);
    }

    return all_subsets;
}

/// Calculate the power of a number (x^n) efficiently using recursion.
/// @param base The base.
/// @param exponent The exponent.
/// @return The result of x^n.
double recursive_power(double base, int exponent) {
    // Base case: any number to the power of 0, is 1
    if (exponent == 0) {
        return 1;
    } else if (exponent > 0) {
        // General case: when the exponent is positive
        return base * recursive_power(base, exponent - 1);
    } else {
        // General case: when the exponent is negative
        // return: 1 / (base * (base ^ (-(exponent + 1))))
        return 1 / recursive_power(base, -(exponent + 1)) / base;
    }
}

/// Check if a given string is a palindrome using recursion.
/// This check is case-insensitive.
/// @param str The input string.
/// @return True if the string is a palindrome, false otherwise.
bool is_palindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }

    return is_palindrome_helper(str, 0, str.size() - 1);
}

// Add function definitions for any helper functions you write below, if any.

/// Helper function for count_occurences_in_vector
/// @param vec The input std::vector.
/// @param index The current index in the vector being checked.
/// @param target The element to count.
/// @return The count of occurrences of the target element.
template <class T>
size_t count_occurrences_in_vector_helper(const std::vector<T>& vec, size_t
                                         index, const T& target) {
    if (index == 0) {
        // Base case: checks if the last element matches the target
        return vec[0] == target ? 1 : 0;
    } else {
        // General case: include the current target and move to the next
        return (vec[index] == target ? 1 : 0) +
                count_occurrences_in_vector_helper(vec, index - 1, target);
    }
}

/// Helper function for generate_all_subsets_helper
/// @param input_set The input set as a std::vector.
/// @param index The current index being processed.
/// @param current The current subset being built.
/// @param all_subsets The collection of all subsets found so far.
void generate_all_subsets_helper(const std::vector<int>& input_set, size_t
                                 index, std::vector<int>& current,
                                 std::vector<std::vector<int>>& all_subsets) {
    if (index == input_set.size()) {
        // Base case: all elements have been considered, add the current
        //            subset to the list
        all_subsets.push_back(current);
        return;
    }

    // General case: Include the current element and move to the next
    generate_all_subsets_helper(input_set, index + 1, current, all_subsets);

    // Include the current element and move to the next
    current.push_back(input_set[index]);
    generate_all_subsets_helper(input_set, index + 1, current, all_subsets);

    // Backtrack: remove the current element before going up the recursive
    current.pop_back();
}

/// Helper function for generate_all_subsets
/// @param input_set The input set as a std::vector.
void reverse_values(std::vector<int>& input_set) {
    // Reverse the values
    int temp;                                    // temporary swapping variable
    int i = 0;                                         // tracks lowest index
    int j = static_cast<int>(input_set.size()) - 1;    // tracks highest index

    // Swap values
    while (i < j) {
        temp = input_set[i];
        input_set[i] = input_set[j];
        input_set[j] = temp;
        ++i;
        --j;
    }
}

/// Helper function for is_palindrome
/// @param str The input string.
/// @param left The left index of the substring to check.
/// @param right The right index of the substring to check.
/// @return True if the substring is a palindrome, false otherwise.
bool is_palindrome_helper(const std::string& str, size_t left, size_t right) {
    // Base case: if there is only one or no characters, its a palindrome
    if (left >= right) {
        return true;
    }

    // Compare the characters, ignoring case.
    if (std::tolower(str[left]) != std::tolower(str[right])) {
        return false;     // Characters do not match.
    }

    // Move towards the middle and recurse.
    return is_palindrome_helper(str, left + 1, right - 1);
}

// ============================================================================
// ========= U N I T   T E S T S   --   D O   N O T   M U T A T E =============
// ============================================================================

TEST_CASE("Function 1: Compute the length of a C-string", "[compute_c_string_length]") {

    SECTION("Basic tests") {
        REQUIRE(compute_c_string_length("Hello") == 5);
        REQUIRE(compute_c_string_length("World!") == 6);
    }

    SECTION("Empty string") {
        REQUIRE(compute_c_string_length("") == 0);
    }

    SECTION("Single character strings") {
        REQUIRE(compute_c_string_length("A") == 1);
    }

    SECTION("Longer strings") {
        REQUIRE(compute_c_string_length("This is a relatively longer string for testing.") == 47);
    }

    SECTION("Strings with spaces and special characters") {
        REQUIRE(compute_c_string_length("Hello, World!") == 13);
        REQUIRE(compute_c_string_length("12345 67890") == 11);
        REQUIRE(compute_c_string_length("!@#$%^&*()") == 10);
    }
}

TEST_CASE("Function 2: Sum of Array Elements", "[sum_of_array_elements]") {
    int arr1[] = {1, 2, 3, 4, 5};
    CHECK(sum_of_array_elements(arr1, 5) == 15);

    int arr2[] = {0};
    CHECK(sum_of_array_elements(arr2, 1) == 0);

    int arr3[] = {-1, 2, -3, 4};
    CHECK(sum_of_array_elements(arr3, 4) == 2);
}

TEST_CASE("Function 3: Count Occurrences in a Vector", "[count_occurrences_in_vector]") {
    CHECK(count_occurrences_in_vector(std::vector<int>{1, 2, 3, 1, 1, 4, 5}, 1) == 3);
    CHECK(count_occurrences_in_vector(std::vector<int>{}, 1) == 0);
    CHECK(count_occurrences_in_vector(std::vector<int>{1, 2, 3}, 4) == 0);
}

TEST_CASE("Function 4: Generate All Subsets", "[generate_all_subsets]") {
    auto result = generate_all_subsets({1, 2, 3});
    std::vector<std::vector<int>> expected =
        {{}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}};
;
    CHECK(result == expected);

    result = generate_all_subsets({});

    expected = {{}};
    CHECK(result == expected);
}

TEST_CASE("Function 5: Recursive Power Function", "[recursive_power]") {
    CHECK(recursive_power(2, 3) == 8);
    CHECK(recursive_power(5, 0) == 1);
    CHECK(recursive_power(0, 5) == 0);
    CHECK(recursive_power(3, -1) == Approx(1.0/3.0));
}

TEST_CASE("Function 6: Check for Palindrome", "[is_palindrome]") {
    CHECK(is_palindrome("radar") == true);
    CHECK(is_palindrome("hello") == false);
    CHECK(is_palindrome("") == true);
    CHECK(is_palindrome("A") == true);
    CHECK(is_palindrome("RaDaR") == true);
}

/* EOF: pa15.cpp */

