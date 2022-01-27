#include "vector"
#include "algorithm"

template <typename T>
void RemoveDuplicates(std::vector<T>& elements){
    std::sort(std::begin(elements), std::end(elements));
    auto it = std::unique(std::begin(elements), std::end(elements));
    elements.erase(it, std::end(elements));
}