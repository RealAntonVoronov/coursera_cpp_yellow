#pragma once

#include "map"
#include "set"
#include "date.h"
#include "vector"
#include "string"
#include "iostream"
#include "functional"
using std::vector, std::string, std::pair, std::map, std::set;
class Database{
public:
    void Add(const Date& date, const string& event);
    std::ostream& Print(std::ostream& ostream) const;
    vector<string> FindIf(std::function<bool(const Date& date, const string& event)> condition) const;
    int RemoveIf(std::function<bool(const Date& date, const string& event)> condition);
    string Last(const Date& date) const;
private:
    map<Date, pair<vector<string>, set<string>>> database;
};