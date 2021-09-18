#include "vector"
#include "iostream"
#include "map"

template<typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value>& m, Key k){
    if (m.count(k) == 0){
        throw std::runtime_error("");
    }
    else return m[k];
}