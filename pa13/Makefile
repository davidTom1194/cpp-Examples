# @file Makefile
# @author David Tom <8000190528@student.csn.edu>
# @date 10/3/23
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
all: pa clean

#optional: Vector-test valgrind-test turnin
#PERSONAL_DEBUG: valgrind-test pa-test turnin Vector-test

# Main file - programming assignment and dependencies
pa: pa13a.cpp Vector.o
		$(compFlag) pa13a.cpp Vector.cpp Vector.h -o pa13a

# Vector class - a sequence container that encapsulates dynamic size arrays.
Vector.o: Vector.cpp Vector.h
		$(compFlag) -c Vector.cpp Vector.h -o Vector.o

# Clean *.o files
clean: Vector.o
		rm -rf *.o

# Test files for verification
# Vector class
Vector-test: Vector.cpp Vector-test1.cxx Vector-test2.cxx
		$(compFlag) Vector.cpp Vector-test1.cxx -o vector-test1
		./vector-test1
		$(compFlag) Vector.cpp Vector-test2.cxx -o vector-test2
		./vector-test2

# Test all
# Note: the below test script was not submitted alongside the required files
pa-test: homemade-judge.sh
		time ./homemade-judge.sh

valgrind-test: vector-test1 vector-test2
		time valgrind ./vector-test1
		time valgrind ./vector-test2

turnin: Vector.h Vector.cpp pa13a.cpp Makefile
		turnin -c cs202 -p pa13a -v Vector.h Vector.cpp pa13a.cpp Makefile

# EOF: Makefile
