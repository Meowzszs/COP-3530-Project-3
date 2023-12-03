#include <functional>
#include <string>

class FoodItem {
public:
    std::string category;
    std::string description;
    int nutrientDataBankNumber;

    bool operator==(const FoodItem &other) const {
        return nutrientDataBankNumber == other.nutrientDataBankNumber;
    }
};

// Custom hash function for FoodItem
namespace std {
    template <>
    struct hash<FoodItem> {
        std::size_t operator()(const FoodItem& item) const {
            return hash<int>()(item.nutrientDataBankNumber);
        }
    };
}
