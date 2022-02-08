#include "database.h"
#include "sstream"
#include "algorithm"

void Database::Add(const Date &date, const string &event) {
    if (database[date].second.insert(event).second){
        database[date].first.push_back(event);
    }
}
std::ostream& Database::Print(std::ostream& ostream) const {
    for (const auto& it : database){
        Date date = it.first;
        vector<string> events = it.second.first;
        for (const string& event : events){
            ostream << date << " " << event << std::endl;
        }
    }
    return ostream;
}
vector<string> Database::FindIf(std::function<bool(const Date &, const string &)> condition) const {
    vector<string> result;
    for (const auto& it : database) {
        Date date = it.first;
        vector<string> events = it.second.first;
        for (const string &event: events) {
            if (condition(date, event)) {
                std::stringstream ss;
                ss << date << " " << event;
                result.push_back(ss.str());
            }
        }
    }
    return result;
}
int Database::RemoveIf(std::function<bool(const Date&, const string&)> condition) {
    int res=0;
    set<Date> dates_to_remove;
    for (auto& it : database){
        auto remove_it = std::stable_partition(it.second.first.begin(), it.second.first.end(),
                                        [condition, it] (string& event){
            return !condition(it.first, event);});

        for (auto counter_it = remove_it; counter_it != it.second.first.end(); counter_it++){
            res++;
            it.second.second.erase(*counter_it);
        }
        it.second.first.erase(remove_it, it.second.first.end());
        if (it.second.first.empty()){
            dates_to_remove.insert(it.first);
        }
    }
    for (const Date& d : dates_to_remove){
        database.erase(d);
    }
    return res;
}
string Database::Last(const Date& date) const {
    auto upper_bound = database.upper_bound(date);
    if (upper_bound == database.begin()){
        throw std::invalid_argument("");
    }
    else {
        std::stringstream ss;
        upper_bound--;
        Date found = upper_bound->first;
        vector<string> events = upper_bound->second.first;
        ss << found << " " << *events.rbegin();
        return ss.str();
    }
}
