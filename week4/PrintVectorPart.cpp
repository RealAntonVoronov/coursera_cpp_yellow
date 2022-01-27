#include "iostream"
#include "vector"
#include "algorithm"

void PrintVectorPart(const std::vector<int>& nums){
    auto it = std::find_if(std::begin(nums), std::end(nums),
                           [](const int& x) {return x < 0;});
    while (it != std::begin(nums)){
        --it;
        std::cout << *it << " ";
    }
}