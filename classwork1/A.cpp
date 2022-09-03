#include <iostream>

using namespace std;

void swap(void* x, void* y) {
    void* t;
    t = x;
    x = y;
    y = t;
}

int main() {
    int a, b;
    cin >> a >> b;
    swap(a, b);
    cout << a << " " << b << endl;
    return 0;
}
