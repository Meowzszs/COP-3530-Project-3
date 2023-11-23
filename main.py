import pandas as pd
import numpy as np

ingredientsData = pd.read_csv("ingredients.csv")

#function for user input of micronutrients
def get_user_choices():
    print("Select 1 or 2 micronutrients from the list:")
    print("1. Carbohydrate  2. Cholesterol  3. Fiber  4. Protein  5. Sugar  6. Saturated Fat")
    print("7. Calcium  8. Iron  9. Potassium  10. Sodium  11. Vitamin A  12. Vitamin C")

    # Get user input for micronutrient choices
    micronutrient_input = input("Enter the numbers corresponding to your choices (comma-separated): ")
    selected_micronutrients = [int(choice) for choice in micronutrient_input.split(',')]

    if len(selected_micronutrients) < 1 or len(selected_micronutrients) > 2:
        print("Please select 1 or 2 micronutrients. Try again.")
        return get_user_choices()

    # Get user input for high/low options
    high_low_input = input("Enter 'High' or 'Low' for each selected micronutrient (comma-separated): ")
    high_low_choices = [choice.strip().lower() for choice in high_low_input.split(',')]

    if len(high_low_choices) != len(selected_micronutrients):
        print("Please enter high/low choices for each selected micronutrient. Try again.")
        return get_user_choices()

    # Get user input for allergies
    allergies_input = input("Enter any foods you have allergies to (comma-separated): ")
    allergies = [allergy.strip().lower() for allergy in allergies_input.split(',')]

    return selected_micronutrients, high_low_choices, allergies

# Example usage (can delete)
micronutrients, high_low, allergies = get_user_choices()
print("Selected Micronutrients:", micronutrients)
print("High/Low Choices:", high_low)
print("Allergies:", allergies)


#implement function for knapsack algorithm