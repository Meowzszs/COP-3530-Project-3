//
// Created by Brandon Sibbitt on 12/2/23.
//

#include "bin_heap.h"
#include <cmath>
#include <iostream>

bin_heap::bin_heap(int capacity, bool high_or_low) {
    // set initial values for the heap according to values passed in via constructor
    this->k = capacity;
    this->high_or_low = high_or_low;
    this->size = 0;
}

void bin_heap::heapifyUp() {
    int inserted = this->size - 1; // index of last node in heap
    int parentIndex = this->getParentIndex(inserted);
    // keeping K largest elements
    if (this->high_or_low) {
        // as long as the inserted node is not at the root of the heap, and its value is less than its parent...
        while (inserted != 0 && this->container.at(inserted).second < this->container.at(parentIndex).second) {
            // swap the parent and the inserted node, then repeat the process
            this->swap(parentIndex, inserted);
            inserted = parentIndex;
            parentIndex = this->getParentIndex(inserted);
        }
    }
    // keeping K smallest elements
    else {
        // as long as the inserted node is not the root of the heap, and its value is greater than its parent...
        while (inserted != 0 && this->container.at(inserted).second > this->container.at(parentIndex).second) {
            // swap parent and the inserted node, then repeat
            this->swap(parentIndex, inserted);
            inserted = parentIndex;
            parentIndex = this->getParentIndex(inserted);
        }
    }
}

void bin_heap::heapifyDown() {
    int replaced = 0; // index of node that was replaced (will always be the root)
    pair<int, int> childIndices = this->getChildIndex(replaced);

    // keeping K largest elements
    if (this->high_or_low) {
        // checks if the current node has children and if its value is greater than either of its children
        while (childIndices.first < this->size && (this->container.at(replaced).second > this->container.at(childIndices.first).second || this->container.at(replaced).second > this->container.at(childIndices.second).second)) {
            // if so, swap the current node with the smaller of its two children
            int smaller_child = this->container.at(childIndices.first).second < this->container.at(childIndices.second).second ? childIndices.first : childIndices.second;
            this->swap(replaced, smaller_child);

            // repeat the process
            replaced = smaller_child;
            childIndices = this->getChildIndex(replaced);
        }
    }
    // keeping K smallest elements
    else {
        // checks if the current node has children and if its value is less than either of its children
        while (childIndices.first < this->size && (this->container.at(replaced).second < this->container.at(childIndices.first).second || this->container.at(replaced).second < this->container.at(childIndices.second).second)) {
            // if so, swap the current node with the larger of its two children
            int larger_child = this->container.at(childIndices.first).second > this->container.at(childIndices.second).second ? childIndices.first : childIndices.second;
            this->swap(replaced, larger_child);

            // repeat the process
            replaced = larger_child;
            childIndices = this->getChildIndex(replaced);
        }
    }
}

void bin_heap::insert(FoodItem& item, double nutrient_amount) {
    // ensures that once the heap is full, elements with values smaller than the minimum in the heap do not get inserted, which
    // should reduce the time it takes for the algorithm to complete
    if (this->size < this->k || (this->high_or_low ? nutrient_amount >= this->container.at(0).second : nutrient_amount <= this->container.at(0).second)) {
        this->container.push_back(make_pair(item, nutrient_amount));
        this->size++;
        this->heapifyUp(); // make sure heap properties are satisfied
    }

    // whenever the size exceeds the number of elements we want to track, remove the root
    if (this->size > this->k) {
        this->extract();
    }
}

FoodItem bin_heap::extract() {
    // make sure the heap is not empty
    if (this->size > 0) {
        FoodItem root_item = this->container.at(0).first;
        // replace root node with the last node in the heap
        this->container.at(0) = this->container.at(this->size - 1);
        this->container.pop_back(); // remove last element in the heap
        this->size--;
        this->heapifyDown(); // ensure heap properties are satisfied
        return root_item; // return the removed element
    }
    else {
        throw out_of_range("Error: cannot extract from binary heap with 0 elements");
    }
}

// returns the index of a node's parent
int bin_heap::getParentIndex(int child_index) {
    return floor((child_index - 1) * 0.5);
}

// returns the indices of a node's children
pair<int, int> bin_heap::getChildIndex(int parent_index) {
    return make_pair(2 * parent_index + 1, min(2 * parent_index + 2, this->size - 1));
}

// prints the heap's elements in order
void bin_heap::print() {
    for (unsigned int i = 0; i < this->container.size(); i++) {
        cout << this->container.at(i).first.name << ": " << this->container.at(i).second << endl;
    }
}

// swaps the data stored in two indices
void bin_heap::swap(int index1, int index2) {
    pair<FoodItem, double> temp = this->container.at(index1);
    this->container.at(index1) = this->container.at(index2);
    this->container.at(index2) = temp;
}
