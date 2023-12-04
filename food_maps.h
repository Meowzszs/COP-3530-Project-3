#include <vector>
#include <string>

class FoodItem {
public:
    std::string name;
    std::vector<double> micronutrients;

    FoodItem() : name(""), micronutrients({}) {}

    FoodItem(std::string& name, std::vector<double>& micronutrients)
            : name(name), micronutrients(micronutrients) {}

    bool operator==(const FoodItem &other) const {
        return name == other.name;
    }
};