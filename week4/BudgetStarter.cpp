#include "iostream"
#include "vector"
#include "algorithm"
#include "numeric"
using std::vector;

// years are from 2000 to 2099 we'll turn them to from 0 to 99
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
    for (int i = 0; i < year; i++){
        res += 365 + (leap_year(i));
    }
    vector<int> days_in_months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    auto end_it = days_in_months.begin() + month - 1;
    res += std::accumulate(days_in_months.begin(), end_it, 0);
    return res + day + (leap_year(year) and (month > 2));
}
int main() {
    int n_queries;
    std::cout.precision(25);
    vector<double> budget(CountDayNumber(99,12,31), 0);
    std::cin >> n_queries;
    for (size_t i=0; i < n_queries; i++){
        std::string command;
        std::cin >> command;
        int from_year, from_month, from_day;
        int to_year, to_month, to_day;
        char sep;
        std::cin >> from_year >> sep >> from_month >> sep >> from_day;
        std::cin >> to_year >> sep >> to_month >> sep >> to_day;
        from_year -= 2000;
        to_year -= 2000;
        int from = CountDayNumber(from_year, from_month, from_day);
        int to = CountDayNumber(to_year, to_month, to_day);
        //std::cout << "from" << from << ' ' << "to" << to << std::endl;
        if (command == "ComputeIncome"){
            std::cout << std::accumulate(budget.begin() + from, budget.begin() + to + 1, .0) << std::endl;
        }
        else if (command == "Earn"){
            double value;
            std::cin >> value;
            int range = to - from + 1;
            for (int day = from; day <= to; day++){
                budget[day] += value / range;
            }
        }
    }
    return 0;
}
