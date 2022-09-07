#include <iostream>

using namespace std;

int next_element (void* &current, int type_size){
    char* cur_ptr = reinterpret_cast<char*>(current);
    cur_ptr += type_size;
    current = reinterpret_cast<void*>(cur_ptr);
    return 0;
}

int compare_int_min (void* a, void* b){
    if ((*reinterpret_cast<int*>(a)) < (*reinterpret_cast<int*>(b))){
        return 1;
    }
    return 0;
}

int compare_int_max (void* a, void* b){
    if ((*reinterpret_cast<int*>(a)) > (*reinterpret_cast<int*>(b))){
        return 1;
    }
    return 0;
}

int minimal(void* arr, int arr_size, int type_size, int (*compare)(void *, void *)) {
    int min_index = 0;
    void* min_value = arr;
    for (int i = 0; i < arr_size; i++){
        if (compare(arr, min_value) == 1){
            min_index = i;
            min_value = arr;
        }
        next_element(arr, type_size);
    }
    return min_index;
}

int main(){
    int arr_int[5] = {0};
    char arr_char[5] = {' '};
    cout << "Enter 5 integers" << endl;
    for (int i = 0; i < 5; i++){
        cin >> arr_int[i];
    }
    cout << "Index of the minimum element: " << minimal(arr_int, 5, sizeof(int), compare_int_min) << endl;
    cout << "Index of the maximum element: " << minimal(arr_int, 5, sizeof(int), compare_int_max) << endl;
    cout << "Enter 5 chars" << endl;
    for (int i = 0; i < 5; i++){
        cin >> arr_char[i];
    }
    cout << "Index of the minimum element: " << minimal(arr_int, 5, sizeof(char), compare_int_min) << endl;
    cout << "Index of the maximum element: " << minimal(arr_int, 5, sizeof(char), compare_int_max) << endl;
    return 0;
}
