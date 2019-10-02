# PROGRAM:    Assign 1 
# PROGRAMMER: Samuel Piecz
# LOGON ID:   Z1732715
# DATE DUE:   9/06/19
#

# Compiler variables
CCFLAGS = -ggdb -Wall -std=c++11

# Rule to link object code files to create executable file
Assign3: Assign3.o
	g++ $(CCFLAGS) -o Assign3 Assign3.o

# Rule to compile source code file to object code
Assign3.o: Assign3.cxx
	g++ $(CCFLAGS) -c Assign3.cxx

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign3
