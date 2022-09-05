#include<iostream>
#include <cstring>

using namespace std;

void swap (void* a, void* b, int type_size){
    void* tmp = malloc(type_size);
    memcpy (tmp, a, type_size );
    memcpy (a, b, type_size );
    memcpy (b, tmp, type_size );
    free(tmp);
}

int main(){
    char a, b;
    cin >> a >> b;
    cout << "Before swap: a = " << a << ", b = " << b << endl;
    swap(&a , &b, sizeof(char));
    cout << "After swap: a = " << a << ", b = " << b << endl;
    return 0;
}
