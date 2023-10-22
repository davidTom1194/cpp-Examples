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
all: clean optional

optional: pa pa-test Vector-test valgrind-test turnin
#PERSONAL_DEBUG: valgrind-test pa-test turnin Vector-test pa

# Main file - programming assignment and dependencies
pa: pa14.cpp
		$(compFlag) pa14.cpp -o pa14

# Vector class - a sequence container that encapsulates dynamic size arrays.
#Vector.o: Vector.cpp Vector.h
#		$(compFlag) -c Vector.cpp Vector.h -o Vector.o

# Clean *.o files
clean:
		rm -rf *.o

# Test files for verification
# Vector class
Vector-test: Vector.hpp Vector-test4.cxx
		#Vector.cpp Vector-test1.cxx Vector-test2.cxx Vector-test3.cxx
		#$(compFlag) Vector.cpp Vector-test1.cxx -o vector-test1
		#./vector-test1
		#$(compFlag) Vector.cpp Vector-test2.cxx -o vector-test2
		#./vector-test2
		#$(compFlag) Vector.hpp Vector-test3.cxx -o vector-test3
		#time ./vector-test3
		$(compFlag) Vector.hpp Vector-test4.cxx -o vector-test4
		time ./vector-test4

# Test all
# Note: the below test script was not submitted alongside the required files
pa-test:
		#time ./homemade-judge.sh
		time ./csn-judge.sh

valgrind-test: vector-test4
		#vector-test1 vector-test2 vector-test3
		#time valgrind ./vector-test1
		#time valgrind ./vector-test2
		#time valgrind ./vector-test3
		time valgrind ./vector-test4

turnin: Vector.hpp pa14.cpp Makefile
		turnin -c cs202 -p pa14 -v Vector.hpp pa14.cpp Makefile

# EOF: Makefile
