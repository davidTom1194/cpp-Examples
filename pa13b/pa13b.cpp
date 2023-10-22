/// @file pa13b.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 10/17/23
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This program is a programming assignment that demonstrates
/// class concepts learned in Chapter 13 through the use of the Vector
/// class to provide a wide range of use cases..
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
#include <iomanip>          // output formatting
#include <string>           // string formatting
#include <sstream>          // string stream formatting

// template file(s)
#include "Vector.hpp"       // vector template

// Global constant definition(s)
const int COL1 = 18;              // used for column spacing for output
const int COL2 = 6;               // used for column spacing for output
const int COL3 = 4;               // used for column spacing for output


/// -------------------------------------------------------------------------
/// Structure Declaration(s)
/// -------------------------------------------------------------------------


/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
// Input Phase
void readStudentData(Vector<std::string>& student_names,
                     Vector<Vector<int>>& student_scores);

// Processing Phase
int sum(Vector<Vector<int>>& student_scores);
double average(Vector<Vector<int>>& student_scores);
char setGrade(double average);

// Output Phase
void printStatistics(Vector<std::string>& student_names,
                     Vector<Vector<int>>& student_scores);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Variable declarations(s)
    int exitState;                      // tracks the exit code for the process
    exitState = EXIT_SUCCESS;           // set state to successful run

    Vector<std::string> student_names;        // stores student names
    Vector<Vector<int>> student_scores;       // stores student scores

    /* ******* Input Phase ************************************************** */
    readStudentData(student_names, student_scores);

    /* ******* Processing / Output Phase ************************************ */
    printStatistics(student_names, student_scores);

    // cleanup
    student_names.clear();
    student_scores.clear();

    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------


/// Function will populate the student data from an input into an array
/// @param student_names is the names of the students
/// @param student_scores is the score of the students
void readStudentData(Vector<std::string>& student_names,
                     Vector<Vector<int>>& student_scores) {
    std::string line;       // stores line

    // eof loop
    while (std::getline(std::cin, line)) {
        // similar to fstream, use istringstream
        std::istringstream ss(line);

        // set/reset names
        std::string name;

        // iterate and push back characters to student_names
        ss >> name;
        student_names.push_back(name);

        // set/reset scores
        int score;
        Vector<int> scores;

        // iterate and push numbers to scores
        while (ss >> score) {
            scores.push_back(score);
        }
        // push back scores to student_scores
        student_scores.push_back(scores);
    }
}


/// Function will calculate the sum of all elements in the class.
/// @param student_scores are the integers stored to be referenced.
/// @return the sum of all the elements in the class.
int sum(Vector<Vector<int>>& student_scores) {
    int sum = 0;                         // stores the sum of the values

    // obtain a sum from all elements in the Bag
    for (int i = 0; i < static_cast<int>(student_scores.size()); ++i) {
        // iterate through all contents of scores
        for (int j = 0; j < static_cast<int>(student_scores.at(i).size());
             ++j) {
            // add to sum
            sum += student_scores.at(i).at(j);
        }
    }

    return sum;
}


/// Function will calculate the average of all elements in the class.
/// @param student_scores  are the integers stored to be referenced.
/// @return the average of the elements in the class.
/// @note average = sum of all elements / size of all elements
double average(Vector<Vector<int>>& student_scores) {
    double avg = 0;                              // stores the average value
    int totalScores = 0;                         // total number of scores
    // total number of students
    int totalStudents = static_cast<int>(student_scores.size());

    // obtain scores for average
    for (int i = 0; i < totalStudents; ++i) {
        totalScores += student_scores.at(i).size();
    }

    // obtain average, see note in function for equation
    if (student_scores.size() > 0) {
        avg = static_cast<double>(sum(student_scores)) /
              static_cast<double>(totalScores);
    }

    return avg;
}


/// Function will determine the grade and GPA from an average score
/// @param average is an average of student records
/// @return grade is the grade of the report
char setGrade(double average) {
    char grade;                   // sets the grade

    // if statement to determine letter grade
    if (average >= 90) {
        grade = 'A';
    } else if (average >= 80) {
        grade = 'B';
    } else if (average >= 70) {
        grade = 'C';
    } else if (average >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }

    return grade;
}


/// Function will output the computed statistics and contents from the class.
/// @param vector are the integers stored to be referenced.
void printStatistics(Vector<std::string>& student_names,
                     Vector<Vector<int>>& student_scores) {
    // Variable Declaration(s)
    /// COL based on column widths from output
    /// COL1 + (COL2 * (number of scores + 1)) + 1
    const int COL = COL1 + (COL2 * (student_scores.at(0).size() + 1)) + 1;
    const std::string DASH(COL, '-');      // dash prompt for output

    // average score for class
    const double avgScoreTotal = average(student_scores);
    // average grade for class
    const char gradeTotal = setGrade(avgScoreTotal);

    // used to track student grades
    int studentSum;                         // tracks student sum of grades
    double studentAvg;                      // tracks student average of grades
    char studentGrade;                      // tracks student grade

    /* ******* Class Total: output the class averages *********************** */
    // class average output
    std::cout << "Class Average:   "
              << std::fixed
              << std::setprecision(1)
              << avgScoreTotal
              << "  Grade: "
              << gradeTotal
              << std::endl;

    // dashes for output
    std::cout << DASH << std::endl;

    /* ******* Contents: output the vector's contents *********************** */
    // loop through vector and output all values at index
    for (int i = 0; i < static_cast<int>(student_names.size()); ++i) {
        // set sum to 0
        studentSum = 0;
        // output names
        std::cout << std::left
                  << std::setw(COL1)
                  << student_names.at(i);

        for (int j = 0; j < static_cast<int>(student_scores.at(i).size());
             ++j) {
            // output scores
            if (j != static_cast<int>(student_scores.at(i).size() - 1)) {
            std::cout << std::left
                      << std::setw(COL2)
                      << student_scores.at(i).at(j);
            } else {
                // if at last row then set new column width
                std::cout << std::left
                          << std::setw(COL3)
                          << student_scores.at(i).at(j);
            }

            // obtain a sum of scores
            studentSum += student_scores.at(i).at(j);
        }

        // calculate average and grade per student (average = sum / size)
        studentAvg = static_cast<double>(studentSum) /
                     student_scores.at(i).size();
        studentGrade = setGrade(studentAvg);

        // output average and grade
        std::cout << " "
                  << std::left
                  << std::fixed
                  << std::setprecision(1)
                  << studentAvg
                  << " / ";
        std::cout << studentGrade << std::endl;
    }

    // dashes for output
    std::cout<< DASH << std::endl;

}

// EOF: pa13b.cpp
