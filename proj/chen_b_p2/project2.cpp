#include "Heap.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]){
    //we can have a vector to represent the heap
    //for the "handle array", use a hashmap of fixed size n, as we know that max size is n, unordered_map

    if (argc < 3){
        cout << "Not enough commandline arguments" << endl;
        return -1;
    }

    string infile = argv[1];
    string outfile = argv[2];

    ifstream inputFile(infile);
    ofstream outputFile(outfile);

    if (!inputFile){
        cout << "Input file not valid." << endl;
        return -1;
    }

    if (!outputFile){
        cout << "Output file not valid." << endl;
        return -1;
    }

    streambuf* coutBuf = cout.rdbuf();
    cout.rdbuf(outputFile.rdbuf());
    //redirecting cout to file, I wrote this using cout, IMO easier than passing in outstream to Heap class

    string line;
    string arg;
    stringstream parsed_string;
    string param1;
    string param2;
    //variables to handle different parts of each command

    getline(inputFile, line);

    Heap heap(stoi(line)); //this is assuming first arg is an int

    while (getline(inputFile, line)){
        cout << line << endl;

        //unique 5 chars of each command - "findC", "inser", "elimi", "earnP", "loseP", "showC", "showH", "showL", "crown"
        //elimi, showC, showH, crown 0 args
        //findC, showL 1 arg
        // inser, earnP, loseP 2 arg
        arg = line.substr(0, 5);

        if (arg == "elimi" || arg == "showC" || arg == "showH" || arg == "crown"){
            if (arg == "elimi"){
                heap.eliminateWeakest(true);
            } else if (arg == "showC") {
                heap.showContestants();
            } else if (arg == "showH") {
                heap.showHandles();
            } else {
                heap.crownWinner();
            }
        } else if (arg == "findC" || arg == "showL") {
            //we know that we will have one argument, so, we use string stream to divide out line by whitespace
            parsed_string.clear();
            parsed_string.str(line); // parsed_string == command, <x>, <y>
            parsed_string >> param1; // param1 = command - We do this to get rid of the command
            parsed_string >> param1; // param1 = <x> - we have replaced command with our parameter
            param1 = param1.substr(1, param1.length() - 2); // param1 = x
            if (arg == "findC") {
                heap.findContestant(stoi(param1), true);
            } else {
                heap.showLocation(stoi(param1));
            }
        } else if (arg == "inser" || arg == "earnP" || arg == "loseP") {
            parsed_string.clear();
            parsed_string.str(line);
            parsed_string >> param1;
            parsed_string >> param1;
            parsed_string >> param2;

            param1 = param1.substr(1, param1.length() - 2);
            param2 = param2.substr(1, param2.length() - 2);

            if (arg == "inser") {
                heap.insertContestant(stoi(param1), stoi(param2));
            } else if (arg == "earnP") {
                heap.earnPoints(stoi(param1), stoi(param2));
            } else {
                heap.losePoints(stoi(param1), stoi(param2));
            }
        } else {
            cout << "Given command" << arg << "does not exist!!!" << endl;
        }
    }

    return 0;
}
