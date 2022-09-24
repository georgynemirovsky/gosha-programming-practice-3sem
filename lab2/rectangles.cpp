#include <iostream>
#include <string>

using namespace std;

string line_without_spase (string a) {
    string tmp;
    for (char c : a)
        if (c != ' ')
            tmp += c;
    return tmp;
}
struct Point {
    unsigned long long x, y;
    Point ( unsigned long long x , unsigned long long y ): x(x), y(y) { }
    Point minx(Point const &rha) const {
        return Point(rha.x < x ? rha.x : x, y);
    }
    Point miny(Point const &rha) const {
        return Point(x, rha.y < y ? rha.y : y);
    }
    Point maxx(Point const &rha) const {
        return Point(rha.x > x ? rha.x : x, y);
    }
    Point maxy(Point const &rha) const {
        return Point(x, rha.y > y ? rha.y : y);
    }
    Point operator=(Point const &other) {
        x = other.x;
        y = other.y;
    }
    void print() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

class Rectangle {
    public:
        Rectangle(Point const & point) : point(point) { }
        Rectangle() : Rectangle (Point(0, 0)) { }
        void print() const {
            point.print();
        }
        Rectangle operator*(const Rectangle &rha) const{
            Rectangle smallx = Rectangle (point.minx(rha.point));
            Rectangle smally = Rectangle (smallx.point.miny(rha.point));
            return smally;
        }
        Rectangle operator+(const Rectangle &rha ) const{
            Rectangle bigx = Rectangle (point.maxx(rha.point));
            Rectangle bigy = Rectangle (bigx.point.maxy(rha.point));
            return bigy;
        }
        Rectangle &operator+=(Rectangle const &rha)
        {
            Rectangle bigx = Rectangle (point.maxx(rha.point));
            Rectangle bigy = Rectangle (bigx.point.maxy(rha.point));
            point = bigy.point;
            return *this;
        }
        Rectangle &operator*=(Rectangle const &rha)
        {
            Rectangle smallx = Rectangle (point.minx(rha.point));
            Rectangle smally = Rectangle (smallx.point.miny(rha.point));
            point = smally.point;
            return *this;
        }
    private:
        Point point;
};


Rectangle Get_Rectangle(int &i, string expression) {
    int x = 0;
    i++;
    while (expression[i] != ',')
    {
        x = 10 * x + (expression[i] - '0');
        i++;
    }
    i++;
    int y = 0;
    while (expression[i] != ')')
    {
        y = 10 * y + (expression[i] - '0');
        i++;
    }
    Rectangle rec(Point(x, y));
    return rec;
}

Rectangle calk(string expression){
    int number = 0;
    int number_mult = 0;
    for (char c : expression) {
        if (c == '*')
            number_mult++;
        if (c == '(')
            number++;
    }
    Rectangle *arr = new Rectangle[number - number_mult];
    int i = 0;
    int i_sum = 0;
    while (i < expression.length()) {
        Rectangle a(Point(0, 0));
        if (expression[i] == '(') {
            Rectangle tmp = Get_Rectangle(i, expression);
            a += tmp;
        }
        if (not(++i == expression.length())) {
            while (expression[i] == '*') {
                i++;
                Rectangle tmp = Get_Rectangle(i, expression);
                i++;
                a *= tmp;
            }
        }
        i++;
        arr[i_sum] = a;
        i_sum++;
    }
    Rectangle result;
    for (i = 0; i < number - number_mult; ++i) {
        result += arr[i];
    }
    delete [] arr;
    return result;
}

int main() {
    string expression;
    getline(cin, expression);
    Rectangle rec = calk(line_without_spase(expression));
    rec.print();
    return 0;
}
