#include "food_maps.h"

// Constructor implementation for FoodItem
FoodItem::FoodItem(std::string category, std::string description, int nutrientDataBankNumber,
                   double carbohydrate, double cholesterol, double fiber, double protein,
                   double sugarTotal, double saturatedFat, double calcium, double iron,
                   double potassium, double sodium, double vitaminA, double vitaminC)
        : category(category), description(description), nutrientDataBankNumber(nutrientDataBankNumber),
          carbohydrate(carbohydrate), cholesterol(cholesterol), fiber(fiber), protein(protein),
          sugarTotal(sugarTotal), saturatedFat(saturatedFat), calcium(calcium), iron(iron),
          potassium(potassium), sodium(sodium), vitaminA(vitaminA), vitaminC(vitaminC) {}

// Map declarations
std::map<double, std::vector<FoodItem>> carbohydrateMap;
std::map<double, std::vector<FoodItem>> cholesterolMap;
std::map<double, std::vector<FoodItem>> fiberMap;
std::map<double, std::vector<FoodItem>> proteinMap;
std::map<double, std::vector<FoodItem>> sugarMap;
std::map<double, std::vector<FoodItem>> fatMap;
std::map<double, std::vector<FoodItem>> calciumMap;
std::map<double, std::vector<FoodItem>> ironMap;
std::map<double, std::vector<FoodItem>> potassiumMap;
std::map<double, std::vector<FoodItem>> sodiumMap;
std::map<double, std::vector<FoodItem>> vitaminAMap;
std::map<double, std::vector<FoodItem>> vitaminCMap;

// Function to populate maps
void populateMaps(const std::vector<FoodItem>& foodItems) {
    for (const auto& item : foodItems) {
        carbohydrateMap[item.carbohydrate].push_back(item);
        cholesterolMap[item.cholesterol].push_back(item);
        fiberMap[item.fiber].push_back(item);
        proteinMap[item.protein].push_back(item);
        sugarMap[item.sugarTotal].push_back(item);
        fatMap[item.saturatedFat].push_back(item);
        calciumMap[item.calcium].push_back(item);
        ironMap[item.iron].push_back(item);
        potassiumMap[item.potassium].push_back(item);
        sodiumMap[item.sodium].push_back(item);
        vitaminAMap[item.vitaminA].push_back(item);
        vitaminCMap[item.vitaminC].push_back(item);
    }
}