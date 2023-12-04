#ifndef PROJECT3_AVAV_BIN_HEAP_H
#define PROJECT3_AVAV_BIN_HEAP_H

#include "food_maps.h"
#include <vector>
using namespace std;

class bin_heap {
    void heapifyUp();
    void heapifyDown();
    int getParentIndex(int child_index);
    pair<int, int> getChildIndex(int parent_index);
    void swap(int index1, int index2);

    vector<pair<FoodItem, double>> container;
    // keep track of the k highest/lowest elements in the data stream
    int k = -1;
    int size = 0;
    // 0 (FALSE) = keep K lowest elements
    // 1 (TRUE)  = keep K highest elements
    bool high_or_low = 0;
public:
    bin_heap(int capacity = 10, bool high_or_low = 1);

    void insert(FoodItem& item, double nutrient_amt);
    FoodItem extract(); // get the root of the heap
    void print();
};

#endif //PROJECT3_AVAV_BIN_HEAP_H
