#include <iostream>
using namespace std;

class Animal {
public:
    Animal (const string& in_name) : Name(in_name){
    }
    const string Name;
};


class Dog : public Animal{
public:
    Dog(const string& name) : Animal(name){};
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};