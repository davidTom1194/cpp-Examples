# @file Makefile
# @author David Tom <8000190528@student.csn.edu>
# @date 11/12/23
# @note I pledge my word of honor that I have abided by the
# the CSN Academic Integrity Policy while completing this assignment.
#
# @brief This makefile is designed to easily compile any dependencies alongside
#        the main file in order to apply any changes required for submission.
#
# @note People who helped me: N/A
#
# @note This is but one possible solution to the assignment.
#       Programming techniques and commands in this solution
#       are aligned with the current and previous chapters,
#       labs, and lectures, which may result in a trade-off
#       between efficient coding and what student are
#       currently able to understand.

# Variable Declaration(s)
compFlag = g++ $$CXXFLAGS

# Main runtime
all: clean optional

optional: pa pa-test unit-tests turnin

# Main file - programming assignment and dependencies
pa: pa16.cpp
		$(compFlag) pa16.cpp -o pa16

# Clean *.o files
clean:
		rm -rf *.o

# Test all
# Note: the below test script was not submitted alongside the required files
pa-test:
		time ./pa16

unit-tests: unit-tests.cpp
		$(compFlag) unit-tests.cpp -o unit-tests
		time ./unit-tests

valgrind: pa16 unit-tests
		valgrind ./pa16
		valgrind ./unit-tests

turnin: pa16.cpp unit-tests.cpp Makefile
		turnin -c cs202 -p pa16 unit-tests -v pa16.cpp unit-tests.cpp Makefile

# EOF: Makefile
