# @file Makefile
# @author David Tom <8000190528@student.csn.edu>
# @date 11/29/23
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
cpp = pa18.cpp
hpp1 = LList.hpp
hpp2 = Stack.hpp
pa = pa18

# Main runtime
all: clean optional

optional: pa unit-tests tests linter valgrind turnin

# Main file - programming assignment and dependencies
pa: $(cpp) $(hpp)
		$(compFlag) $(cpp) -o $(pa)

# Clean *.o files
clean:
		rm -rf *.o

# Test all
# Note: the below test script was not submitted alongside the required files

unit-tests: homemade-judge.sh
		./homemade-judge.sh

tests: $(hpp1) $(hpp2) LList-test.cxx Stack-test.cxx
		$(compFlag) $(hpp1) LList-test.cxx -o llist-test; ./llist-test
		$(compFlag) $(hpp2) Stack-test.cxx -o stack-test; ./stack-test

linter: $(cpp)
		lint $(cpp)

valgrind: $(pa)
		valgrind cat Pjudge/$(pa)-input0.txt | ./$(pa)
		valgrind cat Pjudge/$(pa)-input1.txt | ./$(pa)
		valgrind cat Pjudge/$(pa)-input2.txt | ./$(pa)
		valgrind cat Pjudge/$(pa)-input3.txt | ./$(pa)

turnin: $(pa) $(hpp2) $(cpp) Makefile
		turnin -c cs202 -p $(pa) -v $(hpp2) $(cpp) Makefile

# EOF: Makefile
