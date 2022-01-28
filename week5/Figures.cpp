#include "sstream"
#include "iostream"
#include "vector"
#include "iomanip"
#include "memory"
#include "cmath"
using namespace std;

const float pi = 3.14;

class Figure{
public:
    Figure(const string& type) : name_(type) {};
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
    const string name_;
};
class Rect : public Figure{
public:
    Rect(const double& width, const double& height) : Figure("RECT"),
            width_(width), height_(height){};
    string Name() const override {
        return name_;
    }
    double Perimeter() const override{
        return (width_ + height_) * 2;
    }
    double Area() const override{
        return  width_ * height_;
    }
private:
    size_t width_, height_;
};
class Circle : public Figure{
public:
    Circle(const size_t& radius) : Figure("CIRCLE"),
            radius_(radius){};
    string Name() const override {
        return name_;
    }
    double Perimeter() const override{
        return 2 * pi * radius_;
    }
    double Area() const override{
        return  pi * radius_ * radius_;
    }
private:
    size_t radius_;
};
class Triangle : public Figure{
public:
    Triangle(const size_t& a, const size_t& b, const size_t& c) : Figure("TRIANGLE"),
            a_(a), b_(b), c_(c){};
    string Name() const override {
        return name_;
    }
    double Perimeter() const override{
        return a_ + b_ + c_;
    }
    double Area() const override{
        double p = Perimeter()/2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }
private:
    size_t a_, b_, c_;
};
shared_ptr<Figure> CreateFigure(istringstream& is){
    string name;
    is >> name;
    if (name == "RECT"){
        size_t w, h;
        is >> w >> h;
        return make_shared<Rect>(Rect(w, h));
    }
    if (name == "CIRCLE"){
        size_t r;
        is >> r;
        return make_shared<Circle>(Circle(r));
    }
    if(name == "TRIANGLE"){
        size_t a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(Triangle(a, b, c));
    }
    throw std::invalid_argument("This type is not supported");
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}