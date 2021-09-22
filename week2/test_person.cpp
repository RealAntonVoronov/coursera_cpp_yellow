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

void TestChangeName(){
    Person person;
    person.ChangeFirstName(1900, "Anton");
    AssertEqual(person.GetFullName(1900), "Anton with unknown last name", "this year changed name");
    AssertEqual(person.GetFullName(1890), "Incognito", "has not changed name yet");
    AssertEqual(person.GetFullName(1910), "Anton with unknown last name", "some time after changed name");
    person.ChangeFirstName(1895, "Tony");
    AssertEqual(person.GetFullName(1900), "Anton with unknown last name",
                "Changed name in the past, but now already with new.");
    AssertEqual(person.GetFullName(1890), "Incognito","has not changed name yet too");
    AssertEqual(person.GetFullName(1896), "Tony with unknown last name", "his old name.");
    AssertEqual(person.GetFullName(1910), "Anton with unknown last name", "his future name.");
    person.ChangeFirstName(1910, "Anthony");
    AssertEqual(person.GetFullName(1910), "Anthony with unknown last name",
                "succesfully changed in the future");
    return;
}
void TestChangeSurname(){
    Person person;
    person.ChangeLastName(1900, "Voronov");
    AssertEqual(person.GetFullName(1900), "Voronov with unknown first name",
                "this year changed surname");
    AssertEqual(person.GetFullName(1890), "Incognito", "has not changed surname yet");
    AssertEqual(person.GetFullName(1910), "Voronov with unknown first name",
                "some time after changed name");
    person.ChangeLastName(1895, "Semyonkin");
    AssertEqual(person.GetFullName(1900), "Voronov with unknown first name",
                "Changed surname in the past, but now already with new.");
    AssertEqual(person.GetFullName(1890), "Incognito","has not changed name yet too");
    AssertEqual(person.GetFullName(1896), "Semyonkin with unknown first name", "his old surname.");
    AssertEqual(person.GetFullName(1910), "Voronov with unknown first name", "his future surname.");
    return;
}
void TestCombine(){
    Person p;
    AssertEqual(p.GetFullName(1900), "Incognito", "noname");
    p.ChangeFirstName(1900, "Anton");
    AssertEqual(p.GetFullName(1899), "Incognito", "still noname");
    AssertEqual(p.GetFullName(1900), "Anton with unknown last name", "still noname");
    p.ChangeLastName(1899, "Voronov");
    AssertEqual(p.GetFullName(1898), "Incognito", "still noname");
    AssertEqual(p.GetFullName(1899), "Voronov with unknown first name", "already Voronov");
    AssertEqual(p.GetFullName(1900), "Anton Voronov", "already Anton Voronov");
    AssertEqual(p.GetFullName(1901), "Anton Voronov", "still Anton Voronov");
    p.ChangeFirstName(1905, "Tony");
    AssertEqual(p.GetFullName(1902), "Anton Voronov", "still Anton Voronov, but changes start to appear");
    AssertEqual(p.GetFullName(1905), "Tony Voronov", "now Tony Voronov");
    AssertEqual(p.GetFullName(1907), "Tony Voronov", "Tony Voronov from the future");
    p.ChangeLastName(1906, "Semyonkin");
    AssertEqual(p.GetFullName(1906), "Tony Semyonkin", "finally Tony Semyonkin");
    AssertEqual(p.GetFullName(1905), "Tony Voronov", "always has been Tony Voronov");
    AssertEqual(p.GetFullName(1900), "Anton Voronov", "remember him? Anton Voronov");
    AssertEqual(p.GetFullName(1899), "Voronov with unknown first name", "History cannot be changed");
}
int main() {
    TestRunner runner;
    runner.RunTest(TestChangeName, "TestChangeName");
    runner.RunTest(TestChangeSurname, "TestChangeSurname");
    runner.RunTest(TestCombine, "TestEverything");
    return 0;
}