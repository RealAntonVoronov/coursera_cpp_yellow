#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person (const string& name, const string& type) : Name(name), Type(type){};
    virtual void Walk(const string& destination) const = 0;
    string GetName() const {
        return Name;
    }
    string GetType() const {
        return Type;
    }
private:
    const string Name, Type;
};
void PersonWalk(const string& type, const string& name, const string& destination){
    cout << type << ": " << name << " walks to: " << destination << endl;
}
class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong) : Person(name, "Student"),
                                                               FavouriteSong(favouriteSong) {
    };
    void Learn() const {
        cout << GetType() << ": " << GetName() << " learns" << endl;
    }
    void SingSong() const {
        cout << GetType() << ": " << GetName() << " sings a song: " << FavouriteSong << endl;
    }
    void Walk(const string& destination) const override {
        PersonWalk(GetType(), GetName(), destination);
        SingSong();
    }
private:
    string FavouriteSong;
};
class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject) : Person(name, "Teacher"), Subject(subject){};
    void Teach() {
        cout << GetType() << ": " << GetName() << " teaches: " << Subject << endl;
    }
    void Walk(const string& destination) const override {
        PersonWalk(GetType(), GetName(), destination);
    }
private:
    string Subject;
};
class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name, "Policeman"){};
    void Check(shared_ptr<Person> p){
        cout << GetType() << ": " << GetName() << " checks " << p->GetType() << ". " << p->GetType()
             << "'s name is: " << p->GetName() << endl;
    }
    void Walk(const string& destination) const override {
        PersonWalk(GetType(), GetName(), destination);
    }
};
void VisitPlaces(shared_ptr<Person> p, vector<string> places){
    for (const string& x : places){
        p->Walk(x);
    }
}
int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(make_shared<Teacher>(t), {"Moscow", "London"});
    p.Check(make_shared<Student>(s));
    VisitPlaces(make_shared<Student>(s), {"Moscow", "London"});
    return 0;
}
