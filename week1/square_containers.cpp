#include "vector"
#include "iostream"
#include "utility"
#include "map"

template <typename T> std::vector<T> operator * (const std::vector<T>& lhs, const std::vector<T>& rhs);
template <typename First, typename Second>
std::pair<First, Second> operator * (const std::pair<First, Second>& lhs, const std::pair<First, Second>& rhs);
template <typename Key, typename Value>
std::map<Key, Value> operator * (const std::map<Key, Value>& lhs, const std::map<Key, Value>& rhs);

template <typename Container> Container Sqr (const Container& c){
    return c * c;
}

template <typename T> std::vector<T> operator * (const std::vector<T>& lhs, const std::vector<T>& rhs){
    std::vector<T> res(lhs.size());
    for (size_t i = 0; i < lhs.size(); i++){
        res[i] = lhs[i] * rhs[i];
    }
    return res;
}
template <typename First, typename Second>
std::pair<First, Second> operator * (const std::pair<First, Second>& lhs, const std::pair<First, Second>& rhs){
    return std::make_pair(lhs.first * rhs.first, lhs.second * rhs.second);
}
template <typename Key, typename Value>
std::map<Key, Value> operator * (const std::map<Key, Value>& lhs, const std::map<Key, Value>& rhs){
    std::map<Key, Value> res;
    for (const auto& x : lhs){
        res[x.first] = x.second * x.second;
    }
    return res;
}