#include <vector>
#include <string>

// Definition of the FoodItem class
class FoodItem {
public:
    // Attributes of a FoodItem
    std::string name;
    std::vector<double> micronutrients;

    // Default constructor initializing attributes
    FoodItem() : name(""), micronutrients({}) {}

    // Parameterized constructor for creating a FoodItem with specified name and micronutrients
    FoodItem(std::string& name, std::vector<double>& micronutrients)
            : name(name), micronutrients(micronutrients) {}

    // Overloaded equality operator for comparing FoodItems based on their names
    bool operator==(const FoodItem &other) const {
        return name == other.name;
    }
};