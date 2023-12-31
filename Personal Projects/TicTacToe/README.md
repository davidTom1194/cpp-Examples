# Tic Tac Toe
The program will allow for the playing of the game tic-tac-toe
between 2 entities, human and/or computer. When selecting 0 users, the
computer will play against itself by using two different algorithms:
one to select a move based on the available moves, the other (Minimax) 
will select a move that potentially is the best based on the algorithm's
specifications. If a user is selected, the AI will use Minimax. 
 
Program is optimized to run effectively with minimal intervention and may 
be used on larger game boards (ie. 30x30 ~ 5 seconds) quickly and 
efficiently by using Alpha-Beta Cut Offs. Additional modifications, such as
turn-based timers, allow the program to handle even larger game boards by
selecting a random move, albeit a much less effective approach to a
calculated approach.

# File descriptions
- Tic Tac Toe: Tic-Tac-Toe.cpp
  - proper code documentation
  - AI vs AI, AI vs Human, and Human vs Human
  - AI Algorithms: Minimax with Alpha-Beta Cut Off & Random Selections
  - dynamic game board size
  - customizable AI game counts
  - benchmarking function
  - bounds checking and input verification
  - pointers
  - vectors
  - structs
  - no memory leaks
  - and an appropriate output based on the validity of the program's operation.

- Examples and estimated times:
  - 3x3     = 5.08e-05  seconds
  - 10x10   = 0.0153459 seconds 
  - 30x30   = 4.8283    seconds

## Getting Started

Clone/download the files and any dependencies for your project then compile and run the programs using the linux command:
  - "$ c++ $CXXFLAGS [programName.cpp] -o [programName]"
  - "./[programName]

### Prerequisites

In order to run any C++ based programs you must first have installed C++ and its dependencies on a device that can compile
and run the program.  You can install the appropriate software many ways:
1. Visual Studio
2. Geany
3. Repository: Most if not all linux distros have a repository containing the necessary software that can be accessed using the
   below example commands (more information can be found by accessing the manual/help page for your operating system):
   - For Debian/GNU Linux:
         - "$ sudo apt install build-essential"
   - RHEL
         - "$ sudo dnf install build-essential"

Occasionally programs may require dependencies; the easiest way to properly install them is by searching GitHub repositories
and cloning/downloading the appropriate files for your project.  This can be done in:
    - a web browser
    - **or**
    - through the "git clone ssh://git@github.com/[username]/[repository-name].git" command
Once downloaded, import the library and restart your IDE.

### Example installation
1. Download the appropriate dependencies and software
2. Install as needed
3. Import any libraries/dependencies for your project (most projects will state this in the first few lines)
4. Clone the files from the repository
5. Upload the code to your device (laptop, Desktop, etc.).
6. Contribute to further developments.
7. Repeat as needed

## Contributing

Please read [CONTRIBUTING.md](https://github.com/davidTom1194/davidTom1194/blob/main/CONTRIBUTING.md) for details on our
code of conduct, and the process for submitting pull requests to us.

## Authors

* **David Tom** - *Initial Work* - [davidTom1194](https://github.com/davidTom1194)
See also the list of [contributors](https://github.com/davidTom1194/davidTom1194/blob/main/contributors)

## License

This project is licensed under the GNU General Public License Version 3 - see the [LICENSE](https://github.com/davidTom1194/davidTom1194/blob/main/LICENSE) file for details

## Acknowledgements

* A big thanks to any and all contributors, no matter how big or small the contribution it all helps.
