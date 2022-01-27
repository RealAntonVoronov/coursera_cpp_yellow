#include "iostream"
#include "vector"
#include "algorithm"

std::vector<std::string> SplitIntoWords (const std::string& s){
    std::vector<std::string> res;
    auto begin = std::begin(s);
    auto end = std::find(std::begin(s), std::end(s), ' ');
    //std::cout << *prev << " " << *next << std::endl;
    while (end != std::end(s)) {
        res.push_back({begin, end});
        begin = ++end;
        end = std::find(begin, std::end(s), ' ');
    }
    res.push_back({begin, end});
    return res;
}