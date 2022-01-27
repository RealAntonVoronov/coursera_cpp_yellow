#include "iostream"
#include "deque"
using std::string;

int main() {
    int n;
    std::deque<string> res;
    string first, operation, operand;
    std::cin >> first >> n;
    res.push_back(first);
    for (size_t i=0; i < n; i++){
        std::cin >> operation >> operand;
        res.push_front("(");
        res.push_back(")");
        res.push_back(" ");
        res.push_back(operation);
        res.push_back(" ");
        res.push_back(operand);
    }
    for (const string& x : res) {
        std::cout << x;
    }
    return 0;
}