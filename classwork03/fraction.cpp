#include <iostream>

using namespace std;

class Fraction {
    public:
        friend ostream& operator<<(ostream& out, const Fraction& obj);  // Оператор вывода << "числитель знаминатель"
        friend istream& operator>>(istream& is, Fraction& obj);  // Оператор ввода >> числитель >> знаминатель

        Fraction& operator+=(const Fraction& other) {
            this->sumFrac(other);
            return *this;
        }

        Fraction& operator-=(const Fraction& other) {
            this->diffFrac(other);
            return *this;
        }

        Fraction& operator*=(const Fraction& other) {
            this->multByFrac(other);
            return *this;
        }

        Fraction operator+(const Fraction& other) const{
            Fraction tmp = *this;
            tmp += other;
            return tmp;
        }

        Fraction operator-(const Fraction& other) const{
            Fraction tmp = *this;
            tmp -= other;
            return tmp;
        }

        Fraction operator*(const Fraction& other) const{
            Fraction tmp = *this;
            tmp *= other;
            return tmp;
        }

        Fraction& operator++() {
            return *this += Fraction(1);
        }
        Fraction operator++(int){
            Fraction result = *this;
            ++(*this);
            return result;
        }
        Fraction& operator--(){
            return *this -= Fraction(1);
        }
        Fraction operator--(int){
            Fraction result = *this;
            --(*this);
            return result;
        }

        Fraction(int numerator, int denominator): numerator(numerator), denominator(denominator) { }

        Fraction(int numerator): numerator(numerator), denominator(1) {}
        Fraction() = delete;

        Fraction(const Fraction& other): numerator(other.numerator), denominator(other.denominator) { }

        void printFraction() {
            cout << numerator << "/" << denominator << endl;  // Выводит дробь в формате 'numerator / denominator'
        }

        void fracReverse() {  // Перевернуть дробь, знаменатель<->числитель
            int t = numerator;
            numerator = denominator;
            denominator = t;
        }

        void fracSimplify() {  // Сокращает дробь по возможности
            int gcd = GCD();
            numerator /= gcd;
            denominator /= gcd;
        }

        void multByNumber(int value) {  // Умножить дробь на число
            numerator *= value;
            fracSimplify();
        }

        void multByFrac(const Fraction& other) {
            numerator *= other.numerator;
            denominator *= other.denominator;
            fracSimplify();
            // Умножить дробь на другую дробь, результат оставить в вызывающей (в this)
        }

        Fraction multByFracReturn(const Fraction& other) const {
            int new_num, new_den;
            new_num = numerator * other.numerator;
            new_den = denominator * other.denominator;
            Fraction new_frac(new_num, new_den);
            new_frac.fracSimplify();
            return new_frac;
            // умножает дроби и возвращает результат в третью
        }

        void sumFrac(const Fraction& other) {
            int a = numerator * other.denominator;
            int b = denominator * other.numerator;
            numerator = a + b;
            denominator *= other.denominator;
            // Просуммировать дробь на другую дробь, результат оставить в вызывающей (в this)
        }

        Fraction sumFracReturn(const Fraction& other) const {
            int a = numerator * other.denominator;
            int b = denominator * other.numerator;
            a = a + b;
            b = denominator * other.denominator;
            Fraction new_frac(a, b);
            new_frac.fracSimplify();
            return new_frac;
            // просуммировать дроби и вернуть результат в третью
        }

        void diffFrac(const Fraction& other) {
            int a = numerator * other.denominator;
            int b = denominator * other.numerator;
            numerator = a - b;
            denominator *= other.denominator;
            fracSimplify();
            // Взять разность дробей, результат оставить в вызывающей (в this)
        }

        Fraction diffFracReturn(const Fraction& other) const {
            int a = numerator * other.denominator;
            int b = denominator * other.numerator;
            a = a - b;
            b = denominator * other.denominator;
            Fraction new_frac(a, b);
            new_frac.fracSimplify();
            return new_frac;
            // Взять разность дробей, результат в третью
        }

        double calc() {  // Возвращает значение дроби в десятичном виде
            return double(numerator) / double(denominator);
        }

        int getNumerator() {  // Возвращает значение числителя
            return numerator;
        }

        int getDenominator() {  // Возвращает знамечение знаменателя
            return denominator;
        }

    private:
        int numerator;
        int denominator;
        int GCD() {
            int a = numerator;
            int b = denominator;
            if (a < b) {
                swap(a, b);
            }
            while (a % b != 0) {
                a = a % b;
                swap(a, b);
            }
            return b;
        }
};

ostream& operator<<(ostream& out, const Fraction& obj) {
    out << obj.numerator << "/" << obj.denominator << "\n";
    return out;
}

istream& operator>>(istream& in, Fraction& obj) {
    in >> obj.numerator >> obj.denominator;
    return in;
}

int main() {
    Fraction a(1), b(1);
    cin >> a >> b;
    cout << "+ " << a + b << endl;
    cout << "- " << a - b << endl;
    cout << "* " << a * b << endl;
    cout << "++a " << (++a) << endl;
    cout << "--a " << (--a) << endl;
    a += b;
    cout << "a += " << a << endl;
    a -= b;
    cout << "a -= " << a << endl;
    a *= b;
    cout << "a *= " << a << endl;
    return 0;
}
