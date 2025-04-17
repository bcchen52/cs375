all: submission

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
submission: Heap.o project2.o
	g++ project2.o Heap.o -o submission

# Specify how the object files should be created from source files
project2.o: project2.cpp
	g++ -c project2.cpp

Heap.o: Heap.cpp 
	g++ -c Heap.cpp

clean:
	rm -f *.o project2 submission Heap