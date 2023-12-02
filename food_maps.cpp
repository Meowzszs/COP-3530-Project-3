#include <unordered_map>
#include <array>
#include "food_maps.h"

//Each FoodItem has 12 micronutrient values
using MicronutrientArray = std::array<double, 12>;

std::unordered_map<FoodItem, MicronutrientArray> foodMap;

//merge and quicksort??
void populateFoodMap() {
    // Code to read from ingredients.csv and populate foodMap
    // For each line in the CSV, create a FoodItem and MicronutrientArray, then add to the map
}
