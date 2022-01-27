#include "iostream"
#include "vector"
using std::string, std::vector;
bool first_elem_comp(const string& lhs, const string& rhs){
    return lhs[0] < rhs[0];
}
template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        char prefix){
    auto not_less_it = std::lower_bound(range_begin, range_end, string{prefix}, first_elem_comp);
    auto higher_it = std::upper_bound(range_begin, range_end, string{prefix}, first_elem_comp);
    return {not_less_it, higher_it};
}