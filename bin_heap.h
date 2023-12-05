#ifndef PROJECT3_AVAV_BIN_HEAP_H
#define PROJECT3_AVAV_BIN_HEAP_H

#include "food_maps.h"
#include <vector>
using namespace std;

class bin_heap {
    // propagate heap properties up (insertion) or down (deletion)
    void heapifyUp();
    void heapifyDown();
    int getParentIndex(int child_index); // get the index of the parent of a node in the heap
    pair<int, int> getChildIndex(int parent_index); // get the indices of the children of a node in the heap
    void swap(int index1, int index2); // swap the data stored in 2 indices

    vector<pair<FoodItem, double>> container; // the actual container used to store the heap's data
    // keep track of the k highest/lowest elements in the data stream
    int k = -1;
    int size = 0; //
    // 0 (FALSE) = keep K lowest elements
    // 1 (TRUE)  = keep K highest elements
    bool high_or_low = 0;
public:
    // constructor
    bin_heap(int capacity = 10, bool high_or_low = 1);

    // insert a food item into the heap, along with a "priority" according to the user's chosen micronutrient
    void insert(FoodItem& item, double nutrient_amt);
    FoodItem extract(); // get the root of the heap
    void print(); // print the heap in order
};

#endif //PROJECT3_AVAV_BIN_HEAP_H
