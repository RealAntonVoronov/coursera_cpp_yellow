#include "iostream"
#include "algorithm"
#include "set"

using std::set;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border){
    auto it_lower = numbers.lower_bound(border);
    if (it_lower != numbers.begin()){
        int dist_1 = std::abs(*(it_lower) - border);
        int dist_2 = std::abs(*(std::prev(it_lower)) - border);
        if (dist_1 < dist_2){
            return it_lower;
        }
        else return std::prev(it_lower);
    }
    else return it_lower;
}

int main() {
    set<int> numbers = {1, 4, 7, 10};
    std::cout <<
              *FindNearestElement(numbers, 8) << " " <<
              *FindNearestElement(numbers, 3) << " " <<
              *FindNearestElement(numbers, 5) << " " <<
              *FindNearestElement(numbers, 6) << " " <<
              *FindNearestElement(numbers, 100) << std::endl;

    set<int> empty_set;

    std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
    return 0;
}