#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person (const string& name, const string& type) : Name(name), Type(type){};
    void Log() const {
        cout << Type << ": " << Name;
    }
    virtual void Walk(const string& destination) const {
        Log();
        cout << " walks to: " << destination << endl;
    }
    string GetName() const {
        return Name;
    }
    string GetType() const {
        return Type;
    }
private:
    const string Name, Type;
};
class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong) : Person(name, "Student"),
                                                               FavouriteSong(favouriteSong) {
    };
    void Learn() const {
        Log();
        cout << " learns" << endl;
    }
    void SingSong() const {
        Log();
        cout << " sings a song: " << FavouriteSong << endl;
    }
    void Walk(const string& destination) const override {
        Log();
        cout << " walks to: " << destination << endl;
        SingSong();
    }
private:
    string FavouriteSong;
};
class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject) : Person(name, "Teacher"), Subject(subject){};
    void Teach() const {
        cout << GetType() << ": " << GetName() << " teaches: " << Subject << endl;
    }
private:
    string Subject;
};
class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name, "Policeman"){};
    void Check(const Person& p) const {
        Log();
        cout << " checks " << p.GetType() << ". " << p.GetType()
             << "'s name is: " << p.GetName() << endl;
    }
};
void VisitPlaces(const Person& p, vector<string> places){
    for (const string& x : places){
        p.Walk(x);
    }
}
int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
