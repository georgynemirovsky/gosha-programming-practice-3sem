#include <iostream>

using namespace std;

int next_int (void* &current){
    int* cur_ptr = reinterpret_cast<int*>(current);
    cur_ptr++;
    current = reinterpret_cast<int*>(cur_ptr);
    return 0;
}

int main(){
    int arr[10] = {0};
    void* cur = arr;
    for (int i = 0; i < 10; i++){
        cin >> arr[i];
    }
    next_int(cur);
    return 0;
}
