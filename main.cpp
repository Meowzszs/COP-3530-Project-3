#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include <string>
#include <limits>
#include <fstream>
#include <chrono>

#include "bin_heap.h"

// Function for user input of micronutrients
std::tuple<int, std::string, double, std::string> get_user_choices() {
    std::cout << "Select a micronutrient from the list:" << std::endl;
    std::cout << "1. Carbohydrate  2. Cholesterol  3. Fiber  4. Protein  5. Sugar  6. Saturated Fat" << std::endl;
    std::cout << "7. Calcium  8. Iron  9. Potassium  10. Sodium  11. Vitamin A  12. Vitamin C" << std::endl;

    // Get user input for micronutrient choice
    std::cout << "Enter the number corresponding to your choice:" << std::endl;
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Ask for max or min
    std::string max_or_min;
    std::cout << "Do you want the value to be a maximum or minimum? (Enter 'max' or 'min')" << std::endl;
    std::getline(std::cin, max_or_min);

    // Get the value for the chosen micronutrient
    double value;
    std::cout << "Enter the value for your chosen micronutrient:" << std::endl;
    std::cin >> value;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Ask for allergies
    std::string allergies;
    std::cout << "Enter any allergies (comma-separated, enter 'none' if no allergies):" << std::endl;
    std::getline(std::cin, allergies);

    return std::make_tuple(choice, max_or_min, value, allergies);
}

void populateFoodMap(const std::string& filename, std::vector<FoodItem>& foodItems) {
    std::fstream dataFile(filename);
    std::string line, cell;
    if (dataFile.is_open()) {
        cout << "file is open" << endl;
        while (getline(dataFile, line)) {
            FoodItem item_to_add = FoodItem();
            int data_position = 0;
            cout << line << endl;
            std::stringstream lineStream(line);
            //indices: 0-carbs, 1-cholesterol, 2-fiber, 3-protein, 4-sugar, 5-saturated fat, 6-calcium, 7-iron, 8-potassium, 9-sodium, 10-vitamin A, 11-vitamin C
            std::vector<double> nutrients;

            // Read each micronutrient value
            while (getline(lineStream, cell, ',')) {
                if (data_position == 0) {
                    item_to_add.name = cell;
                }
                else if (data_position > 1) {
                    item_to_add.micronutrients.push_back(std::stod(cell));
                }
                data_position++;
            }
            foodItems.push_back(item_to_add);
        }
    }

    dataFile.close();
}

int partition(std::vector<FoodItem>& list, int low, int high, int type) {
    //Declares the pivot as the first in the array
    int pivot = list[low].micronutrients[type];
    int up = low, down = high;

    //goes through array arranging it so that all is smaller on the left side of the pivot and larger on the right
    while (up<down)
    {
        for(int i = up;i<high;i++) {
            if(list[up].micronutrients[type] > pivot)
                break;
            up++;
        }
        for(int i = high;i>low;i--) {
            if(list[down].micronutrients[type] < pivot)
                break;
            down--;
        }
        if(up<down)
            iter_swap(list.begin()+up,list.begin()+down);
    }
    iter_swap(list.begin()+low,list.begin()+down);
    return down;
}

void Quick_Sort(std::vector<FoodItem>& list, int low, int high, int type) {
    //Sorts around a pivot while dividing the array
    if(low < high)
    {
        int pivot = partition(list,low,high,type);
        Quick_Sort(list,low,pivot-1,type);
        Quick_Sort(list,pivot+1,high,type);
    }
}

int main() {
    std::vector<FoodItem> foodItems;
    populateFoodMap("../ingredients_v2.csv", foodItems);

    // Getting user choices including allergies
    auto user_choices = get_user_choices();
    int micronutrient_choice = std::get<0>(user_choices);
    std::string max_or_min = std::get<1>(user_choices);
    double value = std::get<2>(user_choices);
    std::string allergies = std::get<3>(user_choices);

    auto beforeHeap = std::chrono::high_resolution_clock::now();
    bin_heap foodHeap(10, max_or_min == "max" ? 1 : 0);
    for (unsigned int i = 0; i < foodItems.size(); i++) {
        foodHeap.insert(foodItems.at(i), foodItems.at(i).micronutrients.at(micronutrient_choice - 1));
    }
    auto afterHeap = std::chrono::high_resolution_clock::now();
    double heapDuration = chrono::duration_cast<chrono::milliseconds>(afterHeap - beforeHeap).count();

    foodHeap.print();
    cout << "The modified heap sort algorithm required " << heapDuration << " milliseconds to complete." << endl;

    // run QuickSort in a similar fashion down here
    //          vvv     vvv
    //Quick_Sort implementation
    auto beforeQuick = std::chrono::high_resolution_clock::now();
    //input's the lowest index and the heighest as well as the type of micronutrient subtracted by 1
    Quick_Sort(foodItems, 0, foodItems.size()-1,micronutrient_choice-1);
    if(max_or_min == "max") {
        for(int i = 1;i<=10;i++) {
            //print max
            std::cout << foodItems[foodItems.size() - i].name << " " << foodItems[foodItems.size() - i].micronutrients[micronutrient_choice-1] << std::endl;
        }
    }
    else {
        for(int i = 0;i<10;i++) {
            //print min
            std::cout << foodItems[i].name << " " <<  foodItems[i].micronutrients[micronutrient_choice-1] << std::endl;
        }
    }
    auto afterQuick = std::chrono::high_resolution_clock::now();
    double QuickDuration = chrono::duration_cast<chrono::milliseconds>(afterQuick - beforeQuick).count();
    cout << "The Quick sort algorithm required " << QuickDuration << " milliseconds to complete." << endl;

    return 0;
}