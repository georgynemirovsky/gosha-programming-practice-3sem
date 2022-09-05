#include <iostream>

using namespace std;

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

int next_int (void* &current){
    int* cur_ptr = reinterpret_cast<int*>(current);
    cur_ptr++;
    current = reinterpret_cast<void*>(cur_ptr);
    return 0;
}

int minimal(void* arr, int arr_size, int type_size, int (*compare)(void *, void *), int (*next)(void * &)) {
    int min_index = 0;
    void* min_value = arr;
    for (int i = 0; i < arr_size; i++){
        if (compare(arr, min_value) == 1){
            min_index = i;
            min_value = arr;
        }
        next(arr);
    }
    return min_index;
}

int main(){
    int arr[10] = {0};
    for (int i = 0; i < 10; i++){
        cin >> arr[i];
    }
    cout << "Index of the minimum element: " << minimal(arr, 10, sizeof(int), compare_int_min, next_int) << endl;
    cout << "Index of the maximum element: " << minimal(arr, 10, sizeof(int), compare_int_max, next_int) << endl;
    return 0;
}
