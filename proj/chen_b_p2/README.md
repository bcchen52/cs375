Written with C++

To compile: make

To run: ./submission 

Notes: Works perfectly for example. For the heap and handle array, I use a vector, solely for the fact that I am using a class and can't declare and reiniatilize a raw array without dynamically allocating memory, which I would rather not. I do not use any vector functionality that arrays do not have, except for the ability to reallocate them to the given max size in my Heap constructor. I could have initialized array to some large number, but there was no limit given on how large n can be. 

Also, in showHandles, the error message says that handle[<k>] = -1 when k is not in the heap. I use 0, as k is from 1 to n, so 0 is a valid invalid integer. However, I print that it is -1 to match with the expected output. 

Assumptions include that any k is in the range of 1 to n, I have added some error checking, but not fully. 