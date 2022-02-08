#include "date.h"
#include "iostream"
#include "iomanip"
#include "vector"

Date::Date(const size_t &year, const size_t &month, const size_t &day) {
    year_ = year;
    month_ = month;
    day_ = day;
}
size_t Date::GetDay() const{
    return day_;
}
size_t Date::GetMonth() const{
    return month_;
}
size_t Date::GetYear() const{
    return year_;
}
Date ParseDate(std::istream& ss){
    size_t year, month, day;
    ss >> year;
    ss.ignore(1);
    ss >> month;
    ss.ignore(1);
    ss >> day;
    return {year, month, day};
}
std::ostream& operator << (std::ostream& ostream, const Date& date){
    ostream << std::setfill('0');
    ostream << std::setw(4);
    ostream << date.GetYear() << "-";
    ostream << std::setw(2);
    ostream << date.GetMonth() << '-';
    ostream << std::setw(2) << date.GetDay();
    return ostream;
}
bool operator < (const Date& lhs, const Date& rhs){
    std::vector<size_t> l{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()};
    std::vector<size_t> r{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
    return l < r;
    }
bool operator == (const Date& lhs, const Date& rhs){
    std::vector<size_t> l{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()};
    std::vector<size_t> r{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
    return l == r;
}
bool operator != (const Date& lhs, const Date& rhs){
    return !(lhs == rhs);
}
bool operator <= (const Date& lhs, const Date& rhs){
    std::vector<size_t> l{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()};
    std::vector<size_t> r{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
    return l <= r;
}
bool operator > (const Date& lhs, const Date& rhs){
    return !(lhs <= rhs);
}
bool operator >= (const Date& lhs, const Date& rhs){
    std::vector<size_t> l{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()};
    std::vector<size_t> r{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
    return !(l <  r);
}