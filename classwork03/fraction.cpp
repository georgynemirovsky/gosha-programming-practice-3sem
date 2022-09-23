#include <iostream>

using namespace std;

class Fraction {
    public:
        friend ostream& operator<<(ostream& out, const Fraction& obj);  // �������� ������ << "��������� �����������"
        friend istream& operator>>(istream& is, Fraction& obj);  // �������� ����� >> ��������� >> �����������

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
            cout << numerator << "/" << denominator << endl;  // ������� ����� � ������� 'numerator / denominator'
        }

        void fracReverse() {  // ����������� �����, �����������<->���������
            int t = numerator;
            numerator = denominator;
            denominator = t;
        }

        void fracSimplify() {  // ��������� ����� �� �����������
            int gcd = GCD();
            numerator /= gcd;
            denominator /= gcd;
        }

        void multByNumber(int value) {  // �������� ����� �� �����
            numerator *= value;
            fracSimplify();
        }

        void multByFrac(const Fraction& other) {
            numerator *= other.numerator;
            denominator *= other.denominator;
            fracSimplify();
            // �������� ����� �� ������ �����, ��������� �������� � ���������� (� this)
        }

        Fraction multByFracReturn(const Fraction& other) const {
            int new_num, new_den;
            new_num = numerator * other.numerator;
            new_den = denominator * other.denominator;
            Fraction new_frac(new_num, new_den);
            new_frac.fracSimplify();
            return new_frac;
            // �������� ����� � ���������� ��������� � ������
        }

        void sumFrac(const Fraction& other) {
            int a = numerator * other.denominator;
            int b = denominator * other.numerator;
            numerator = a + b;
            denominator *= other.denominator;
            // �������������� ����� �� ������ �����, ��������� �������� � ���������� (� this)
        }

        Fraction sumFracReturn(const Fraction& other) const {
            int a = numerator * other.denominator;
            int b = denominator * other.numerator;
            a = a + b;
            b = denominator * other.denominator;
            Fraction new_frac(a, b);
            new_frac.fracSimplify();
            return new_frac;
            // �������������� ����� � ������� ��������� � ������
        }

        void diffFrac(const Fraction& other) {
            int a = numerator * other.denominator;
            int b = denominator * other.numerator;
            numerator = a - b;
            denominator *= other.denominator;
            fracSimplify();
            // ����� �������� ������, ��������� �������� � ���������� (� this)
        }

        Fraction diffFracReturn(const Fraction& other) const {
            int a = numerator * other.denominator;
            int b = denominator * other.numerator;
            a = a - b;
            b = denominator * other.denominator;
            Fraction new_frac(a, b);
            new_frac.fracSimplify();
            return new_frac;
            // ����� �������� ������, ��������� � ������
        }

        double calc() {  // ���������� �������� ����� � ���������� ����
            return double(numerator) / double(denominator);
        }

        int getNumerator() {  // ���������� �������� ���������
            return numerator;
        }

        int getDenominator() {  // ���������� ���������� �����������
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
