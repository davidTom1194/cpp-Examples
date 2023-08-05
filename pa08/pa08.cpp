/// @file pa08.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date 7/24/23
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This program is a programming assignment that deciphers a message
///        using a book by using array concepts learned in Chapter 8.
///
/// @note People who helped me: N/A
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.
///

// preprocessor directives
// library includes
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cassert>

using namespace std;

// Global constant definition(s)
const int MAX_SIZE = 100;    // the maximum number of strings to read

/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
// for processing the secret message
string getFileName(const string& prompt);
void getMessage(const string& fileName, string msg[], int& size, int maxSize);
void copyArray(const string a[], string b[], int size);
void sortArray(string a[], int size);
int extractPageNumber(const string codeStr);

// for processing the target page
void setCharLocation(const string codeStr,
                     int& pageNum, int& lineNum, int& charPos);
int getPageLines(const string& FN, int pageNum, string a[], int MAX_LINES);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Local constant definition(s)
    const int MAX_LINES = 30;     // the maximum number of lines on a page

    // stores a prompt to obtain the file name
    const string FILE_PROMPT = "Enter the file name of the coded message: ";
    // stores a prompt to obtain the cipher text key
    const string KEY_PROMPT = "Enter the file name of the cipher text key: ";
    // stores a prompt to obtain a page to display
    const string PAGE_PROMPT = "Enter the number of the page to display: ";

    // Variable declarations(s)
    int exitState;             // tracks the exit code for the process
    exitState = EXIT_SUCCESS;  // set state to successful run

    string FN;                 // stores the file name

    int size = 0;              // the actual number of strings to read
    string msg[MAX_SIZE];      // stores the cipher code for a single character
    string copy[MAX_SIZE];     // stores the second copy of the first array
    string lines[MAX_SIZE];    // stores the lines of text from the page
    int pageNum;               // stores the page number
    int lineNum;               // stores the line number
    int charPos;               // stores the character position
    int i;                     // tracks the loop count
    string character;          // stores the character from the book
    string message[MAX_SIZE];  // stores the decoded message as an array
    string decoded;            // stores the array message

    // Input Phase

    // obtain file name from user
    FN = getFileName(FILE_PROMPT);

    // obtain the secret message
    getMessage(FN, msg, size, MAX_SIZE);

    // obtain file name
    FN = getFileName(KEY_PROMPT);

    // Processing Phase

    // create a copy of the first array
    copyArray(msg, copy, size);

    // sort into the correct order
    sortArray(copy, size);

    // loop to obtain character from pages and decode message
    for (i = 0 ; i < size; i++) {
        // obtain page and line numbers as well as character position
        setCharLocation(copy[i], pageNum, lineNum, charPos);

        // obtain page lines
        getPageLines(FN, pageNum, lines, MAX_LINES);

        // set the decoded message for output
        character = lines[lineNum];
        message[i] = (character.at(charPos));
        decoded += message[i];

    }

    // Output phase

    cout << decoded << endl;
    cout << endl;

    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------

/// Function obtains a file name from the user through a prompt
/// @param prompt is a user prompt to obtain a file name
/// return FN is a string storing the file name
string getFileName(const string& prompt) {
    string FN;                  // stores the file name

    // obtain file name from user
    cout << prompt << endl;
    cin >> FN;

    return FN;
}

/// Function opens a file and stores the message in an array.
/// @param fileName is the file name of the secret message
/// @param msg[] is an array that holds each line of the message
/// @param size is the number of elements used
/// @param maxSize is the number of elements available in the array
void getMessage(const string& fileName, string msg[], int& size, int maxSize) {

    // open file
    ifstream fin;
    fin.open(fileName);

    // read line by line and store in array with an EOF loop
    do {
        // count and store an amount of strings less than the maxSize
        if (size < maxSize) {
            getline(fin, msg[size]);
            size++;
        } else {
            // if the size exceeds the maxSize close the file
            fin.clear();
            fin.close();
        }
    } while (fin);

    // remove unused array value obtained from do..while loop
    size--;

    // close file
    fin.clear();
    fin.close();
}

/// Function will copy the first array into a second array
/// @param a[] is the source array
/// @param b[] is the destination array following the processing
/// @param size is the number of elements used in the array
void copyArray(const string a[], string b[], int size) {
    int i;                        // tracks the values in the for loop

    for (i = 0; i < size; i++) {
        // copy values from the initial array value to the end
        b[i] = a[i];
    }
}

/// Function will sort the array with selection sort
/// @param a[] is an array to be sorted
/// @param size is the number of elements used in the array
void sortArray(string a[], int size) {
    int i;                        // tracks the values of the array
    int smallestIndex;            // stores the smallest value of i
    int location;                 // stores the location of the value of i
    string temp;                  // acts as a temporary variable
    int p;                        // stores the page number as an integer
    int pSmallestIndex;           // stores the smallest page number

    // start a loop through the array
    for (i = 0; i < size; i++) {
        // set the smallestIndex variable to i in the loop (ie. 0, 1, etc.)
        smallestIndex = i;
        for (location = i + 1; location < size; location++) {
            // extract page numbers as an integer and assign as variables
            p = extractPageNumber(a[location]);
            pSmallestIndex = extractPageNumber(a[smallestIndex]);
            // compare the page numbers
            if (p < pSmallestIndex) {
                smallestIndex = location;
            }
        }
        // store a temporary value of the array value with the smallest index
        temp = a[smallestIndex];
        a[smallestIndex] = a[i];
        a[i] = temp;
    }
}

/// This function extracts the page number from the cipher code
/// @param codeStr cipher code string
/// @return the page number from the code string.
int extractPageNumber(const string codeStr) {
    int pageNum = 0;

    // set a variable to hold the location of the first dot
    const size_t pos1 = codeStr.find('.');

    // extract and translate the ASCII text representing the
    // page number into an integer
    pageNum = stoi(codeStr.substr(0, pos1));

    return pageNum;
}

/// Function obtains the page lines from a book
/// @param FN holds the name of the cipher text file to be opened and read
/// by the function
/// @param pageNum holds the page number to be retrieved
/// @param a[] is the array that will hold the lines of text from the page
/// @param MAX_LINES is the maximum array size
/// @return size is the set array size
int getPageLines(const string& FN, int pageNum, string a[], int MAX_LINES) {
    int i = 0;                     // tracks array count
    int startPageLines = 0;        // stores the start of the line
    int maxPageLines = 0;          // stores the maximum line size
    int lineCount = 0;             // stores the line count for the new array
    int endPageLines = 0;          // stores the value of the end of the lines
    const int finalPage = pageNum + 1;   // stores where to end the page
    string strFinalPage;           // stores the page number to end on
    string strStartingPage;        // stores the page to search

    string tmp[10000];              // temporary value to read array
    int j;                          // stores the new value for a[]

    // assign strings to find using stoi
    strFinalPage = "page " + to_string(finalPage);
    strStartingPage = "page " + to_string(pageNum);

    // open file
    ifstream fin;
    fin.open(FN);

    // loop to obtain page lines
    do {
        // obtain initial data from line
        getline(fin, tmp[i]);
        // search for first page number
        if (tmp[i].find(strStartingPage) != string::npos) {
            // set the start of the page lines and the maximum lines
            startPageLines = i;
            maxPageLines = MAX_LINES + i;
            j = 0;
            while (fin) {
                // assign the temporary value to a[]
                getline(fin, tmp[i]);
                a[j] = tmp[i];
                // search for final page number or line count = MAX_LINES
                if ((tmp[i].find(strFinalPage) != string::npos) ||
                     i == maxPageLines) {
                    // set the end of the page and close the file
                    endPageLines = i;
                    // end while loop
                    fin.close();
                    fin.clear();
                }
                // continue loop through array
                i++;
                j++;
            }
        }
        // continue loop through array
        i++;
    } while (fin);

    // set the array size to the line count
    lineCount = endPageLines - startPageLines;

    // close file
    fin.clear();
    fin.close();

    return lineCount;

}


/// Function will find the position of the character to look for in the message
/// @param pageNum is the extracted page number from the code string
/// @param codeStr holds one line of the message file
/// @param lineNum is the extracted line number from the code string
/// @param charPos is the extracted character position in the line
void setCharLocation(const string codeStr,
                     int& pageNum, int& lineNum, int& charPos) {
    int lengthCharacter;    // stores the length of the string
    string promptChar;      // stores the character of the value at j
    string tmpPage;         // stores a temporary string for page number
    string tmpLine;         // stores a temporary string for line number
    string tmpChar;         // stores a temporary string for character position
    int j = 0;              // tracks the loop count
    bool isValid = true;    // verifies the loop is valid

    // determine the for loop max count
    lengthCharacter = static_cast<int>(codeStr.length());

    // verify the loop is valid and check for digits
    while (isValid && static_cast<bool>(isdigit(codeStr.at(j)))) {
        // obtain page numbers until a period is detected
        promptChar = codeStr.at(j);
        tmpPage += promptChar;
        pageNum = stoi(tmpPage);
        j++;
        if (codeStr.at(j) == '.') {
            // skip over value at period
            j++;
            while (isValid && static_cast<bool>(isdigit(codeStr.at(j)))) {
                // obtain line numbers until a period is detected
                promptChar = codeStr.at(j);
                tmpLine += promptChar;
                lineNum = stoi(tmpLine);
                j++;
                if (codeStr.at(j) == '.') {
                    // skip over value at period
                    j++;
                    while (isValid &&
                           static_cast<bool>(isdigit(codeStr.at(j)))) {
                         // obtain character position for the remainder of
                         // the string length
                         promptChar = codeStr.at(j);
                         tmpChar += promptChar;
                         charPos = stoi(tmpChar);
                         j++;
                         if (j == lengthCharacter) {
                             // set bool to false at the end of the string
                             isValid = false;
                         }
                    }
                }
            }
        }
    }

    // Set line number - 1 for appropriate decoding of array
    lineNum--;
    charPos--;

}


// EOF: pa08.cpp
