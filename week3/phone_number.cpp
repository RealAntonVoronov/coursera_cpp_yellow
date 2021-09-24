#include "phone_number.h"
#include "sstream"


PhoneNumber::PhoneNumber(const string &international_number) {
    stringstream is(international_number);
    char sign = is.get();
    getline(is, country_code_, '-');
    getline(is, city_code_, '-');
    getline(is, local_number_, '-');
    if (sign != '+' or country_code_.empty() or city_code_.empty() or local_number_.empty()){
            throw invalid_argument("invalid number");
        }
    }
string PhoneNumber::GetCityCode() const {
    return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}
string PhoneNumber::GetCountryCode() const {
    return country_code_;
}
string PhoneNumber::GetInternationalNumber() const {
    return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}
