/// @file pa09.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 8/2/23
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This program is a lab assignment that demonstrates struct concepts
///        learned in Chapter 9 through the use of a data set involving
///        individual names and their respective scores.
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
const int SCORE_CNT = 15;           // the number of scores
const int STUDENT_CNT = 10;         // the number of students
const int COL1 = 18;                // 1st column width of tabulated output
const int COL2 = 7;                 // 2nd column width of tabulated output
const int COL3 = 5;                 // 3rd column width of tabulated output
const int COL4 = 7;                 // 4th column width of tabulated output

/// -------------------------------------------------------------------------
/// Structure Declaration(s)
/// -------------------------------------------------------------------------

struct student_t {
    string fName;
    string lName;
    int scores[SCORE_CNT] = {0};
    double average;
    double gpa;
    string grade;
};  // end struct student_t

/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
// Input Phase
bool readStudentData(const string& FN, student_t dataSet[]);

// Processing Phase
void runCalcs(student_t dataSet[]);
void setGradeNGpa(student_t dataSet[], int idx);

// Output Phase
void printStudentData(const student_t data[]);
void printGradeReport(const student_t dataSet[]);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
    // Variable declarations(s)
    int exitState;                      // tracks the exit code for the process
    exitState = EXIT_SUCCESS;           // set state to successful run

    string fn;                          // file name for the student data
    student_t records[STUDENT_CNT];     // array of student records

    /* ******* Input Phase *********************************************** */
    // expected command line argument: bug09-studentData.txt;
    if (argc < 2) {
        cout
        << setw(40) << "Expected a data file name, such as: "
        << "pa09-data0.csv\n"
        << setw(40) << "Launch Syntax: "
        << "./pa09 <filename.ext>\n\n";
        exitState = EXIT_FAILURE;
    } else {
        fn = argv[1];

        // Read in the data. if it fails set the exitState to fail
        if (!readStudentData(fn, records)) {
            exitState = EXIT_FAILURE;
        }
    }

    /* ******* Processing / Ouptut Phase ********************************* */
    if (exitState == EXIT_SUCCESS) {
        // update the record with calculated average score on each record
        runCalcs(records);

        // Output a tabulated report of individual scores
        printStudentData(records);

        // Output a table of score averages, grades, and GPA
        printGradeReport(records);
    }

    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------

/// Function will populate the student data from a file into an array
/// @param FN is the file containing the data
/// @param dataSet is the data model
/// @return true if successful, otherwise false
bool readStudentData(const string& FN, student_t dataSet[]) {
    bool didOpen = true;     // success flag
    ifstream fin;            // declare the file stream header
    int record;             // current record from file

    fin.open(FN);            // attempt to open the data file

    // If the file was successfully opened...
    if (fin.is_open()) {
        record = 0;

        // loop through all the records in the file
        // extract the data and place in data model
        while (record < STUDENT_CNT) {
            getline(fin, dataSet[record].fName, ',');   // get the last name
            getline(fin, dataSet[record].lName, ',');   // get the last name

            // get student scores
            for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
                fin >> dataSet[record].scores[scoreIdx];
                fin.ignore();
            }
            // increment record pointer
            record++;
        }
    } else {    // the file wasn't open
        cout << "Unable to process data file: " << FN << endl;
        didOpen = false;
    }

    fin.close();

    return didOpen;

}

/// Function will calculate the average scores from the data file
/// @param dataSet[] is the array to read the scores from
void runCalcs(student_t dataSet[]) {
    int total = 0;      // sum accumulator

    // loop through each record and calculate the average score for the record
    for (int recordIdx = 0; recordIdx < STUDENT_CNT; recordIdx++) {
        total = 0;      // reset accumulator
        for (int scoreIdx = 0; scoreIdx < SCORE_CNT; scoreIdx++) {
            // total the scores
            total += dataSet[recordIdx].scores[scoreIdx];
        }

        // calculate the average for the record
        dataSet[recordIdx].average = static_cast<double>(total) / SCORE_CNT;
        setGradeNGpa(dataSet, recordIdx);
    }
}

/// Function will determine the grade and GPA from an average score
/// @param dataset[] is an array of student records
/// @param idx is the index of the record
void setGradeNGpa(student_t dataSet[], int idx) {
    if (dataSet[idx].average >= 95) {
        dataSet[idx].grade = "A";
        dataSet[idx].gpa = 4.0;
    } else if (dataSet[idx].average >= 90) {
        dataSet[idx].grade = "A-";
        dataSet[idx].gpa = 3.7;
    } else if (dataSet[idx].average >= 87) {
        dataSet[idx].grade = "B+";
        dataSet[idx].gpa = 3.3;
    } else if (dataSet[idx].average >= 83) {
        dataSet[idx].grade = "B";
        dataSet[idx].gpa = 3.0;
    } else if (dataSet[idx].average >= 80) {
        dataSet[idx].grade = "B-";
        dataSet[idx].gpa = 2.7;
    } else if (dataSet[idx].average >= 77) {
        dataSet[idx].grade = "C+";
        dataSet[idx].gpa = 2.3;
    } else if (dataSet[idx].average >= 73) {
        dataSet[idx].grade = "C";
        dataSet[idx].gpa = 2.0;
    } else if (dataSet[idx].average >= 70) {
        dataSet[idx].grade = "C-";
        dataSet[idx].gpa = 1.7;
    } else if (dataSet[idx].average >= 67) {
        dataSet[idx].grade = "D+";
        dataSet[idx].gpa = 1.3;
    } else if (dataSet[idx].average >= 65) {
        dataSet[idx].grade = "D";
        dataSet[idx].gpa = 1.0;
    } else {
        dataSet[idx].grade = "F";
        dataSet[idx].gpa = 0.0;
    }

}

/// Function will output a tabulated report of individual scores
/// @param data[] is an array of student records
void printStudentData(const student_t data[]) {
    int recordIdx = 0;
    string name;           // holds the name string for output

    while (recordIdx < STUDENT_CNT) {
        // output index
        if (recordIdx < 9) {
            cout << right << "   " << recordIdx + 1 << ". ";
        } else {
            cout << right << "  " << recordIdx + 1 << ". ";
        }

        // concatenate the last and first name to make output formatting
        // easier, then print the name
        name = data[recordIdx].fName + " " + data[recordIdx].lName;
        cout << left << setw(18) << name << ": ";

        // print the scores
        cout << right;
        for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
             cout << setw(3) << data[recordIdx].scores[scoreIdx] << " ";
        }
        cout << endl;

        // increment record pointer
        recordIdx++;
    }
}

/// Function will output the scores with proper tabulation
/// @param dataSet[] is an array of student recrods
void printGradeReport(const student_t dataSet[]) {
    const string SEP = string(COL1 + COL2 + COL3 +
                              COL4, '-');    // line separator
    const string INDENT = "     ";                       // indent for table
    int recordIdx = 0;
    string name;        // holds the name string for output

    // set output formatting for numbers
    cout << fixed << setprecision(2);

    // print heading
    cout << endl;
    cout << INDENT << left << setw(COL1) << " Name";
    cout << right << setw(COL2) << "GRD";
    cout << right << setw(COL3) << "Avg";
    cout << right << setw(COL4) << "GPA\n";
    cout << INDENT << SEP << endl;

    while (recordIdx < STUDENT_CNT) {
        // set decimal precision
        cout << setprecision(1);

        // output index
        if (recordIdx < 9) {
            cout << "   " << recordIdx + 1 << ". ";
        } else {
            cout << "  " << recordIdx + 1 << ". ";
        }

        // concatenate the last and first name to make output formatting
        // easier, then print the name
        name = dataSet[recordIdx].fName + " " + dataSet[recordIdx].lName;
        cout << left << setw(COL1) << name << "|  ";

        // print the grade
        cout << left << setw(COL2 - 2) << dataSet[recordIdx].grade;

        // print the averages
        cout << left << setw(COL3 - 1) << dataSet[recordIdx].average;

        // print the GPA
        cout << right << setw(COL4 - 2) << dataSet[recordIdx].gpa
        << "  " << endl;

        // increment record pointer
        recordIdx++;
    }
}

// EOF: pa09.cpp
