#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include <string>
#include <limits>
#include <fstream>

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
            FoodItem item_to_add = FoodItem("", vector<double>{});
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

int main() {
    std::vector<FoodItem> foodItems;
    populateFoodMap("../ingredients_v2.csv", foodItems);

    cout << foodItems.size() << endl;

    // Getting user choices including allergies
    auto user_choices = get_user_choices();
    int micronutrient_choice = std::get<0>(user_choices);
    std::string max_or_min = std::get<1>(user_choices);
    double value = std::get<2>(user_choices);
    std::string allergies = std::get<3>(user_choices);

    bin_heap foodHeap(10, max_or_min == "max" ? 1 : 0);
    for (unsigned int i = 0; i < foodItems.size(); i++) {
        foodHeap.insert(foodItems.at(i), foodItems.at(i).micronutrients.at(micronutrient_choice - 1));
    }
    foodHeap.print();

    return 0;
}