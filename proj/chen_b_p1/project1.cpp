#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <utility> 
#include <chrono>

using namespace std;

vector<vector<int> > getCombinations(int n);

int main(int argc, char *argv[]) {
    //save market_prices dict?
    //Loop through price list
        //Loop through possibilities, calcualte

    //get market prices, put into map

    //we are given market price file and 

    if(argc != 5){
        cout << "Commandline format wrong" << endl;
        return 1;
    }

    string mfile = argv[2];
    string pfile = argv[4];

    ifstream inputFile(mfile);

    if (!inputFile) {
        cout << "Failed to open market prices file.\n";
        return 1;
    }

    //map/dict for prices
    map<string, int> market_prices;

    string line;

    //add market prices to map
    //skip int in first line, we can j loop through
    getline(inputFile, line);
    while (getline(inputFile, line)) {
        string name;
        string price;
        bool n = true;
        for(int i=0; i<line.length(); i++){
            if(line[i] == ' '){
                n = false;
                continue;
            }
            if(n){
                name += line[i];
            } else {
                price += line[i];
            }
        }

        //add pairs to map
        int k = stoi(price);
        market_prices[name] = k;
    }

    inputFile.close();

    ifstream inputFile2(pfile);

    if (!inputFile2) {
        cout << "Failed to open prices file.\n";
        return 1;
    }

    ofstream outFile("output.txt");
    //each loop is a problem, defined by the header of "entries budget"
    while (getline(inputFile2, line)) {

        //start timer
        auto start = chrono::high_resolution_clock::now();

        vector<pair<string, int> > prices;
        //prices in the form of [(name, price), (name, price)...] so easily indexed because combinations are given by index

        //we assume we are at an int line
        //parse heading line
        bool n = true;
        int entries;
        int budget;
        string t_entries;
        string t_budget;
        for(int i=0; i<line.length(); i++){
            if(line[i] == ' '){
                n = false;
                continue;
            }
            if(n){
                t_entries += line[i];
            } else {
                t_budget += line[i];
            }
        }

        entries = stoi(t_entries);
        budget = stoi(t_budget);

        // loop through each item and price
        for(int i=0; i<entries; i++){
            getline(inputFile2, line);
            string name;
            string price;
            bool n = true;
            for(int i=0; i<line.length(); i++){
                if(line[i] == ' '){
                    n = false;
                    continue;
                }
                if(n){
                    name += line[i];
                } else {
                    price += line[i];
                }
            }

            //add pairs to map
            int k = stoi(price);
            prices.push_back(make_pair(name, k));
        }

        //now, everything is parsed and ready

        vector<vector<int> > k = getCombinations(entries);

        int max = 0;
        int temp_prices;
        int temp_profit;
        vector<string> combo;
        vector<string> temp_combo;

        for (int i=0;i < k.size(); i++){
            //for each subset/combo
            temp_combo.clear();
            temp_prices = 0;
            temp_profit = 0;

            for (int w=0; w < k[i].size(); w++){
                string name = prices[k[i][w]-1].first;
                
                temp_combo.push_back(name);

                //buy price
                int buy = prices[k[i][w]-1].second;
                
                //if over budget, throw the whole combination out
                temp_prices += buy;
                if(temp_prices > budget){
                    break;
                }

                //check if market price
                if (market_prices.find(name) != market_prices.end()) {
                    //add profit
                    temp_profit += market_prices[name] - buy;
                } else {
                    cout << "No price for " << name << endl;
                    return 1;
                }
            }

            //check if it offers better solution. > because if repeats we only print 1 anyway
            if(temp_profit > max){
                max = temp_profit;
                combo = temp_combo;
            }
        }

        auto end = chrono::high_resolution_clock::now();

        //put time in microseconds
        chrono::duration<double, micro> duration = end - start;

        outFile << entries << " " << max << " " << combo.size() << " " << duration.count() << "microseconds" << endl;
        
        for( int i=0; i<combo.size(); i++){
            outFile << combo[i] << endl;
        }

        prices.clear();
    }

    inputFile2.close();

    outFile.close();

    return 0;
}

//return vector of combinations
vector<vector<int> > getCombinations(int n){
    int total = 1 << n;  // 2^n, combs is 2^n-1

    vector<vector<int> > output;

    //for example for n = 3, will loop through (001, 010, 011, 100, 101, 110, 111)
    for (int mask = 1; mask < total; ++mask) {
        vector<int> subset;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(i + 1);
                //if there is a 1 at the bit, add the i+1 index, so in 010, there is 1 at index 1, so we are adding 2 to the subset, because our subsets are in the form (1, 2, 3)
            }
        }

        output.push_back(subset);
    }

    return output;
}

//DISCUSSION: Worst and best case are 2^n, because we are running through 2^n combinations no matter what. 