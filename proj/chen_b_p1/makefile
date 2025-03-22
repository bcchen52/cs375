all: program1

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
program1: project1.o
	g++ project1.o -o program1

# Specify how the object files should be created from source files

project1.o: project1.cpp
	g++ -c project1.cpp

clean:
	rm -f *.o project1 program1