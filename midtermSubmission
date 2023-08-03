/// @file midtermB.cpp
/// @author David Tom <8000190528@student.csn.edu>
/// @date July 9, 2023
/// @note I pledge my word of honor that I have abided by the
/// CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This is a program using techniques learned in cs135 and falls in
/// line with the requirements outlined in the Midterm exam: Programming
/// Portion (midtermB).  Program is based on techniques learned from
/// Chapter 1 to 6 (week 06).  The program counts the vowels in the provided
/// texts and writes an appropriate output based on the test script.
///
/// @note People who helped me: NA

// Include header files
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>

// Set namespace
using namespace std;

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main()
{

/* ********** Variable declarations(s) ************************************ */
/// 1. Local constant definition(s)
/// 2. Exit state variables
/// 3. User Input variables
/// 4. Processing Phase variables
/* ************************************************************************ */

// 1. Local constant definition(s)
    const string INDENT = "       ";  // indent used for output

// 2. Exit state variables
    int exitState;                    // exitState used for result
    exitState = EXIT_SUCCESS;         // exitState set for 0

// 3. User Input variables
    string inFile;                    // input file string

// 4. Processing Phase variables
    string fileData;                  // store data from file
    int lengthCharacter;              // count the characters from the file
    int sumCharacters = 0;            // count the total number of characters

    int loopCount;                    // count the loop
    char fileCharacter;               // store the character from the file

    int vowelCount = 0;               // tracks the amount of vowels
    int aVowel = 0;                   // tracks the amount of the letter 'a'
    int eVowel = 0;                   // tracks the amount of the letter 'e'
    int iVowel = 0;                   // tracks the amount of the letter 'i'
    int oVowel = 0;                   // tracks the amount of the letter 'o'
    int uVowel = 0;                   // tracks the amount of the letter 'u'

    double percentVowels = 0;         // Calculate percent

/* ********** User Input Phase ******************************************** */
/// 1. Obtain desired file name for vowel count.
/* ************************************************************************ */

// 1. Obtain desired file name for vowel count.
    cout << '\n'
         << "Enter file name for vowel count: ";
    cin >> inFile;

    // Open file.
    ifstream fin;
    fin.open(inFile);

/* ********** Processing Phase ******************************************** */
/// 1. Determine if file is valid.
/// 2. If the file is valid, read for whitespace characters and vowels.
/// 3. Count the vowels in the file.
/// 4. If no data, determine if there are vowels in the file.
/// 5. Calculate the percent of vowels.
/* ************************************************************************ */

// 1. Determine if file is valid.
    if (!fin.is_open()) {
        // If file is not valid: return 1.
        exitState = 1;
    } else {
// 2. If the file is valid, read for whitespace characters and vowels.
        fin >> fileData;
        if (!fin) {
            // If there is no data: return 2.
            exitState = 2;
        }

        // If there is data: EOF loop to count the characters in the file.
        while (fin) {
            lengthCharacter = static_cast<int>(fileData.length());
            sumCharacters = sumCharacters + lengthCharacter;
            fin >> fileData;
        }
    }

// 3. Count the vowels in the file.
    // Reset the file.
    fin.clear();
    fin.close();
    fin.open(inFile);

    if (fin.is_open()) {
        // Loop based on the number of characters and counts the vowels.
        for (loopCount = 0; loopCount < sumCharacters; loopCount++) {
             fin >> fileCharacter;
             // Return a lowercase character for any uppercase characters.
             if (!static_cast<bool>(islower(fileCharacter))) {
                 fileCharacter = static_cast<char>(tolower(fileCharacter));
             }
             // Count vowels
             // Switch can easily swap lower/uppercase values.
             switch (fileCharacter) {
             case 'a':
                 vowelCount++;
                 aVowel++;
                 break;
             case 'e':
                 vowelCount++;
                 eVowel++;
                 break;
             case 'i':
                 vowelCount++;
                 iVowel++;
                 break;
             case 'o':
                 vowelCount++;
                 oVowel++;
                 break;
             case 'u':
                 vowelCount++;
                 uVowel++;
                 break;
             default:
                 break;
             }
        }

// 4. If no data, determine if there are vowels in the file.
        // If no vowels: return 3.
        if (exitState != 2) {
            if (vowelCount == 0) {
                exitState = 3;
            }
        }

// 5. Calculate the percent of vowels.
        percentVowels = (static_cast<double>(vowelCount) /
                         static_cast<double>(sumCharacters)) * 100;
    }

/* ********** Output Phase ************************************************ */
/// 1. Write the total non-whitespace characters read.
/// 2. Write the total number of vowels.
/// 3. Write the total number of each vowel, including lower and uppercase.
/// 4. Write the percentage of vowels.
/// 5. Write error message based on return value.
/* ************************************************************************ */

    switch (exitState) {
    case 0:
// 1. Write the total non-whitespace characters read.
        cout << "Total non-whitespace characters read: "
             << sumCharacters
             << endl
             << '\n';

// 2. Write the total number of vowels.
        cout << "Total vowels read: "
             << vowelCount
             << endl;

// 3. Write the total number of each vowel including lower and uppercase.
        cout << INDENT
             << "'a' or 'A': "
             << aVowel
             << endl
             << INDENT
             << "'e' or 'E': "
             << eVowel
             << endl
             << INDENT
             << "'i' or 'I': "
             << iVowel
             << endl
             << INDENT
             << "'o' or 'O': "
             << oVowel
             << endl
             << INDENT
             << "'u' or 'U': "
             << uVowel
             << endl
             << '\n';

// 4. Write the percentage of vowels.
        // Set precision to 2 decimal places.
        cout << fixed
             << showpoint
             << setprecision(2);
        // Write the percentage.
        cout << "Of all the non-whitespace characters read "
             << percentVowels
             << "% were vowels."
             << endl
             << '\n';
        break;

// 5. Write error message based on return value.
    case 1:
        cout << "Unable to Read File, exiting..."
             << endl
             << '\n';
        break;
    case 2:
        cout << "There were no non-whitespace characters..."
             << endl
             << '\n';
        break;
    case 3:
        cout << "No vowels found..."
             << endl
             << '\n';
        break;

    // If case value is invalid, then write "The return value is invalid.".
    default:
        cout << "The return value is invalid.";
        break;
    }

/* ********** End Program ************************************************* */
/// 1. Close the file.
/// 2. return exitState.
/* ************************************************************************ */

// 1.  Close the file.
    fin.clear();
    fin.close();

// 2. return exitState.
    return exitState;
}

// EOF: midtermB.cpp
