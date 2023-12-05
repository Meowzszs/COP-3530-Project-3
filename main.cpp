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

// Function to populate the foodItems vector from a CSV file
void populateFoodMap(const std::string& filename, std::vector<FoodItem>& foodItems) {
    // Open the CSV file
    std::fstream dataFile(filename);
    // Strings to store a line and a cell from the CSV
    std::string line, cell;

    // Check if the file is open
    if (dataFile.is_open()) {
        // Inform that the file is open
        cout << "file is open" << endl;

        // Read each line in the CSV file
        while (getline(dataFile, line)) {
            // Create a new FoodItem for each line
            FoodItem item_to_add = FoodItem();

            // Initialize the position of data in the CSV
            int data_position = 0;
            cout << line << endl;

            // Use stringstream to separate cells in the line
            std::stringstream lineStream(line);

            // Vector to store nutrient values for the current food item
            std::vector<double> nutrients;

            // Read each micronutrient value separated by commas
            while (getline(lineStream, cell, ',')) {
                // The first cell contains the name of the food item
                if (data_position == 0) {
                    item_to_add.name = cell;
                }
                    // For cells beyond the first, add the nutrient values to the micronutrients vector
                else if (data_position > 1) {
                    item_to_add.micronutrients.push_back(std::stod(cell));
                }
                // Increment the data position
                data_position++;
            }
            // Add the populated FoodItem to the foodItems vector
            foodItems.push_back(item_to_add);
        }
    }
    dataFile.close();
}

int partition(std::vector<FoodItem>& list, int low, int high, int type) {
    int pivot = list[low].micronutrients[type];
    int up = low, down = high;

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
    Quick_Sort(foodItems, 0, foodItems.size()-1,micronutrient_choice-1);
    if(max_or_min == "max") {
        for(int i = 1;i<=10;i++) {
            std::cout << foodItems[foodItems.size() - i].name << " " << foodItems[foodItems.size() - i].micronutrients[micronutrient_choice-1] << std::endl;
        }
    }
    else {
        for(int i = 0;i<10;i++) {
            std::cout << foodItems[i].name << " " <<  foodItems[i].micronutrients[micronutrient_choice-1] << std::endl;
        }
    }
    auto afterQuick = std::chrono::high_resolution_clock::now();
    double QuickDuration = chrono::duration_cast<chrono::milliseconds>(afterHeap - beforeHeap).count();
    cout << "The Quick sort algorithm required " << QuickDuration << " milliseconds to complete." << endl;

    return 0;
}