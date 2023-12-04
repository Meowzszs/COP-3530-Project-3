#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <string>
#include <limits>
#include <fstream>
#include "food_maps.h"

// Placeholder for pandas DataFrame
class DataFrame {

};

// pd.read_csv()
DataFrame read_csv(const char* filename) {
    return DataFrame();
}

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
    std::ifstream file(filename);
    std::string line, cell;
    while (getline(file, line)) {
        std::stringstream lineStream(line);
        std::string name;
        //indices: 0-carbs, 1-cholesterol, 2-fiber, 3-protein, 4-sugar, 5-saturated fat, 6-calcium, 7-iron, 8-potassium, 9-sodium, 10-vitamin A, 11-vitamin C
        std::vector<double> nutrients;

        // Read the food item's name
        getline(lineStream, name, ',');

        // Read each micronutrient value
        while (getline(lineStream, cell, ',')) {
            nutrients.push_back(std::stod(cell));
        }

        foodItems.emplace_back(name, nutrients);
    }
}

int main() {
    DataFrame ingredientsData = read_csv("ingredients.csv");

    std::vector<FoodItem> foodItems;
    populateFoodMap("ingredients.csv", foodItems);

    // Getting user choices including allergies
    auto user_choices = get_user_choices();
    int micronutrient_choice = std::get<0>(user_choices);
    std::string max_or_min = std::get<1>(user_choices);
    double value = std::get<2>(user_choices);
    std::string allergies = std::get<3>(user_choices);

    return 0;
}