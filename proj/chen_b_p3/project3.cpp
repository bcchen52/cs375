#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <time.h>

using namespace std;

int greedy1(int max, vector<map<string, int> > items);
int greedy2(int max, vector<map<string, int> > items);
int backtrack(int max, vector<map<string, int> > items);
double max_possible(int curr_position, int rem_weight, vector<map<string, int> > items);

int main(int argc, char *argv[]){

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

    int algorithm = atoi(argv[3]);

    if(algorithm > 2 || algorithm < 0){
        cout << "Invalid algorithm chosen";
        return -1;
    }

    string line;

    clock_t start, end;

    while (getline(inputFile, line)){
        vector<map<string, int> > knapsack;
        istringstream iss(line);
        int x;
        int max;
        iss >> x;
        iss >> max;
        for (int i = 0; i < x; i++){
            getline(inputFile, line);
            istringstream iss_item(line);
            map<string, int> item;
            iss_item >> item["weight"];
            iss_item >> item["profit"];
            knapsack.push_back(item);
        }

        int profit;

        start = clock();
        if (algorithm == 0){
            profit = greedy1(max, knapsack);
        } else if (algorithm == 1){
            profit = greedy2(max, knapsack);
        } else {
            profit = backtrack(max, knapsack);
        }
        end = clock();
        
        outputFile << x << " " << profit << " " << ((double)(end - start)) / CLOCKS_PER_SEC * 1000 << endl;

        //using .sort() from algorithm, we can sort 
    }
    //ifargv2 ==1 

    //greedy a...
    //given an array of weight and profit, current weight, current profit, get max profit
    //greedy b...
    //use greedy a and check max profit
    //backtracking...
    //need bestset. 
    //use greedy a initially, but then you can increment 
}

int greedy1(int max, vector<map<string, int> > items){

    //sort items first
    sort(items.begin(), items.end(), [](const map<string, int>& a, const map<string, int>& b) {
        double ratioA = (double)a.at("profit") / a.at("weight");
        double ratioB = (double)b.at("profit") / b.at("weight");
        return ratioA > ratioB;
    });

    int current_weight = 0;
    int num_items = 0;
    int profit = 0;
    while (num_items < (int)items.size() && current_weight < max){
        current_weight += items.at(num_items)["weight"];
        profit += items.at(num_items)["profit"];
        if(current_weight <= max){
            num_items ++;
        } else {
            //current_weight -= items.at(num_items)["weight"];
            profit -= items.at(num_items)["profit"];
            //if we are here, revert to previous, that's the largest we can do
        }
    }
    
    return profit;
}

int greedy2(int max, vector<map<string, int> > items){
    int largest = 0;

    for (unsigned long i = 0; i < items.size(); i++){
        if (items.at(i)["profit"] > largest && items.at(i)["weight"] <= max){
            largest = items.at(i)["profit"];
        }
    }

    int greedy_result = greedy1(max, items);

    if (greedy_result > largest){
        return greedy_result;
    }

    return largest;
}

int backtrack(int max, vector<map<string, int> > items){

    //sort items first
    sort(items.begin(), items.end(), [](const map<string, int>& a, const map<string, int>& b) {
        double ratioA = (double)a.at("profit") / a.at("weight");
        double ratioB = (double)b.at("profit") / b.at("weight");
        return ratioA > ratioB;
    });

    int best_profit = greedy2(max, items);

    vector<vector<int>> nodes;
    //position, current weight, current profit
    //treat this is a stack for DFS

    vector<int> node; //which node, and whether or not

    vector<int> remaining_profit;

    int sum = 0;

    for (unsigned long i = 0; i < items.size(); i++){
        sum += items.at(i)["profit"];
        remaining_profit.push_back(0); //init
    }

    for (unsigned long i = 1; i < items.size(); i++){
        sum -= items.at(i)["profit"];
        remaining_profit.at(i) = sum;
    }
    //each position will have max profit at that position onward, so 0 is everything

    nodes.push_back({-1, 0, 0});

    while (nodes.size() > 0){
        node = nodes.back();
        nodes.pop_back();
        int position = node.at(0);
        int weight = node.at(1);
        int profit = node.at(2);
        //check if better, then backtrack

        if (weight <= max && profit > best_profit) {
            best_profit = profit;
        }

        if (position > -1){
            //this is so the initial node doesn't break by comparing what doesn't exist
            if (position + 1 < (int)items.size() && items.at(position+1)["weight"] <= max && profit + max_possible(position, max-weight, items) > best_profit){
                nodes.push_back({position+1, weight, profit});
                nodes.push_back({position+1, weight + items.at(position+1)["weight"], profit + items.at(position+1)["profit"]});
            }
        } else {
            nodes.push_back({position+1, weight, profit});
            nodes.push_back({position+1, weight + items.at(position+1)["weight"], profit + items.at(position+1)["profit"]});
        }
        //position will tell us which item we are looking at
    }

    return best_profit;
}

double max_possible(int curr_position, int rem_weight, vector<map<string, int> > items){
    //we assume positiion is already here
    double profit = 0;
    while (curr_position + 1 < (int)items.size() && rem_weight > 0){
        if (items.at(curr_position + 1)["weight"] <= rem_weight){
            profit += items.at(curr_position + 1)["profit"];
        } else {
            profit += (double)items.at(curr_position + 1)["profit"] * ((double)rem_weight/(double)items.at(curr_position + 1)["weight"]);
            //this breaks without a bunch of doubles
        }        
        rem_weight -= items.at(curr_position + 1)["weight"];
        curr_position ++;
    }
    return profit;
}