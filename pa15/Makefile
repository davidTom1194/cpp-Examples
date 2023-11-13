# @file Makefile
# @author David Tom <8000190528@student.csn.edu>
# @date 11/7/23
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

optional: pa pa-test turnin

# Main file - programming assignment and dependencies
pa: pa15.cpp
		$(compFlag) pa15.cpp -o pa15

# Clean *.o files
clean:
		rm -rf *.o

pa-test:
		time ./pa15

turnin: pa15.cpp
		turnin -c cs202 -p pa15 -v pa15.cpp

# EOF: Makefile
