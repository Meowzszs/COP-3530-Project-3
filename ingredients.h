#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <vector>
#include <string>

// Placeholder for pandas DataFrame
class DataFrame {

};

// pd.read_csv() equivalent
DataFrame read_csv(const char* filename);

// Function for user input of micronutrients
std::tuple<std::vector<int>, std::vector<std::string>, std::vector<std::string>> get_user_choices();

#endif // INGREDIENTS_H
