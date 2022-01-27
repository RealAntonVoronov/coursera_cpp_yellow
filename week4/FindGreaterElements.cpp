#include "vector"
#include "algorithm"
#include "set"

template <typename T>
std::vector<T> FindGreaterElements (const std::set<T>& elements, const T& border){
    auto it = std::begin(elements);
    while (it != std::end(elements) && *it > border){
        it++;
    }
    return {it, std::end(elements)};
}