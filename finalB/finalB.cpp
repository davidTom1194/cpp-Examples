/// @file finalB.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 8/7/23
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This programming assignment demonstrates the ability to utilize
///        previous examples and solutions to synthesize new code to identify
///        the highest and lowest scores in the class as well as the average.
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
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// Global constant definition(s)
const int SCORE_CNT = 5;            // the number of scores
const int STUDENT_CNT = 10;         // the number of students
const int COL1 = 10;                // 1st column width of tabulated output
const int COL2 = 8;                 // 2nd column width of tabulated output
const int COL3 = 10;                // 3rd column width of tabulated output
const int COL4 = 5;                 // 4th column width of tabulated output

/// -------------------------------------------------------------------------
/// Structure Declaration(s)
/// -------------------------------------------------------------------------

struct student_t {
    string name;                    // stores the name of the student
    int scores[SCORE_CNT] = {0};    // stores the scores as an array
    double average;                 // stores the average of the student
    char grade;                     // stores the grade of the student
};  // end struct student_t

/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------

/* *******  Optional Function(s) ***************************************** */

// optional letter grade function
char score2LetterGrade(double sAverage);

// optional output functions
void printSepLine();
void printHeader();
void printRow(const student_t students[], const int row);
void printClassAverage(const double sum);
void printBestPerformance(const student_t students[]);
void printPoorestPerformance(const student_t students[]);

// optional index identifying functions
int findMaxAve(const student_t students[]);
int findMinAve(const student_t students[]);

/* ******* Required Function(s) ****************************************** */

// Input Phase
string getFilename();
bool readData(const string& fn, student_t students[]);

// Processing Phase
void calculateRecordAverages(student_t students[]);
void recordAverages2LetterGrades(student_t students[]);

// Output Phase
void printReport(const student_t students[]);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Variable Declaration(s)
    int exitState;                      // tracks the exit code for the process
    exitState = EXIT_SUCCESS;           // set state to successful run

    string fn;                          // file name for the student data
    student_t records[STUDENT_CNT];     // array of student records

    /* ******* Input Phase *********************************************** */
    // obtain a file name for the program
    fn = getFilename();

    /* ******* Processing Phase ****************************************** */
    // verify the file exists and has data
    if (readData(fn, records)) {
        // obtain averages from the scores
        calculateRecordAverages(records);

        // obtain a grade from the scores
        recordAverages2LetterGrades(records);

        /* ******* Output Phase ****************************************** */
        // print the report to the screen
        printReport(records);
    } else {
        // if no file exists and has no data then return a fail state
        exitState = EXIT_FAILURE;
    }

    // return exitState
    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------

/* *********** Optional Functions **************************************** */

/// Function will write a seperation line to be used by the output phase
/// Called by printReport(), printBestPefromance(), printPoorestPerformance()
void printSepLine() {
    // write a seperation line that matches the expected output
    for (int i = 0; i < 69; i++) {
        cout << '-';
    }
    cout << endl;
}

/// Function will write a header to be used by the output phase
/// Called by printReport(), printBestPeformance(), printPoorestPerformance()
void printHeader() {
    // constant definition(s)
    const string INDENT1 = "   ";   // used for indentations
    const string INDENT2 = "  ";    // used for indentations

    // write the header details describing the tabulated data
    cout << setfill(' ');           // setfill empty space
    cout << left                    // set the name data to the left
    << setw(COL1) << "Name"
    << right                        // set the remainding data to the right
    << setw(COL2) << "Test 1"
    << setw(COL2) << "Test 2"
    << setw(COL2) << "Test 3"
    << setw(COL2) << "Test 4"
    << setw(COL2) << "Test 5"
    << setw(COL3) << "Average"
    << INDENT1
    << setw(COL4) << "Grade"
    << endl;

    // write the a seperation line that matches above header details
    cout << setfill('-');           // setfill hyphens
    cout << right                   // set the output to the right
    << setw(COL1) << INDENT1
    << left                         // set the remainding output tot he left
    << setw(COL2) << INDENT2
    << setw(COL2) << INDENT2
    << setw(COL2) << INDENT2
    << setw(COL2) << INDENT2
    << setw(COL2) << INDENT2
    << setw(COL3) << INDENT1
    << setw(COL4 + 3) << INDENT1
    << endl;
}

/// Function will write to the screen the students names, scores, and grades
/// Called by printReport(), printBestPerformance(), printPoorestPerformance()
/// @param [in] students is an array of student scores
/// @param row is the array index for the record to be printed
void printRow(const student_t students[], const int row) {
    // write the student's name based on the expected output
    cout << setfill(' ');           // setfill empty space
    cout << left                    // set the output to the left
    << setw(COL1)
    << students[row].name;

    // write the individual scores based on the expected output
    for (int i = 0; i < SCORE_CNT; ++i) {
        cout << right               // set the output to the right
        << setw(COL2)
        << students[row].scores[i];
    }

    // write the average score and the grade
    cout << setw(COL3) << students[row].average
    << right                        // set the output to the right
    << setw(COL4 + 1) << students[row].grade
    << endl;
}

/// Function will obtain the grade for a student based on their average grade
/// Called by recordAverages2LetterGrades()
/// @param sAverage is the student's average score
/// @return the letter grade
char score2LetterGrade(double sAverage) {
    // variable definition(s)
    char grade;                   // stores the grade of the student

    // assign the letter grade based on the student's average score
    if (sAverage >= 90) {
        grade = 'A';
    } else if (sAverage >= 80) {
        grade = 'B';
    } else if (sAverage >= 70) {
        grade = 'C';
    } else if (sAverage >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }

    return grade;
}

/// Function will print the class average
/// Called by printReport()
/// @param sum is the total class score
void printClassAverage(const double sum) {
    // constant definition(s)
    const int AVG_COL = COL1 + (COL2 * 5);   // column length for the averages
    const string INDENT = "  ";              // indent for output of averages

    // variable definition(s)
    double classAverage;                     // stores the total class average

    // average = sum / (students * number of tests)
    classAverage = static_cast<double>(sum) / (STUDENT_CNT * SCORE_CNT);

    // set decimal prescision to 2
    cout << fixed << showpoint << setprecision(2);
    cout << setfill(' ')                     // setfill empty space
    << setw(AVG_COL + 3)
    << "Class average: " << INDENT           // format output for averages
    << classAverage                          // write the class average
    << endl;
}

/// Function will determine the best performer based on the max average
/// Called by printBestPerformance()
/// @param [in] students is an array of student scores
/// @return is index of the best average
int findMaxAve(const student_t students[]) {
    // variable definition(s)
    int record = 0;          // current record from file
    double maxAve;           // stores the max average value
    int index = 0;           // stores the index of the max average

    // store the initial average value to compare against
    maxAve = students[0].average;

    // loop through the averages from each student to find the largest value
    while (record < STUDENT_CNT) {
        // compare the value against the max average
        if (students[record].average >= maxAve) {
            maxAve = students[record].average;
            index = record;
        }
        record++;
    }

    return index;
}

/// Function will determine the poorest performer based on the min average
/// Called by printPoorestPerformance()
/// @param [in] students is an array of student scores
/// @return is index of the poorest average
int findMinAve(const student_t students[]) {
    // variable definition(s)
    int record = 0;          // current record from file
    double minAve;           // stores the min average value
    int index = 0;           // stores the index value

    // store the initial average value to compare against
    minAve = students[0].average;

    // loop through the averages from each student to find the smallest value
    while (record < STUDENT_CNT) {
        // compare the value against the min average
        if (students[record].average <= minAve) {
            minAve = students[record].average;
            index = record;
        }
        record++;
    }

    return index;
}

/// Function will write the best performing student to the screen
/// Called by printReport()
/// @param [in] students is an array of student scores
void printBestPerformance(const student_t students[]) {
    // variable definition(s)
    int i;                        // stores the index for the best performer

    // use the function to obtain the index of the highest scoring student
    i = findMaxAve(students);

    // write an appropriate header
    cout << "Best Performance:" << endl;
    printSepLine();
    printHeader();

    // output the student's information to the screen
    printRow(students, i);

    // write an appropriate tail
    printSepLine();
    cout << endl;
}

/// Function will write the poorest performing student to the screen
/// Called by printReport()
/// @param [in] students is an array of student scores
void printPoorestPerformance(const student_t students[]) {
    // variable definition(s)
    int i;                        // stores the index for the best performer

    // use the function to obtain the index of the lowest scoring student
    i = findMinAve(students);

    // write an appropriate header
    cout << "Poorest Performance:" << endl;
    printSepLine();
    printHeader();

    // output the student's information to the screen
    printRow(students, i);

    // write an appropriate tail
    printSepLine();
    cout << endl;
}

/* *********** Input Phase *********************************************** */

/// Function will obtain a file name from user input
/// Called by main()
/// @return the name of the data file
string getFilename() {
    // variable definition(s)
    string fn;                          // stores the file name

    // prompt the user and obtain a file name
    cout << "Enter the name of your data file: " << endl;
    cin >> fn;

    return fn;
}

/// Function will obtain the file data and store it in a data array
/// Called by main()
/// @param [in] fn input file handler
/// @param [out] students student data array
/// @return true if successful, otherwise false
bool readData(const string& fn, student_t students[]) {
    // variable definition(s)
    bool didOpen = true;     // success flag
    ifstream fin;            // declare the file stream header
    int record;              // current record from file

    fin.open(fn);            // attempt to open the data file

    // obtain the data if the file is valid
    if (fin.is_open()) {
        record = 0;
        // loop through all the records in the file
        // and extract the data to place in the data model
        while (record < STUDENT_CNT) {
            // obtain the students' name
            getline(fin, students[record].name, ' ');
            // obtain the students' scores
            for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
                fin >> students[record].scores[scoreIdx];
                fin.ignore();
            }
            // increment record pointer
            record++;
        }
    } else {
        // file input error
        cout << "Error opening file: " << fn << endl;
        cout << endl;
        didOpen = false;
    }

    // close the file and the return value
    fin.close();

    return didOpen;
}

/* *********** Processing Phase ****************************************** */

/// Function will calculate the averages from the student records
/// Called by main()
/// @param [in,out] students is the array of student records
void calculateRecordAverages(student_t students[]) {
    // variable definition(s)
    int record = 0;              // current record from file
    int sum = 0;                 // accumulator for each student's scores
    double sAvg;                 // average for each student's scores

    while (record < STUDENT_CNT) {
        // set sum to 0 for each student
        sum = 0;
        for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
            // obtain a sum of the student's scores
            sum += students[record].scores[scoreIdx];
        }
        // using the sum calculate the average
        // average score = sum of scores / number of scores
        sAvg = static_cast<double>(sum) / SCORE_CNT;

        // set precision to 2 decimal places
        cout << fixed << showpoint << setprecision(2);

        // assign the average value to the students records
        students[record].average = sAvg;
        record++;
    }
}

/// Function will record and calculate the letter grades of the students
/// Called by main()
/// @param [out] students is the array of student records
void recordAverages2LetterGrades(student_t students[]) {
    // variable definition(s)
    int record = 0;            // current record from file
    double sAvg = 0;           // average for each student's scores

    // loop through each student's average and assign a letter grade
    while (record < STUDENT_CNT) {
        // assign the average score to a temp variable
        sAvg = students[record].average;

        // use the function to obtain a letter grade based on the average
        students[record].grade = score2LetterGrade(sAvg);
        record++;
    }
}

/* *********** Output Phase ********************************************** */

/// Function will write the student reports as per assignment guidelines
/// Called by main()
/// @param [in] students is an array of student records
void printReport(const student_t students[]) {
    // variable definition(s)
    int record = 0;              // current record from file
    int classSum = 0;            // stores the total class scores

    // write an initial header to the screen
    cout << endl;
    cout << "Student Grade Report" << endl;
    printSepLine();
    printHeader();

    // write the students' data to the screen
    while (record < STUDENT_CNT) {
        printRow(students, record);
        record++;
    }

    // write a seperation line
    printSepLine();

    // write the class average
    record = 0;

    // using the student records obtain the sum of the class's scores
    while (record < STUDENT_CNT) {
        for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
             classSum += students[record].scores[scoreIdx];
        }
        record++;
    }

    // use the class sum to write the class average
    printClassAverage(classSum);

    // write a seperation line
    printSepLine();
    cout << endl;               // added line gap for output

    // write the best performing student's information
    printBestPerformance(students);

    // write the poorest performing student's information
    printPoorestPerformance(students);

}


// EOF: finalB.cpp
