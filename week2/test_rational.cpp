#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}
template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}
template <class K, class V>
ostream& operator << (ostream& os, const pair<K, V>& p) {
    os << "{" << p.first << ": " << p.second;
    return os << "}";
}
template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

void AssertRational(const Rational& submitted, const pair<int, int>& correct, const string& message) {
    AssertEqual(pair<int, int>(submitted.Numerator(), submitted.Denominator()), correct, message);
}
const auto p = [](int numerator, int denominator){
    return pair<int, int>(numerator, denominator);
};
void TestDefault(){
    Rational r;
    AssertRational(r, p(0, 1), "check default constructor");
}
void TestGCD(){
    Rational r(12, 2);
    AssertRational(r, p(6, 1), "reduciton1");
    AssertRational({4, 8}, p(1, 2), "reduciton2");
}
void TestNegative(){
    Rational r(-2, 4);
    AssertRational(r, p(-1, 2), "negative and reduciton");
    AssertRational({4, -2}, p(-2, 1), "negative denominator");
    AssertRational({-4, -4}, p(1, 1), "negative both");
}
void TestZero(){
    Rational r(0, 100);
    AssertRational(r, p(0, 1), "denominator to 1");
}
int main() {
    TestRunner runner;
    runner.RunTest(TestDefault, "TestDefault");
    runner.RunTest(TestGCD, "TestGCD");
    runner.RunTest(TestNegative, "TestNegative");
    runner.RunTest(TestZero, "TestZero");
    return 0;
}
