#include "Heap.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

Heap::Heap(){
    size = 0;
    heap = vector<int>(1);
    handle = vector<int>(1);
    max_range = 0;
}

Heap::Heap(int n){
    size = 0;
    heap = vector<int>(n+1);
    handle = vector<int>(n+1);
    max_range = n;
}

int Heap::findContestant(int k, bool p){
    //we use bool p, if used internally to find existance, don't print and use return values that we can use for other stuff
    if (k > max_range){
        if (p){
            cout << "Out of range." << endl; // I belive we assume this will not happen
        }
        return -1;
    } 
    
    if (handle.at(k) != 0){
        if (p){
            cout << "Contestant <" << k << "> in the extended heap with score <" << heap.at(handle.at(k)) << ">." << endl;
        }
        return handle.at(k);
    }

    if (p){
        cout << "Contestant <" << k << "> not in the extended heap." << endl;
    }
    return -2;
        
}
        
void Heap::insertContestant(int k, int s){
    if (size == max_range){
        cout << "Contestant <" << k << "> could not be inserted because the extended heap is full." << endl;
        return;
    } 

    if (findContestant(k, false) > 0){
        cout << "Contestant <" << k << "> is already in the extended heap: cannot insert." << endl;
        return;
    }

    //add it to the heap
    size ++;
    handle.at(k) = size; //your pos will be the last
    heap.at(size) = s;
    percolate_up(size, k);
    cout << "Contestant <" << k << "> inserted with initial score <" << s << ">." << endl;
}

int Heap::eliminateWeakest(bool p){
    //we pop off, change the sizes, then put last size into first position, then percolate down
    if (size == 0){
        if (p){
            cout << "No contestant can be eliminated since the extended heap is empty." << endl;
        }
        return 0;
    }

    int root_index;
    int root_score = heap.at(1);

    if (size == 1){
        //if only one, we need to remove root from handle and from heap
        for (int i = 1; i <= max_range; i++){
            if (handle.at(i) == 1){
                root_index = i; //this is k
            }
        }

        if (p){
            //this is when we want to remove the last node
            heap.at(1) = 0;
            handle.at(root_index) = 0;
            size --;
        } else{
            //for crownWinner, we don't want to remove 1. Rather, keep and return our k
            return root_index; 
        }
    } else {
        //remove first element
        //first, find the k of the the last element
        int new_root_index;
        for (int i = 1; i <= max_range; i++){
            if (handle.at(i) == size){
                new_root_index = i;
            } else {
                if (handle.at(i) == 1){
                    root_index = i;
                }
            }
        }
        //now, we know the root and the one we will be replacing
        //replace the root
        heap.at(1) = heap.at(size);

        handle.at(root_index) = 0;
        handle.at(new_root_index) = 1;
        size--;

        percolate_down(1, new_root_index);
    }
    if (p){
        cout << "Contestant <" << root_index << "> with current lowest score <" << root_score << "> eliminated." << endl;
    }
    return -1; 
}

void Heap::earnPoints(int k, int p){
    //we find, add points, and thus percolate down
    int find = findContestant(k, false);

    if (find > 0){
        heap.at(handle.at(k)) += p;
        percolate_down(handle.at(k), k);
        cout << "Contestant <" << k << ">'s score increased by <" << p << "> points to <" << heap.at(handle.at(k)) << ">." << endl;
        return;
    } 

    //NOTE: find will be < 0 if k out of range or k not found. But, k will always be in range, so assume it means k not found
    cout << "Contestant <" << k <<"> not in the extended heap." << endl;
}

void Heap::losePoints(int k, int p){
    //we find, lower points, and then percolate up
    int find = findContestant(k, false);

    if (find > 0){
        heap.at(handle.at(k)) -= p;
        percolate_up(handle.at(k), k);
        cout << "Contestant <" << k << ">'s score decreased by <" << p << "> points to <" << heap.at(handle.at(k)) << ">." << endl;
        return;
    } 

    //NOTE: find will be < 0 if k out of range or k not found. But, k will always be in range, so assume it means k not found
    cout << "Contestant <" << k << "> not in the extended heap." << endl;
}

void Heap::showContestants(){
    //loop through heap in array order

    //first, we need to get where each contestant is
    vector<int> temp_arr = vector<int>(size + 1);

    for (int i = 1; i <= max_range; i++){
        if (handle.at(i) != 0){
            temp_arr[handle.at(i)] = i;
        } //this should work out, assuming we updated our size and handle array properly
    }

    for (int i = 1; i <= size; i++){
        //temp_arr.at(i) should give you k
        //heap.at(i) should give you the score
        cout << "Contestant <" << temp_arr.at(i) << "> in extended heap location <" << i << "> with score <" << heap.at(i) << ">." << endl;
    }
}

void Heap::showHandles(){
    //loop through handles array
    int val;
    for (int i = 1; i <= max_range; i++){
        val = handle.at(i);
        if (val == 0){
            cout << "There is no Contestant <" << i << "> in the extended heap: handle[<" << i << ">] = -1." << endl;
            //not actually -1, following the format of assignment sheet. I used 0 as default value, as indexes 1 to n.
        } else {
            cout << "Contestant <" << i << "> stores in extended heap location <" << val << ">." << endl;
        }
    }
}

void Heap::showLocation(int k){
    //grab handles.at(k), check first
    int find = findContestant(k, false);

    if (find > 0){
        cout << "FOund, sup." << endl;
        return;
    }

    cout << "This is no Contestant k" << endl;
}

void Heap::crownWinner(){
    //while size > 1, eliminateWeakest()?

    int running = eliminateWeakest(false);
    //running is either 0 for empty, -1 for multiple, or k > 0 if we reached one

    if (running == 0){
        cout << "The extended heap is empty, there is no winner." << endl;
        return;
    }

    //at this point, either -1 or k > 0

    while(running < 0){
        running = eliminateWeakest(false);
        //eventually, this will be -1 once we are full
    }

    //at this point, running = k > 0, meaning we are at the final node, at position 1
    
    cout << "Contestant <" << running << "> wins with score <" << heap.at(1) << ">!" << endl;
}

void Heap::percolate_down(int pos, int k){
    //given contestant k currently held at pos 

    //pos * 2 means left child exists
    if (pos * 2 > size){
        return;
    }

    //first check if left child greater
    bool left_violate = false;
    bool right_violate = false;

    if (heap.at(pos*2) < heap.at(pos)){
        //for 4, laft is true
        left_violate = true;
    }

    if ((pos * 2) + 1 <= max_range){ //if right child
        if (heap.at((pos * 2) + 1) < heap.at(pos)){
            right_violate = true;
        }

        if (left_violate && right_violate){
            if (heap.at((pos * 2) + 1) < heap.at(pos*2)){
                left_violate = false; //if right is less than left, we use right
            } else {
                right_violate = false; //if right is less than left OR equal, use left
            }
        }
    }

    if (left_violate || right_violate){
        //at this point, we should already know which child node we are replacing.
        int child_pos = pos * 2;
        if (right_violate){
            child_pos = (pos * 2) + 1;
        }  

        int child_handle_index = 0;
        for (int i = 1; i <= max_range; i++){ // <= because 1 indexing to n
            if (handle.at(i) == child_pos){
                child_handle_index = i;
                break;
            }
        }

        //first, swap them in handle
        handle.at(child_handle_index) = pos;
        handle.at(k) = child_pos;

        //then, swap their scores in heap
        int temp = heap.at(child_pos);
        heap.at(child_pos) = heap.at(pos);
        heap.at(pos) = temp;

        percolate_down(child_pos, k);
    }
}

void Heap::percolate_up(int pos, int k){
    //we pass in k, so we can easily locate the contestant in handle

    //if anything greater than 1, it will have a parent.
    if (pos == 1){
        return;
    }

    int parent_pos = pos/2; //get parent index
    
    if (heap.at(parent_pos) > heap.at(pos)){
        //we need to find which contestant the parent is
        int parent_handle_index = 0;
        for (int i = 1; i <= max_range; i++){ // <= because 1 indexing to n
            if (handle.at(i) == parent_pos){
                parent_handle_index = i;
                break;
            }
        }

        //first, swap them in handle
        handle.at(parent_handle_index) = pos;
        handle.at(k) = parent_pos;

        //then, swap their scores in heap
        int temp = heap.at(parent_pos);
        heap.at(parent_pos) = heap.at(pos);
        heap.at(pos) = temp;

        percolate_up(parent_pos, k); //we only continue if we need to, aka if we do end up swapping, we would need to keep checking to maintain min heap
    }
}