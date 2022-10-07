#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    double x = 0;
    double y = 0;
    friend ostream& operator<<(ostream& out, const Point& point);
    friend istream& operator>>(istream& in, Point& point);

    Point(double x, double y): x(x), y(y) {}
    Point(): Point(0, 0) {}
    Point operator+(const Point& other) {
        Point tmp = *this;
        tmp.x += other.x;
        tmp.y += other.y;
        return tmp;
    }
    Point operator-(const Point& other) {
        Point tmp = *this;
        tmp.x -= other.x;
        tmp.y -= other.y;
        return tmp;
    }
    Point operator/(double m) {
        Point tmp = *this;
        tmp.x /= m;
        tmp.y /= m;
        return tmp;
    }
    Point operator=(const Point& other) {
        x = other.x;
        y = other.y;
    }
};

istream& operator>>(istream& in, Point &point) {
        in >> point.x >> point.y;
        return in;
}

ostream& operator<<(ostream& out, Point const &point) {
    out << "(" << point.x << ", " << point.y << ")";
    return out;
}

double length (Point &a, Point &b) {
    Point temp;
    temp = a - b;
    return sqrt(temp.x * temp.x + temp.y * temp.y);
}

class Shape {
    protected:
        vector<Point> storage;
    public:
        Shape(vector<Point> storage): storage(storage) {}
        virtual double area() = 0;
        virtual double perimeter() = 0;
        virtual Point center() = 0;

};

class Triangle: public Shape {
    protected:
        double a = 0;
        double b = 0;
        double c = 0;

    public:
        Triangle(vector<Point> storage): Shape(storage) {
            a = length(storage[0], storage[1]);
            b = length(storage[0], storage[2]);
            c = length(storage[1], storage[2]);
            cout << endl << a << " " << b << " " << c << endl;
        }

        double area() override {
            double p = (a + b + c) / 2;
            return sqrt(p * (p - a) * (p - b) * (p - c));
        }

        double perimeter() override {
            return (a + b + c);
        }

        Point center() override {
            return ((storage[0] + storage[1] + storage[2]) / 3);
        }
};

class Square: public Shape {
    protected:
        double a = 0;
    public:
        Square(vector<Point> storage): Shape(storage), a(length(storage[0], storage[1])) {}

        double area() override {
            return (a * a);
        }

        double perimeter() override {
            return a * 4;
        }

        Point center() override {
            return ((storage[0] + storage[1] + storage[3] + storage[4]) / 4);
        }
};

class Line: public Shape {
    protected:
        double a = 0;
    public:
        Line(vector<Point> storage): Shape(storage), a(length(storage[0], storage[1])) {}

        double area() override {
            return 0;
        }

        double perimeter() override {
            return a;
        }

        Point center() override {
            return ((storage[0] + storage[1]) / 2);
        }
};

int main () {
    Point a, b, c;
    cin >> a >> b >> c;
    vector<Point>triangle_points = {a, b, c};
    Triangle t(triangle_points);
    cout << t.area() << endl;
    cout << t.perimeter() << endl;
    cout << (t.center()) << endl;
    return 0;
}
