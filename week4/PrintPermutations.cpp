#include "iostream"
#include "vector"
#include "algorithm"
#include "numeric"

void PrintVector(const std::vector<int>& v){
    for (const int& x : v){
        std:: cout << x << " ";
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    //fills vector with increasing values. Reverse iterators to fill it from the end
    std::iota(std::rbegin(numbers), std::rend(numbers), 1);
    PrintVector(numbers);
    std::cout << std::endl;
    //could also use prev_permutation without changing default comparator
    while (std::next_permutation(std::begin(numbers), std::end(numbers),
                                 [](const int& lhs, const int& rhs) {return lhs > rhs;})){
        PrintVector(numbers);
        std::cout << std::endl;
    }
    return 0;
}