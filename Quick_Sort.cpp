//
// Created by User on 12/2/2023.
//
#include <string>
#include "food_maps.h"

int partition(std::vector<FoodItem>& list, int low, int high, int type) {
    int pivot = list[low].micronutrients[type];
    int up = low, down = high;

    while (up<down)
    {
        for(int i = up;i<high;i++) {
            if(list[up].micronutrients[type] > pivot)
                break;
            up++;
        }
        for(int i = high;i>low;i--) {
            if(list[down].micronutrients[type] < pivot)
                break;
            down--;
        }
        if(up<down)
            iter_swap(list.begin()+up,list.begin()+down);
    }
    iter_swap(list.begin()+low,list.begin()+down);
    return down;
}

void Quick_Sort(std::vector<FoodItem>& list, int low, int high, int type) {
    if(low < high)
    {
        int pivot = partition(list,low,high,type);
        Quick_Sort(list,low,pivot-1,type);
        Quick_Sort(list,pivot+1,high,type);
    }
}

//Quick_Sort implementation
Quick_Sort(foodItems, 0, foodItems.size()-1,micronutrient_choice);
if(max_or_min == "max") {
for(int i = 1;i<=10;i++) {
std::cout << foodItems[foodItems.size() - i].name << " " << foodItems[foodItems.size() - i].micronutrients[micronutrient_choice] << std::endl;
}
}
else {
for(int i = 0;i<10;i++) {
std::cout << foodItems[i].name << " " <<  foodItems[i].micronutrients[micronutrient_choice] << std::endl;
}
}
