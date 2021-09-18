#include "iostream"

int main(){
    int n;
    int density;
    std::cin >> n >> density;
    uint64_t sum = 0;
    for (int i = 0; i < n; i++){
        uint64_t w, h, d;
        std::cin >> w >> h >> d;
        sum += w * h * d * density;
    }
    std::cout << sum;
}