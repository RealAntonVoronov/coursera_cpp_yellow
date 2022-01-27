#include "iostream"
#include "vector"
#include "algorithm"
#include "numeric"
using std::vector;

// years are from 1700 to 2099
bool leap_year(int year){
    if (year % 4 == 0){
        if (year % 400 == 0){
            return true;
        }
        else if (year % 100 == 0){
            return false;
        }
        else return true;
    }
    return false;
}
int CountDayNumber(const int& year, const int& month, const int& day) {
    int res = 0;
    for (int i = 1700; i < year; i++){
        res += 365 + (leap_year(i));
    }
    vector<int> days_in_months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    auto end_it = days_in_months.begin() + month - 1;
    res += std::accumulate(days_in_months.begin(), end_it, 0);
    return res + day - 1 + (leap_year(year) and (month > 2));
}
int main() {
    size_t n_infos;
    vector<size_t> budget(CountDayNumber(2099,12,31) + 1,0);
    vector<size_t> partial_sums(CountDayNumber(2099,12,31) + 1,0);
    std::cin >> n_infos;
    for (size_t i=0; i < n_infos; i++) {
        int from_year, from_month, from_day;
        char sep;
        std::cin >> from_year >> sep >> from_month >> sep >> from_day;
        int from = CountDayNumber(from_year, from_month, from_day);
        int value;
        std::cin >> value;
        budget[from] += value;
    }
    std::partial_sum(budget.begin(), budget.end(), partial_sums.begin());
    /*for (size_t i : budget){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (size_t i : partial_sums){
        std::cout << i << " ";
    }
    std::cout << std::endl;*/
    size_t n_queries;
    std::cin >> n_queries;
    for(size_t i = 0; i < n_queries; i++){
        int to_year, to_month, to_day;
        int from_year, from_month, from_day;
        char sep;
        std::cin >> from_year >> sep >> from_month >> sep >> from_day;
        std::cin >> to_year >> sep >> to_month >> sep >> to_day;
        int from = CountDayNumber(from_year, from_month, from_day);
        int to = CountDayNumber(to_year, to_month, to_day);
        std::cout << partial_sums[to] - partial_sums[from] + budget[from] << std::endl;
    }
    return 0;
}
