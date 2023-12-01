#ifndef FOOD_MAPS_H
#define FOOD_MAPS_H

#include <string>
#include <vector>
#include <map>

// Class to represent a food item and its nutrient content
class FoodItem {
public:
    std::string category;
    std::string description;
    int nutrientDataBankNumber;
    double carbohydrate;
    double cholesterol;
    double fiber;
    double protein;
    double sugarTotal;
    double saturatedFat;
    double calcium;
    double iron;
    double potassium;
    double sodium;
    double vitaminA;
    double vitaminC;

    // Constructor
    FoodItem(std::string category, std::string description, int nutrientDataBankNumber,
             double carbohydrate, double cholesterol, double fiber, double protein,
             double sugarTotal, double saturatedFat, double calcium, double iron,
             double potassium, double sodium, double vitaminA, double vitaminC);
};

// Maps for each micronutrient
extern std::map<double, std::vector<FoodItem>> carbohydrateMap;
extern std::map<double, std::vector<FoodItem>> cholesterolMap;
extern std::map<double, std::vector<FoodItem>> fiberMap;
extern std::map<double, std::vector<FoodItem>> proteinMap;
extern std::map<double, std::vector<FoodItem>> sugarMap;
extern std::map<double, std::vector<FoodItem>> fatMap;
extern std::map<double, std::vector<FoodItem>> calciumMap;
extern std::map<double, std::vector<FoodItem>> ironMap;
extern std::map<double, std::vector<FoodItem>> potassiumMap;
extern std::map<double, std::vector<FoodItem>> sodiumMap;
extern std::map<double, std::vector<FoodItem>> vitaminAMap;
extern std::map<double, std::vector<FoodItem>> vitaminCMap;

// Function to populate the maps
void populateMaps(const std::vector<FoodItem>& foodItems);

#endif