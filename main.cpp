#include <iostream>
#include <vector>
#include <sstream>
#include "ingredients.h"

int main() {
    // Placeholder for DataFrame
    DataFrame ingredientsData = read_csv("ingredients.csv");

    // (can delete)
    auto [micronutrients, high_low, allergies] = get_user_choices();
    std::cout << "Selected Micronutrients: ";
    for (int nutrient : micronutrients) std::cout << nutrient << " ";
    std::cout << std::endl;

    std::cout << "High/Low Choices: ";
    for (const std::string& choice : high_low) std::cout << choice << " ";
    std::cout << std::endl;

    std::cout << "Allergies: ";
    for (const std::string& allergy : allergies) std::cout << allergy << " ";
    std::cout << std::endl;

    return 0;
}
