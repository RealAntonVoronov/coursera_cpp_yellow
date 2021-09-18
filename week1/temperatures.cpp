#include "iostream"
#include "vector"

int main(){
    int n;
    std::cin >> n;
    std::vector<int> temperatures(n);
    int64_t avg = 0;
    for (int& x : temperatures){
        std::cin >> x;
        avg += x;
    }
    avg /= n;
    std::vector<size_t> good_days;
    for (size_t i = 0; i < n; i++){
        if (temperatures[i] > avg){
            good_days.push_back(i);
        }
    }
    std::cout << good_days.size() << std::endl;
    for (auto x : good_days){
        std::cout << x << " ";
    }
}