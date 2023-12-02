//
// Created by Brandon Sibbitt on 12/2/23.
//

#include "bin_heap.h"
#include <cmath>
#include <iostream>

bin_heap::bin_heap(int capacity, bool high_or_low) {
    this->k = capacity;
    this->high_or_low = high_or_low;
    this->size = 0;
}

void bin_heap::heapifyUp() {
    int inserted = this->size - 1; // index of last node in heap
    int parentIndex = this->getParentIndex(inserted);
    // keeping K largest elements
    if (this->high_or_low) {
        while (inserted != 0 && this->container.at(inserted).second < this->container.at(parentIndex).second) {
            pair<FoodItem, double> parent = this->container.at(parentIndex);

            // swap parent and child data
            this->container.at(parentIndex) = this->container.at(inserted);
            this->container.at(inserted) = parent;

            inserted = parentIndex;
            parentIndex = this->getParentIndex(inserted);
        }
    }
    else {
        while (inserted != 0 && this->container.at(inserted).second > this->container.at(parentIndex).second) {
            pair<FoodItem, double> parent = this->container.at(parentIndex);

            // swap parent and child data
            this->container.at(parentIndex) = this->container.at(inserted);
            this->container.at(inserted) = parent;

            inserted = parentIndex;
            parentIndex = this->getParentIndex(inserted);
        }
    }
}

void bin_heap::heapifyDown() {

}

void bin_heap::insert(FoodItem& item, double nutrient_amount) {
    // ensures that elements with values smaller than the minimum in the heap do not get inserted
    if (this->size < this->k || nutrient_amount >= this->container.at(0).second) {
        this->container.push_back(make_pair(item, nutrient_amount));
        this->size++;
        this->heapifyUp();
    }
    if (this->size > this->k) {
        this->extract();
    }
}

FoodItem bin_heap::extract() {
    if (this->size > 0) {
        FoodItem root_item = this->container.at(0).first;
        // replace root node with the last node in the heap
        this->container.at(0) = this->container.at(this->size - 1);
        this->container.pop_back(); // remove last element in the heap
        this->heapifyDown();
        return root_item;
    }
    else {
        throw out_of_range("Error: cannot extract from binary heap with 0 elements");
    }
}

int bin_heap::getParentIndex(int child_index) {
    return floor((child_index - 1) * 0.5);
}

pair<int, int> bin_heap::getChildIndex(int parent_index) {
    return make_pair(2 * parent_index + 1, 2 * parent_index + 2);
}

void bin_heap::print() {
    for (unsigned int i = 0; i < this->container.size(); i++) {
        cout << this->container.at(i).first.description << endl;
    }
}