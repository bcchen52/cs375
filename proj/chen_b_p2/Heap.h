#ifndef HEAP_H
#define HEAP_H

#include <vector>
using namespace std;

class Heap {
    private:
        vector<int> heap;
        vector<int> handle;
        int size;
        int max_range;

    public:
        Heap();

        Heap(int n);

        int findContestant(int k, bool p);
        
        void insertContestant(int k, int s);
        
        int eliminateWeakest(bool p);
        
        void earnPoints(int k, int p);
        
        void losePoints(int k, int p);

        void showContestants();
        
        void showHandles();
        
        void showLocation(int k);
        
        void crownWinner();

        void percolate_up(int pos, int k);

        void percolate_down(int pos, int k);
};

#endif