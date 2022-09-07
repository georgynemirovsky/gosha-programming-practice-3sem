#include <iostream>
#include <limits>

using namespace std;

int main(){
    cout << "char " << numeric_limits<char>::min() << " " << numeric_limits<char>::max() << " " << sizeof(char) * 8 << endl;
    cout << "short int " << numeric_limits<short int>::min() << " " << numeric_limits<short int>::max() << " " << sizeof(short int) * 8 << endl;
    cout << "int " << numeric_limits<int>::min() << " " << numeric_limits<int>::max() << " " << sizeof(int) * 8 << endl;
    cout << "long int " << numeric_limits<long int>::min() << " " << numeric_limits<long int>::max() << " " << sizeof(long int) * 8 << endl;
    cout << "float " << numeric_limits<float>::min() << " " << numeric_limits<float>::max() << " " << sizeof(float) * 8 << endl;
    cout << "double " << numeric_limits<double>::min() << " " << numeric_limits<double>::max() << " " << sizeof(double) * 8 << endl;
    return 0;
}
