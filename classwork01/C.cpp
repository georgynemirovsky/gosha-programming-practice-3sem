#include <iostream>
#include <cstring>

using namespace std;

void swap (void* a, void* b, int type_size){
    void* tmp = malloc(type_size);
    memcpy (tmp, a, type_size );
    memcpy (a, b, type_size );
    memcpy (b, tmp, type_size );
    free(tmp);
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

void* next_element (void* current, int length, int type_size){
    char* cur_ptr = reinterpret_cast<char*>(current);
    cur_ptr += length * type_size;
    current = reinterpret_cast<char*>(cur_ptr);
    return current;
}

int part(void* A, int lo, int hi, int type_size) {
    void* pivot = next_element(A, (hi + lo) / 2, type_size);
    int i = lo;
    int j = hi;
    while (true) {
        while (compare_int_min(next_element(A, i, type_size), pivot)) {
            i++;
        }
        while (compare_int_max(next_element(A, j, type_size), pivot)) {
            j--;
        }
        if (i >= j) {
            return j;
        }
        swap(next_element(A, i, type_size), next_element(A, j, type_size), type_size);
        i++;
        j--;
    }
}

void quicksort(void* A, int lo, int hi, int type_size)
{
    if (lo < hi) {
        int p = part(A, lo, hi, type_size);
        quicksort(A, lo, p, type_size);
        quicksort(A, p + 1, hi, type_size);
    }
}

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    quicksort(arr, 0, n - 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    delete [] arr;
    return 0;
}

