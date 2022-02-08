#pragma once

#include "iostream"
#include "string"

class Date{
public:
    Date(const size_t& year, const size_t& month, const size_t& day);
    size_t GetDay() const;
    size_t GetMonth() const;
    size_t GetYear() const;
private:
    size_t year_, month_, day_;
};
Date ParseDate(std::istream& ss);
std::ostream& operator << (std::ostream& ostream, const Date& date);
bool operator < (const Date& lhs, const Date& rhs);
bool operator <= (const Date& lhs, const Date& rhs);
bool operator > (const Date& lhs, const Date& rhs);
bool operator >= (const Date& lhs, const Date& rhs);
bool operator == (const Date& lhs, const Date& rhs);
bool operator != (const Date& lhs, const Date& rhs);