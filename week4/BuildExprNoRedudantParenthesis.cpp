#include "iostream"
#include "deque"
#include "map"
using std::string;

int main() {
    int n;
    std::map<string, int> priority = {{"+", 0}, {"-", 0},
                                      {"*", 1}, {"/", 1}};
    std::deque<string> res;
    string first, prev_operation, operation, operand;
    bool first_operation=true;
    std::cin >> first >> n;
    res.push_back(first);
    for (size_t i=0; i < n; i++){
        std::cin >> operation >> operand;
        if (!first_operation) {
            if (priority[operation] > priority[prev_operation]) {
                res.push_front("(");
                res.push_back(")");
            }
        }
        res.push_back(" ");
        res.push_back(operation);
        res.push_back(" ");
        res.push_back(operand);
        prev_operation = operation;
        first_operation = false;
    }
    for (const string& x : res) {
        std::cout << x;
    }
    return 0;
}