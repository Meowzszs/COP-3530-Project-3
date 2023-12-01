#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <string>
#include "food_maps.h"

// Placeholder for pandas DataFrame
class DataFrame {

};

// pd.read_csv()
DataFrame read_csv(const char* filename) {
    // Assuming reading CSV functionality is not needed for this example
    return DataFrame();
}

// Function for user input of micronutrients
std::tuple<std::vector<int>, std::vector<double>, std::vector<std::string>> get_user_choices() {
    std::cout << "Select 1 or 2 micronutrients from the list:" << std::endl;
    std::cout << "1. Carbohydrate  2. Cholesterol  3. Fiber  4. Protein  5. Sugar  6. Saturated Fat" << std::endl;
    std::cout << "7. Calcium  8. Iron  9. Potassium  10. Sodium  11. Vitamin A  12. Vitamin C" << std::endl;

    // Get user input for micronutrient choices
    std::cout << "Enter the numbers corresponding to your choices (comma-separated):" << std::endl;
    std::string micronutrient_input;
    std::getline(std::cin, micronutrient_input);
    std::istringstream micronutrient_stream(micronutrient_input);
    std::vector<int> selected_micronutrients;
    int choice;
    while (micronutrient_stream >> choice) {
        selected_micronutrients.push_back(choice);
        if (micronutrient_stream.peek() == ',')
            micronutrient_stream.ignore();
    }

    if (selected_micronutrients.size() < 1 || selected_micronutrients.size() > 2) {
        std::cout << "Please select 1 or 2 micronutrients. Try again." << std::endl;
        return get_user_choices();
    }

    // Get user input for desired nutrient levels
    std::cout << "Enter the desired level for each selected micronutrient (comma-separated):" << std::endl;
    std::string levels_input;
    std::getline(std::cin, levels_input);
    std::istringstream levels_stream(levels_input);
    std::vector<double> nutrient_levels;
    double level;
    while (levels_stream >> level) {
        nutrient_levels.push_back(level);
        if (levels_stream.peek() == ',')
            levels_stream.ignore();
    }

    if (nutrient_levels.size() != selected_micronutrients.size()) {
        std::cout << "Please enter a level for each selected micronutrient. Try again." << std::endl;
        return get_user_choices();
    }

    // Get user input for allergies
    std::cout << "Enter any foods you have allergies to (comma-separated):" << std::endl;
    std::string allergies_input;
    std::getline(std::cin, allergies_input);
    std::istringstream allergies_stream(allergies_input);
    std::vector<std::string> allergies;
    std::string allergy;
    while (std::getline(allergies_stream, allergy, ',')) {
        std::transform(allergy.begin(), allergy.end(), allergy.begin(), ::tolower);
        allergies.push_back(allergy);
    }

    return std::make_tuple(selected_micronutrients, nutrient_levels, allergies);
}

int main() {
    DataFrame ingredientsData = read_csv("ingredients.csv");

    // HYPOTHETICAL - FOR CONVERTING MAP TO FOOD ITEMS
    //std::vector<FoodItem> foodItems = convertDataFrameToFoodItems(ingredientsData);

    // Populate the maps with food item data
    //WILL NEED TO POPULATE MAP AFTER CONVERT TO FOOD ITEM
    //populateMaps(foodItems);

    // Getting user choices
    auto [micronutrients, nutrient_levels, allergies] = get_user_choices();

    // Displaying selected micronutrients and their desired levels
    std::cout << "Selected Micronutrients and Desired Levels: ";
    for (size_t i = 0; i < micronutrients.size(); ++i) {
        std::cout << micronutrients[i] << " (" << nutrient_levels[i] << ") ";
    }
    std::cout << std::endl;

    // Displaying allergies
    std::cout << "Allergies: ";
    for (const std::string& allergy : allergies) {
        std::cout << allergy << " ";
    }
    std::cout << std::endl;
    return 0;
}