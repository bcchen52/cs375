CXXFLAGS = -std=c++11 -Wall -Wextra

all: submission

submission: project3.o
	g++ $(CXXFLAGS) project3.o -o submission

# Specify how the object files should be created from source files
project3.o: project3.cpp
	g++ $(CXXFLAGS) -c project3.cpp

clean:
	rm -f *.o project3 submission