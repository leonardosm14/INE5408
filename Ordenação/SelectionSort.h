#include <stdio.h>

void selectionSort(int arr[], int n) {
    int k, x;
    for (int i = 0; i < n-1; i++) {
        k = i;
        x = arr[i];
        for (int j = i+1; j < n; j++) {
            if (arr[j] < x) {
                k = j;
                x = arr[j];
            }
        }
        arr[k] = arr[i];
        arr[i] = x;
    }
}