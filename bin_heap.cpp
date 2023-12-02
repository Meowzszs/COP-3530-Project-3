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
            this->swap(parentIndex, inserted);
            inserted = parentIndex;
            parentIndex = this->getParentIndex(inserted);
        }
    }
    else {
        while (inserted != 0 && this->container.at(inserted).second > this->container.at(parentIndex).second) {
            this->swap(parentIndex, inserted);
            inserted = parentIndex;
            parentIndex = this->getParentIndex(inserted);
        }
    }
}

void bin_heap::heapifyDown() {
    int replaced = 0; // index of node that was replaced (will always be the root)
    pair<int, int> childIndices = this->getChildIndex(replaced);

    if (this->high_or_low) {
        // checks if the current node has children and if its value is greater than either of its children
        while (childIndices.first < this->size && (this->container.at(replaced).second > this->container.at(childIndices.first).second
            || this->container.at(replaced).second > this->container.at(childIndices.second).second)) {
            int smaller_child = this->container.at(childIndices.first).second < this->container.at(childIndices.second).second ? childIndices.first : childIndices.second;
            this->swap(replaced, smaller_child);

            replaced = smaller_child;
            childIndices = this->getChildIndex(replaced);
        }
    }
    else {
        while (childIndices.first < this->size && (this->container.at(replaced).second < this->container.at(childIndices.first).second
            || this->container.at(replaced).second < this->container.at(childIndices.second).second)) {
            int larger_child = this->container.at(childIndices.first).second > this->container.at(childIndices.second).second ? childIndices.first : childIndices.second;
            this->swap(replaced, larger_child);

            replaced = larger_child;
            childIndices = this->getChildIndex(replaced);
        }
    }
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
        this->size--;
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
    return make_pair(2 * parent_index + 1, min(2 * parent_index + 2, this->size - 1));
}

void bin_heap::print() {
    for (unsigned int i = 0; i < this->container.size(); i++) {
        cout << this->container.at(i).first.description << endl;
    }
}

void bin_heap::swap(int index1, int index2) {
    pair<FoodItem, double> temp = this->container.at(index1);
    this->container.at(index1) = this->container.at(index2);
    this->container.at(index2) = temp;
}
