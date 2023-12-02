//
// Created by User on 12/2/2023.
//
#include <string>
#include "food_maps.h"

int partition(std::map<std::string, std::vector<FoodItem>>& list, int low, int high) {
    int pivot = list[low];
    int up = low, down = high;

    while (up<down)
    {
        for(int i = up;i<high;i++) {
            if(list[up] > pivot)
                break;
            up++;
        }
        for(int i = high;i>low;i--) {
            if(list[down] < pivot)
                break;
            down--;
        }
        if(up<down)
            swap(&list[up],&list[down]);
    }
    swap(&list[low],&list[down])
    return down;
}

void Quick_Sort(std::map<std::string, std::vector<FoodItem>>& list, int low, int high) {
    if(low < high)
    {
        int pivot = partition(list,low,high);
        Quick_Sort(list,low,pivot-1);
        Quick_Sort(list,pivot+1,high);

    }

}


