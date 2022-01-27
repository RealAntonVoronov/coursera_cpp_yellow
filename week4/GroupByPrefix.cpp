#include "iostream"
#include "vector"
using std::string, std::vector;

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        const string& substr){
    return std::equal_range(range_begin, range_end, substr, [substr](auto const& lhs, auto const& rhs) {
        size_t const size = substr.size();
        return lhs.compare(0, size, rhs, 0, size) < 0;
    });
}